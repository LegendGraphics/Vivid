#ifndef VIVID_COMMON_ENUM_OPERATOR_HPP
#define VIVID_COMMON_ENUM_OPERATOR_HPP

#define ENABLE_ENUM_OPERATOR_IN(T,INT_T) \
namespace vivid{                            \
enum class T;                            \
inline T    operator    &   (T x, T y)      {   return static_cast<T>   (   static_cast<INT_T>(x) & static_cast<INT_T>(y));    }; \
inline T    operator    |   (T x, T y)      {   return static_cast<T>   (   static_cast<INT_T>(x) | static_cast<INT_T>(y));    }; \
inline T    operator    ^   (T x, T y)      {   return static_cast<T>   (   static_cast<INT_T>(x) ^ static_cast<INT_T>(y));    }; \
inline T    operator    ~   (T x)           {   return static_cast<T>   (   ~static_cast<INT_T>(x));                           }; \
inline T&   operator    &=  (T& x, T y)     {   x = x & y;  return x;   }; \
inline T&   operator    |=  (T& x, T y)     {   x = x | y;  return x;   }; \
inline T&   operator    ^=  (T& x, T y)     {   x = x ^ y;  return x;   }; \
}

#define ENABLE_ENUM_OPERATOR(T) ENABLE_ENUM_OPERATOR_IN(T, int)

#endif // VIVID_COMMON_ENUM_OPERATOR_HPP
