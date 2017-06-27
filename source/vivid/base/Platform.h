#ifndef VIVID_BASE_PLATFORM_H
#define VIVID_BASE_PLATFORM_H

namespace vivid 
{

    // CODE FROM OGRE


    /* Initial platform/compiler-related stuff to set.
    */
#define VIVID_PLATFORM_WIN32 1
#define VIVID_PLATFORM_LINUX 2
#define VIVID_PLATFORM_APPLE 3
#define VIVID_PLATFORM_APPLE_VIVID_IOS 4
#define VIVID_PLATFORM_ANDROID 5

#define VIVID_COMPILER_MSVC 1
#define VIVID_COMPILER_GNUC 2

#define VIVID_ARCHITECTURE_32 1
#define VIVID_ARCHITECTURE_64 2

    /* Finds the compiler type and version.
    */
#if defined( _MSC_VER )
#   define VIVID_COMPILER VIVID_COMPILER_MSVC
#   define VIVID_COMP_VER _MSC_VER
#elif defined( __GNUC__ )
#   define VIVID_COMPILER VIVID_COMPILER_GNUC
#   define VIVID_COMP_VER (((__GNUC__)*100) + \
        (__GNUC_MINOR__*10) + \
        __GNUC_PATCHLEVEL__)
#else
#   pragma error "No known compiler. Abort! Abort!"
#endif


    /* Finds the current platform */

#if defined( __WIN32__ ) || defined( _WIN32 )
#   define VIVID_PLATFORM VIVID_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
    // Device                                                     Simulator
    // Both requiring OS version 4.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSVIVID_ION_MIN_REQUIRED__ >= 40000 || __IPHONE_OS_VERSVIVID_ION_MIN_REQUIRED >= 40000
#       define VIVID_PLATFORM VIVID_PLATFORM_APPLE_VIVID_IOS
#   else
#       define VIVID_PLATFORM VIVID_PLATFORM_APPLE
#   endif
#elif defined(__ANDROID__)
#	define VIVID_PLATFORM VIVID_PLATFORM_ANDROID
#else
#   define VIVID_PLATFORM VIVID_PLATFORM_LINUX
#endif

    /* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64)
#   define VIVID_ARCH_TYPE VIVID_ARCHITECTURE_64
#else
#   define VIVID_ARCH_TYPE VIVID_ARCHITECTURE_32
#endif


    //----------------------------------------------------------------------------
    // Windows Settings
#if VIVID_PLATFORM == VIVID_PLATFORM_WIN32

    // If we're not including this from a client build, specify that the stuff
    // should get exported. Otherwise, import it.
#	if defined( VIVID_STATIC_LIB )
    // Linux compilers don't have symbol import/export directives.
#   	define VIVID_DLL_EXPORT
#   	define VIVID_DLL_PRIVATE
#   else
#   	if defined( VIVID_DYNAMIC_LIB )
#       	define VIVID_DLL_EXPORT __declspec( dllexport )
#   	else
#           define VIVID_DLL_EXPORT __declspec( dllimport )
#   	endif
#   	define VIVID_DLL_PRIVATE
#	endif
    // Win32 compilers use _DEBUG for specifying debug builds.
    // for MinGW, we set DEBUG
#   if defined(_DEBUG)
#       define VIVID_DEBUG_MODE 1
#   else
#       define VIVID_DEBUG_MODE 0
#   endif
#endif

    // Linux/Apple/iOs/Android Settings
#if VIVID_PLATFORM == VIVID_PLATFORM_LINUX || VIVID_PLATFORM == VIVID_PLATFORM_APPLE \
    || VIVID_PLATFORM == VIVID_PLATFORM_APPLE_VIVID_IOS || VIVID_PLATFORM == VIVID_PLATFORM_ANDROID

    // Enable GCC symbol visibility
#   if defined( VIVID_GCC_VISIBILITY )
#       define VIVID_DLL_EXPORT  __attribute__ ((visibility("default")))
#       define VIVID_DLL_PRIVATE __attribute__ ((visibility("hidden")))
#   else
#       define VIVID_DLL_EXPORT
#       define VIVID_DLL_PRIVATE
#   endif

    // Unlike the Win32 compilers, Linux compilers seem to use DEBUG for when
    // specifying a debug build.
    // (??? this is wrong, on Linux debug builds aren't marked in any way unless
    // you mark it yourself any way you like it -- zap ???)
#   ifdef DEBUG
#       define VIVID_DEBUG_MODE 1
#   else
#       define VIVID_DEBUG_MODE 0
#   endif

#endif

//    // Integer formats of fixed bit width
//    typedef unsigned int uint32;
//    typedef unsigned short uint16;
//    typedef unsigned char uint8;
//    typedef int int32;
//    typedef short int16;
//    typedef char int8;
//    // define uint64 type
//#if VIVID_COMPILER == VIVID_COMPILER_MSVC
//    typedef unsigned __int64 uint64;
//    typedef __int64 int64;
//#else
//    typedef unsigned long long uint64;
//    typedef long long int64;
//#endif


}

#endif // VIVID_BASE_PLATFORM_H
