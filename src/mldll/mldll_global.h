#ifndef MLDLL_GLOBAL_H
#define MLDLL_GLOBAL_H

#include "dllpublic_global.h"

#if defined(MLDLL_LIBRARY)
#  define MLDLL_EXPORT G_DECL_EXPORT
#else
#  define MLDLL_EXPORT G_DECL_IMPORT
#endif

#endif // MLDLL_GLOBAL_H
