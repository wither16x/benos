#include "lib/format.h"
#include "lib/variadic.h"
#include "lib/display.h"
#include "lib/string.h"
#include "lib/types.h"

static void reverse_str(char *str)
{
    int ch = 0;
    for (int i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
}

static char *itoa(int n, char *buf, int base)
{
    int i = 0;
    bool_t is_negative = FALSE;

    if (n == 0) {
        buf[i++] = '0';
        buf[i] = '\0';
        return buf;
    }

    /* Numbers in bases other than 10 are considered unsigned */
    if (n < 0 && base == 10) {
        is_negative = TRUE;
        n = -n;
    }

    while (n != 0) {
        int rem = n % base;
        buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        n = n / base;
    }

    if (is_negative)
        buf[i++] = '-';

    buf[i] = '\0';

    reverse_str(buf);
    return buf;
}

void printf(const char *fmt, ...)
{
    char nbuf[32]; /* buffer to store numbers */

    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            putchar(*fmt++);
            continue;
        }

        ++fmt;

        switch (*fmt) {
        case 's':
            print(va_arg(args, const char *));
            break;

        case 'c':
            putchar((char)va_arg(args, int));
            break;

        case 'd':
            print(itoa(va_arg(args, int), nbuf, 10));
            break;

        case 'x':
            print(itoa(va_arg(args, unsigned int), nbuf, 16));
            break;

        default:
            putchar(*fmt);
            break;
        }

        ++fmt;
    }

    va_end(args);
}
