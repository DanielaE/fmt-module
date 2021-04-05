module;

#define MSVC_WORKAROUND_MEMBER_TEMPLATE_INSTANTIATION

// put all implementation-provided headers into the global module fragment
// to prevent attachment to this module
#include "includes.h"
#include <cassert>

export module fmt;

#define FMT_MODULE 1
#define FMT_USE_NONTYPE_TEMPLATE_PARAMETERS 1

// all library-provided declarations and definitions need to be in the
// module purview to attach them to this module
#include "fmt/format.h"
#include "fmt/compile.h"
#include "fmt/printf.h"
#include "fmt/color.h"
#include "fmt-ct-strings.h"

#ifdef FMT_WITH_OPTIONAL_COMPONENTS
#include "fmt/locale.h"
#include "fmt/ostream.h"
#include "fmt/ranges.h"
#include "fmt/chrono.h"
#include "fmt/args.h"
#endif

#ifdef FMT_WITH_OS
#include "fmt/os.h"
#endif

#if !defined(FMT_HEADER_ONLY) && !defined(FMT_USE_IMPLEMENTATION_UNIT)
module : private;

#ifdef MSVC_WORKAROUND_MEMBER_TEMPLATE_INSTANTIATION
#include "fmt/format-inl.h"
#define FMT_STATIC_THOUSANDS_SEPARATOR
#endif
#include "format.cc"
#ifdef FMT_WITH_OS
#include "os.cc"
#endif
#endif
