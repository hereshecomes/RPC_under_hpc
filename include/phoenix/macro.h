#ifndef __phoenix_MACRO_H__
#define __phoenix_MACRO_H__

#include <string.h>
#include <assert.h>
#include "log.h"

#if defined __GNUC__ || defined __llvm__
#define phoenix_LIKELY(x) __builtin_expect(!!(x), 1)
#define phoenix_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define phoenix_LIKELY(x) (x)
#define phoenix_UNLIKELY(x) (x)
#endif

/// 断言宏封装
#define phoenix_ASSERT(x)                                                                \
    if (phoenix_UNLIKELY(!(x))) {                                                        \
        phoenix_LOG_ERROR(phoenix_LOG_ROOT()) << "ASSERTION: " #x                          \
                                          << "\nbacktrace:\n"                          \
                                          << phoenix::BacktraceToString(100, 2, "    "); \
        assert(x);                                                                     \
    }

/// 断言宏封装
#define phoenix_ASSERT2(x, w)                                                            \
    if (phoenix_UNLIKELY(!(x))) {                                                        \
        phoenix_LOG_ERROR(phoenix_LOG_ROOT()) << "ASSERTION: " #x                          \
                                          << "\n"                                      \
                                          << w                                         \
                                          << "\nbacktrace:\n"                          \
                                          << phoenix::BacktraceToString(100, 2, "    "); \
        assert(x);                                                                     \
    }

#endif
