#ifndef VIVID_BASE_ASSERT_H
#define VIVID_BASE_ASSERT_H

#include <iostream>
#include <cassert>

#define mASSERT(expr, msg) assert((expr) ? true : std::cout << msg << std::endl && false)
#define mSTATIC_ASSERT(expr, msg) static_assert((expr) ? true : std::cout << msg << std::endl && false)

#define ASSERT          assert
#define STATIC_ASSERT   static_assert

#endif // VIVID_BASE_ASSERT_H
