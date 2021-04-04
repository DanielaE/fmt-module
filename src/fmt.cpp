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

FMT_BEGIN_NAMESPACE
export {
template <detail::fixed_string Str>
struct _compile : detail::compiled_string {
  using char_type = std::remove_cvref_t<decltype(Str.data[0])>;
  constexpr operator basic_string_view<char_type>() const {
    return { Str.data, sizeof(Str.data) / sizeof(char_type) - 1 };
  }
};

template <detail::fixed_string Str>
struct _string : compile_string {
  using char_type = std::remove_cvref_t<decltype(Str.data[0])>;
  constexpr operator basic_string_view<char_type>() const {
    return { Str.data, sizeof(Str.data) / sizeof(char_type) - 1 };
  }
};
}
FMT_END_NAMESPACE

#ifdef FMT_WITH_OPTIONAL_COMPONENTS
#include "fmt/locale.h"
#include "fmt/ostream.h"
#include "fmt/ranges.h"
#include "fmt/chrono.h"
#include "fmt/color.h"
#include "fmt/args.h"
#endif

#ifdef FMT_WITH_OS
#include "fmt/os.h"
#endif

module : private;

#ifdef MSVC_WORKAROUND_MEMBER_TEMPLATE_INSTANTIATION
#include "fmt/format-inl.h"
#define FMT_STATIC_THOUSANDS_SEPARATOR
#endif
#include "format.cc"
#ifdef FMT_WITH_OS
#include "os.cc"
#endif
