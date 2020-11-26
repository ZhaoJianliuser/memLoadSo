#ifndef CSDLL_GLOBAL_H
#define CSDLL_GLOBAL_H

#include "dllpublic_global.h"

#if defined(CSDLL_LIBRARY)
#  define CSDLL_EXPORT G_DECL_EXPORT
#else
#  define CSDLL_EXPORT G_DECL_IMPORT
#endif

#endif // CSDLL_GLOBAL_H
