#ifndef COMMON_ENUM_OPERATOR_HPP
#define COMMON_ENUM_OPERATOR_HPP

namespace te
{
    template<class T>                                  
    inline T operator|(T a, T b)                        
    {                                                   
        using utype = std::underlying_type<T>::type;    
        return T(utype(a) | utype(b));                  
    }                                                   

    template<class T>                                   
    inline T operator&(T a, T b)                        
    {                                                   
        using utype = std::underlying_type<T>::type;    
        return T(utype(a) & utype(b));                  
    }
    template<class T>                                   
    inline T operator^(T a, T b) 
    { 
        using utype = std::underlying_type<T>::type;
        return T(utype(a) ^ utype(b));
    }
}
               



#endif // COMMON_ENUM_OPERATOR_HPP