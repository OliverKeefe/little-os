#include "common.h"

void putchar(char char_binary);

void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++; // Skips '%' format specifier.

            switch (*fmt) {
                case '\0':
                    putchar('%');
                    goto end;
                case '%':
                    putchar('%');
                    break;
                case 's': {
                    const char *s = va_arg(vargs, const char *);
                    while (*s) {
                        putchar(*s);
                        s++;
                    }
                    break;
                }
                case 'd': {
                    int value = va_arg(vargs, int);
                    unsigned magnitude = value;
                    if (value < 0) {
                        putchar('-');
                        magnitude = -magnitude;
                    }

                    unsigned divisor = 1;
                    while (magnitude / divisor > 9)
                        divisor *= 10;

                    while (divisor > 0) {
                        putchar('0' + magnitude / divisor);
                        magnitude %= divisor;
                        divisor /= 10;
                    }

                    break;
                }
                case 'x': {
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = 7; i >= 0; i--) {
                        unsigned nibble = (value >> (i * 4)) & 0xf;
                        putchar("0123456789abcdef"[nibble]);
                    }
                }
                default: break;
            }
        } else {
            putchar(*fmt);
        }

        fmt++;
    }

    end:
        va_end(vargs);
}

int kvsnprintf(char *buffer, size_t buffer_size, const char *fmt, va_list vargs) {
    size_t buffer_cursor = 0;

    const char *fmt_cursor = fmt;

    const size_t max_return_val = (size_t)(((unsigned int) ~0U ) >> 1);

    if (fmt_cursor == NULL || (buffer == NULL && buffer_size != 0)) {
        return -1;
    }

    #define WRITE_CHAR(char_val) do {                            \
            if (buffer_cursor >= max_return_val) {               \
                return -1;                                       \
            }                                                    \
                                                                 \
            if (buffer != NULL && buffer_size > 0 &&             \
                buffer_cursor < buffer_size - 1) {               \
                buffer[buffer_cursor] = (char)(char_val);        \
            }                                                    \
                                                                 \
            ++buffer_cursor;                                     \
        } while (0)

    while (*fmt_cursor != '\0') {
        if (*fmt_cursor != '%') {
            WRITE_CHAR(*fmt_cursor++);
            continue;
        }

        ++fmt_cursor;

        if (*fmt_cursor == '\0') {
            WRITE_CHAR('%');
            break;
        }

        char conversion_specifier = *fmt_cursor++;

        switch (conversion_specifier) {
            case '%': {
                WRITE_CHAR('%');
                break;
            }

            case 'c': {
                char char_val = (char)va_arg(vargs, int);
                WRITE_CHAR(char_val);
                break;
            }

            case 's': {
                const char *str_val = va_arg(vargs, const char *);

                if (str_val == NULL) {
                    str_val = "(null)";
                }

                while (*str_val != '\0') {
                    WRITE_CHAR(*str_val++);
                }
                break;
            }

            /*
             * %d and %i read a signed integer (%d case will likely need to be changed to support
             * floating points and doubles. With `i`, the sign is printed first (if it's a negative
             * number), and then the magnitude (actual value part of the int) is then printed.
             * 0U is 0x80000000 = 0x80000000 is the unsigned representation of 2147483648.
             */
            case 'd':
            case 'i': {
                int signed_val = va_arg(vargs, int);
                uint32_t magnitude = (uint32_t)signed_val;

                if (signed_val < 0) {
                    WRITE_CHAR('-');
                    magnitude = (uint32_t)(0U - magnitude);
                }
                /*
                 * Convert magnitude to decimal value using a local
                 * reversed digit buffer, then write it backwards.
                 */
                break;
            }

            case 'u': {
                // TODO: Converts unsigned_val to decimal.
                uint32_t unsigned_val = va_arg(vargs, unsigned int);
                break;
            }

            case 'x': {
                // TODO: Convert unsigned_val to hex.
                uint32_t unsigned_val = va_arg(vargs, unsigned int);
                break;
            }

            case 'p': {
                // TODO: Convert address_val to hex.
                void *ptr_val = va_arg(vargs, void *);
                uint32_t address_val = (uint32_t)ptr_val;

                WRITE_CHAR('0');
                WRITE_CHAR('x');
                break;
            }

            default:
                /*
                 * TODO: Return error for unsupported conversion to avoid silently
                 * changing meaning.
                 */
                return -1;
        }
    }

    if (buffer != NULL && buffer_size > 0) {
        size_t null_terminator_idx = buffer_cursor;

        if (null_terminator_idx >= buffer_size) {
            null_terminator_idx = buffer_size - 1;
        }

        buffer[null_terminator_idx] = '\0';
    }

    #undef WRITE_CHAR
    return (int)buffer_cursor;
}

void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = (uint8_t *) dst;

    const uint8_t *s = (const uint8_t *) src;

    while (n--)
        *d++ = *s++;
    return dst;
}

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;

    while (n--)
        *p++ = c;
    return buf;
}

char *strcpy(char *dst, const char *src) {
    char *d = dst;
    while (*src)
        *d++ = *src++;
    *d = '\0';
    return dst;
}