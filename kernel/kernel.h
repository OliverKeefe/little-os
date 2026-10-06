#pragma once
#include "../common/common.h"

// trap_frame represents the program's state.
struct trap_frame {
    uint32_t ra;
    uint32_t gp;
    uint32_t tp;
    uint32_t t0;
    uint32_t t1;
    uint32_t t2;
    uint32_t t3;
    uint32_t t4;
    uint32_t t5;
    uint32_t t6;
    uint32_t a0;
    uint32_t a1;
    uint32_t a2;
    uint32_t a3;
    uint32_t a4;
    uint32_t a5;
    uint32_t a6;
    uint32_t a7;
    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
    uint32_t s8;
    uint32_t s9;
    uint32_t s10;
    uint32_t s11;
    uint32_t sp;
} __attribute__((packed));

// Macro for reading CSR registers.
#define READ_CSR(reg)                                             \
        ({                                                        \
            unsigned long __tmp;                                  \
            __asm__ __volatile__("csrr %0, " #reg : "=r"(__tmp)); \
            __tmp;                                                \
        })

// Macro for writing to CSR registers.
#define WRITE_CSR(reg, value)                                       \
        do {                                                        \
            uint32_t __tmp = (value);                               \
            __asm__ __volatile__("csrw " #reg ", %0" ::"r"(__tmp)); \
        } while (0)

// PANIC is a helpful macro for handling kernel panics (crashing gracefully).
#define PANIC(fmt, ...) do {                                                     \
   printf("KERNEL PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
   while (1) {}                                                                  \
} while (0)                                                                      \

struct sbiret {
    long error;
    long value;
};

// Max number of processes.
#define PROCS_MAX 8

// Unused process control structure.
#define PROC_UNUSED 0

// Runnable processes.
#define PROC_RUNNABLE 1

/*
 process defines a Process Control Block (PCB)
 which is a process object / entity.

 `pid` - The process ID.
 `state` - Integer representation of process state.
 `sp` - Virtual address of stack pointer.
 `stack` - Kernel stack.
 */
struct process {
    int pid;
    int state;
    vaddr_t sp;
    uint32_t *page_table;
    uint8_t stack[8192];
};

__attribute__((naked)) void switch_context(uint32_t *prev_sp, uint32_t *next_sp);

struct process *create_process(uint32_t pc);

extern struct process *current_proc;
extern struct process *idle_proc;

void yield(void);

#define SATP_SV32 (1u << 31)

// Valid
#define PAGE_V (1 << 0)

// Readable
#define PAGE_R (1 << 1)

// Writable
#define PAGE_W (1 << 2)

// Executable
#define PAGE_X (1 << 3)

// User (accessible in User Mode).
#define PAGE_U (1 << 4)

extern int __kernel_base[];
extern char __free_ram[], __free_ram_end[];

paddr_t alloc_pages(uint32_t n);

/**
 * map_page takes the first-level page table, the virtual address, the physical
 * address and the table flags. Then, ensures the first level page table exists,
 * creates the second page table if required and then sets the second level page
 * table entry to map the physical page.
 *
 * The physical address (paddr) is divided by PAGE_SIZE because the entry should
 * contain the physical page number, not the physical address itself.
 *
 * @param table1
 * @param vaddr
 * @param paddr
 * @param flags
 */
void map_page(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags);
