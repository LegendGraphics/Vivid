
#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#include <assert.h>
#include <iostream>

#define TE_ERROR(msg) \
    std::cerr << msg << std::endl

#define TE_LOG(msg, ...) ( \
    printf((msg), ##__VA_ARGS__), \
    std::cout << std::endl \
    )

#define TE_ASSERT(expr, msg) \
    assert((expr) ? true : TE_ERROR(msg) && false)

#define TE_MAX(a, b) ((a)>(b)?(a):(b))
#define TE_MIN(a, b) ((a)<(b)?(a):(b))


#endif // COMMON_MACROS_H