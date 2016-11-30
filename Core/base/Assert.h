#ifndef ASSERT_MACROS_H
#define ASSERT_MACROS_H

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

#endif