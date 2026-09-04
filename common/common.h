#ifndef LITTLE_OS_COMMON_H
#define LITTLE_OS_COMMON_H

typedef int bool;

typedef unsigned char uint8_t;

typedef unsigned short uint16_t;

typedef unsigned int uint32_t;

typedef unsigned long long uint64_t;

typedef uint32_t size_t;

// paddr_t is a type representing physical memory addresses.
typedef uint32_t paddr_t;

// vaddr_t is a type representing virtual memory addresses, equivalent in standard lib is uintptr_t.
typedef uint32_t vaddr_t;

#define true 1
#define false 0

#define NULL ((void *) 0)

// algin_up rounds a value up to the nearest multiple of align. align must be a power of 2.
#define align_up(value, align) __builtin_align_up(value, align)

// is_aligned checks if value is a multiple of align.
#define is_aligned(value, align) __builtin_is_aligned(value, align)

// offsetof returns the offset of a member within a struct.
#define offsetof(type, member) __builtin_offsetof(type, member)


#define va_list  __builtin_va_list
#define va_start __builtin_va_start
#define va_end   __builtin_va_end
#define va_arg   __builtin_va_arg

void *memset(void *buf, char c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
//long sbi_console_putchar(int char_binary);
void printf(const char *fmt, ...);

#endif //LITTLE_OS_COMMON_H
