#include "kernel.h"

__attribute__((naked)) void switch_context(uint32_t *prev_sp, uint32_t *next_sp) {
    __asm__ __volatile__(
        // Save callee-saved registers onto the current process stack.
        "addi sp, sp, -13 * 4\n" // Allocate stack space for 13 4-byte registers.
        "sw ra, 0 * 4(sp)\n" // Save callee-saved registers only.
        "sw s0, 1 * 4(sp)\n"
        "sw s1, 2 * 4(sp)\n"
        "sw s2, 3 * 4(sp)\n"
        "sw s3, 4 * 4(sp)\n"
        "sw s4, 5 * 4(sp)\n"
        "sw s5, 6 * 4(sp)\n"
        "sw s6, 7 * 4(sp)\n"
        "sw s7, 8 * 4(sp)\n"
        "sw s8, 9 * 4(sp)\n"
        "sw s9, 10 * 4(sp)\n"
        "sw s10, 11 * 4(sp)\n"
        "sw s11, 12 * 4(sp)\n"

        // Switch to the stack pointer.
        "sw sp, (a0)\n" // *prev_sp = sp;
        "lw sp, (a1)\n" // Switches stack pointer (sp) here.

        "lw ra, 0 * 4(sp)\n"
        "lw s0, 1 * 4(sp)\n"
        "lw s1, 2 * 4(sp)\n"
        "lw s2, 3 * 4(sp)\n"
        "lw s3, 4 * 4(sp)\n"
        "lw s4, 5 * 4(sp)\n"
        "lw s5, 6 * 4(sp)\n"
        "lw s6, 7  * 4(sp)\n"
        "lw s7, 8  * 4(sp)\n"
        "lw s8, 9  * 4(sp)\n"
        "lw s9,  10 * 4(sp)\n"
        "lw s10, 11 * 4(sp)\n"
        "lw s11, 12 * 4(sp)\n"
        "addi sp, sp, 13 * 4\n" // Pop 13, 4-byte registers from stack.
        "ret\n"
        );
}

// All process control structures.
struct process procs[PROCS_MAX];

struct process *create_process(uint32_t pc) {
    //Find unused process control structure.
    struct process *proc = NULL;
    int i;

    for (i = 0; i < PROCS_MAX; i++) {
        if (procs[i].state == PROC_UNUSED) {
            proc = &procs[i];
            break;
        }
    }

    if (!proc) PANIC("no free process slots");

    uint32_t *sp = (uint32_t *) &proc->stack[sizeof(proc->stack)];
    *--sp = 0; // s11
    *--sp = 0; // s10
    *--sp = 0; // s9
    *--sp = 0; // s8
    *--sp = 0; // s7
    *--sp = 0; // s6
    *--sp = 0; // s5
    *--sp = 0; // s4
    *--sp = 0; // s3
    *--sp = 0; // s2
    *--sp = 0; // s1
    *--sp = 0; // s0
    *--sp = (uint32_t) pc; // ra

    // Init PCB struct fields.
    proc->pid = i + 1;
    proc->state = PROC_RUNNABLE;
    proc->sp = (uint32_t) sp;
    return proc;
}
