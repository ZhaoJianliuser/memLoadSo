#ifndef DLLPUBLIC_GLOBAL_H
#define DLLPUBLIC_GLOBAL_H

#if defined (_MSC_VER)
#  define G_DECL_DEPRECATED __declspec(deprecated)
#  define G_DECL_ALIGN(n) __declspec(align(n))
#  define G_DECL_EXPORT __declspec(dllexport)
#  define G_DECL_IMPORT __declspec(dllimport)

#elif defined(__ARMCC__) || defined(__CC_ARM)
#  define G_DECL_DEPRECATED __attribute__ ((__deprecated__))
#  if defined(__linux__) || defined(__linux)
#    define G_DECL_EXPORT     __attribute__((visibility("default")))
#    define G_DECL_IMPORT     __attribute__((visibility("default")))
#    define G_DECL_HIDDEN     __attribute__((visibility("hidden")))
#  else
#    define G_DECL_EXPORT     __declspec(dllexport)
#    define G_DECL_IMPORT     __declspec(dllimport)
#  endif

#elif defined (__GNUC__)
#  define G_DECL_DEPRECATED __attribute__ ((__deprecated__))
#  define G_DECL_ALIGN(n)   __attribute__((__aligned__(n)))
#  define G_DECL_UNUSED     __attribute__((__unused__))
#  if defined(_WIN32) || defined(WIN32)
#    define G_DECL_EXPORT     __declspec(dllexport)
#    define G_DECL_IMPORT     __declspec(dllimport)
#  else
#    define G_DECL_EXPORT     __attribute__((visibility("default")))
#    define G_DECL_IMPORT     __attribute__((visibility("default")))
#    define G_DECL_HIDDEN     __attribute__((visibility("hidden")))
#  endif

#else
#  error "Compiler not supported"
#endif

#endif // DLLPUBLIC_GLOBAL_H
