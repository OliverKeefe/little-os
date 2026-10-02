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

// PAGE_SIZE defines the size of a page, in this case 4KB.
#define PAGE_SIZE 4096

#define va_list  __builtin_va_list
#define va_start __builtin_va_start
#define va_end   __builtin_va_end
#define va_arg   __builtin_va_arg

void *memset(void *buf, char c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
//long sbi_console_putchar(int char_binary);

/**
 * kvsnprintf is the kernel specific vsnprintf implementation. It formats a string into a bounded buffer.
 *
 * `k` - Denotes the kernel specific scope of this function (not to be confused with libc's `vsnprintf()` function.
 *
 * `v` - Accepts a variadic argument list `va_list`.
 *
 * `snprintf` - Formats into a bounded buffer.
 *
 * @param buffer Pointer to the destination buffer, may be null when buffer_size == 0, allowing function to calculate
 * the required length without storing anything.
 * @param buffer_size Total buffer capacity, including the terminating '\0'.
 * @param fmt The format string.
 * @param vargs The list of variadic arguments, the caller has already started this list with `va_start()`.
 * @return int value of the full number of characters that would have been written, excluding terminator.
 */
int kvsnprintf(char *buffer, size_t buffer_size, const char *fmt, va_list vargs);

void printf(const char *fmt, ...);

#endif //LITTLE_OS_COMMON_H
