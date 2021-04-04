module;
#define MSVC_WORKAROUND_EXTERN_C

// put all implementation-provided headers into the global module fragment
// to prevent attachment to this module
#include "includes.h"
#ifdef MSVC_WORKAROUND_EXTERN_C
#include "fwd-windows.h"
#endif
#include <cassert>

module fmt;

#ifdef EXPOSE_MSVC_MODULE_EXTERN_C_BUG
extern "C" int foo_extern_C(int);
#endif

#define FMT_MODULE 1
#define FMT_MODULE_IMPLEMENTATION 1 // retain only preprocessor declarations from core.h and format.h
#define FMT_USE_NONTYPE_TEMPLATE_PARAMETERS 1

#ifndef EXPOSE_MSVC_MODULE_LEAK_HEADER_GUARD_BUG
#undef FMT_CORE_H_
#undef FMT_FORMAT_H_
#undef FMT_FORMAT_INL_H_
#else
#ifdef FMT_CORE_H_
#error FMT_CORE_H_ is defined
#endif
#ifdef FMT_FORMAT_H_
#error FMT_FORMAT_H_ is defined
#endif
#ifdef FMT_FORMAT_INL_H_
#error FMT_FORMAT_INL_H_ is defined
#endif
#endif

#ifdef EXPOSE_MSVC_MODULE_NAMESPACE_BUG
/* this expands to 
namespace fmt { inline namespace v7 {
namespace detail {
}
} }
*/
#include "fmt/core.h"
#else

#ifdef EXPOSE_MSVC_MODULE_ICE
namespace fmt { inline namespace v7 {
} }
#endif

// all library-provided declarations and definitions need to be in the
// module purview to attach them to this module
#include "format.cc" // transitively includes format-inl.h

#endif
#ifdef FMT_WITH_OS
#include "os.cc"
#endif
