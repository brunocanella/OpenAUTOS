#ifndef OS_DEBBUGER
#define OS_DEBBUGER

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80

#define LOGGER_DEBUG(x)
#define LOGGER_ERROR(x)

#elif defined(PLATFORM) &&  PLATFORM == LINUX

#include <stdarg.h>
#include <stdio.h>

void dbg_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void err_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

#define LOGGER_DEBUG(x) do { dbg_printf x; } while (0)
#define LOGGER_ERROR(x) do { err_printf x; } while (0)

#else
#error Platform not declared
#endif



#endif//OS_DEBBUGER