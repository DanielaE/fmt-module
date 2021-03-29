module;

// put all implementation-provided headers into the global module fragment
// to prevent attachment to this module
#include "includes.h"

export module fmt;

#define FMT_MODULE_PURVIEW 1
#define FMT_USE_NONTYPE_TEMPLATE_PARAMETERS 1

// all library-provided declarations and definitions need to be in the
// module purview to attach them to this module
#include "format.cc"
#if 0
#include "fmt/locale.h"
#include "fmt/ostream.h"
#include "fmt/ranges.h"
#include "fmt/chrono.h"
#include "fmt/color.h"
#include "fmt/compile.h"
#include "fmt/printf.h"
#include "fmt/args.h"
#endif

#ifdef FMT_WITH_OS
#include "fmt/os.h"
#include "os.cc"
#endif
