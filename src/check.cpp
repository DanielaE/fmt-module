//#define NO_MODULE
//#define UNITY_BUILD
#if !defined(NO_MODULE)

import fmt;

#ifdef EXPOSE_MSVC_MODULE_LEAK_HEADER_GUARD_BUG
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

#else

#pragma warning(disable: 4702)

#include "includes.h"
#define FMT_USE_NONTYPE_TEMPLATE_PARAMETERS 1
#include "fmt/format.h"
#include "fmt/compile.h"
#include "fmt/printf.h"
#include "fmt/color.h"
#include "fmt-ct-strings.h"

#ifdef FMT_WITH_OPTIONAL_COMPONENTS
#   include "fmt/args.h"
#   include "fmt/chrono.h"
#   include "fmt/locale.h"
#   include "fmt/ostream.h"
#   include "fmt/ranges.h"
#endif

#if !defined(FMT_HEADER_ONLY) && defined(UNITY_BUILD)
#include "format.cc"
#endif

#endif

// provide FMT_* macros using templates from fmt-ct-strings.h
#undef FMT_COMPILE
#define FMT_COMPILE(s) fmt::_compile<s>{}
#undef FMT_STRING
#define FMT_STRING(s) fmt::_string<s>{}

using namespace fmt::literals; // for udl ""_cf

int main() {
    auto result = fmt::format("{}", 42.0);
    static_assert(sizeof(decltype(result)::value_type) == sizeof(char));
    auto greetings = fmt::format("{greeting} {city}!", "greeting"_a = "Grüße aus", "city"_a ="Nürnberg");
    fmt::print("{}\n", result);
    fmt::print("{}\n", greetings);
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    fmt::print(fg(fmt::rgb(255, 200, 30)) | fmt::emphasis::italic, "{} ", "Greetings from");
    fmt::print(fg(fmt::rgb(255, 180, 180)) | fmt::emphasis::italic, "{}\n", "Nuremberg, Germany!");
    result = fmt::format(FMT_STRING("{}"), 42);
    result = fmt::format(FMT_COMPILE("{}"), 42);
    result = fmt::format("{}"_cf, 42);
#endif

    // wchar_t
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    auto wresult = fmt::format(L"{}", 42.0);
    static_assert(sizeof(decltype(wresult)::value_type) == sizeof(wchar_t));
    auto wgreetings = fmt::format(L"{} {}!", L"Greetings from", L"Nuremberg");
    fmt::print(L"wide: {}\n", wresult);
    fmt::print(L"wide: {}\n", wgreetings);
    wresult = fmt::format(FMT_STRING(L"{}"), 42);
    wresult = fmt::format(FMT_COMPILE(L"{}"), 42);
#endif

#if defined(NO_MODULE) || defined(MODULE_WORKS)
#include <string_view>
using std::string_view;
    const auto s = fmt::_string<"{}">{};
    const auto c = fmt::_compile<"{}">{};
    const auto u = "{}"_cf;
    constexpr std::string_view reference("{}");
    static_assert(fmt::string_view(s).data() == reference);
    static_assert(fmt::string_view(c).data() == reference);
    static_assert(fmt::string_view(u).data() == reference);

    const auto ws = fmt::_string<L"{}">{};
    const auto wc = fmt::_compile<L"{}">{};
    constexpr std::wstring_view wreference(L"{}");
    static_assert(fmt::wstring_view(ws).data() == wreference);
    static_assert(fmt::wstring_view(wc).data() == wreference);
#endif

}