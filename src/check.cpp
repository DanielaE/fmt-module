//#define NO_MODULE
//#define UNITY_BUILD
//#define MODULE_WORKS

#pragma warning(disable: 4127)
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
#include "fmt/args.h"
#include "fmt/printf.h"
#include "fmt/ostream.h"
#include "fmt/ranges.h"
#include "fmt/color.h"
#include "fmt/chrono.h"
#include "fmt/locale.h"
#include "fmt-ct-strings.h"

#if !defined(FMT_HEADER_ONLY) && defined(UNITY_BUILD)
#include "format.cc"
#endif

#endif

// provide FMT_* macros using templates from fmt-ct-strings.h
#undef FMT_COMPILE
#define FMT_COMPILE(s) fmt::_compile<s>{}
#undef FMT_STRING
#define FMT_STRING(s) fmt::_string<s>{}

enum class check_color {red, green, blue};

namespace fmt {
template<> struct formatter<check_color> : formatter<string_view> {
// parse is inherited
    template <typename FormatContext>
    auto format(check_color c, FormatContext& ctx) {
        string_view name = "?";
        switch (c) {
            case check_color::red:   name = "red"; break;
            case check_color::green: name = "green"; break;
            case check_color::blue:  name = "blue"; break;
        }
        return formatter<string_view>::format(name, ctx);
    }
};    
}

#if !defined(NO_MODULE)
#if defined(MODULE_WORKS)
#include <chrono>
#else
// this leaks from the module BMI!
// if you move this to line 52, std::chrono is correctly unknown
auto gNow = std::chrono::system_clock::now();
#error BMI leaks stuff from the global module fragment! Remove this error directive to check further
#endif
#endif

using namespace fmt::literals; // for udl ""_cf

int main() {
    auto result = fmt::format("{}", 42.0);
    static_assert(sizeof(decltype(result)::value_type) == sizeof(char));
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    result = fmt::to_string(42);
#endif
    result = "{value}"_format("value"_a = 42);
    auto greetings = fmt::format("{greeting} {city}!", "greeting"_a = "Grüße aus", fmt::arg("city", "Nürnberg"));
    fmt::print("{}\n", result);
    fmt::print("{}\n", greetings);
#if defined(NO_MODULE) || defined(MODULE_WORKS)
  {
    fmt::memory_buffer out_buffer;
    const auto format_to_result = fmt::format_to(out_buffer, "{}", 42);
  }
#endif
#if defined(NO_MODULE) || defined(MODULE_WORKS)
  {
    auto store = fmt::dynamic_format_arg_store<fmt::format_context>();
    store.push_back(42);
    store.push_back(1.5f);
    result = fmt::vformat("{} {}", store);
  }
#endif
  {
    fmt::string_view sv{"bla"};
    fmt::formatter<fmt::string_view> fsv;
    fmt::format_args args = fmt::make_format_args("hi", result);
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    result = fmt::format(std::locale(), "{}", 42);
    result = fmt::format("{:>10}", check_color::blue);
    result = fmt::vformat(std::locale(), "{},{}", args);
#endif
    result = fmt::vformat("{},{}", args);
    fmt::vprint("{},{}\n", args);
  }
  {

  }    
    const auto common_style = bg(fmt::color::dark_slate_gray) | fmt::emphasis::italic;
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    fmt::print(fg(fmt::rgb(255, 200, 30)) | common_style, "{} ", "Greetings from");
    fmt::print(fg(fmt::rgb(255, 180, 180)) | common_style, "{}\n", "Nuremberg, Germany!");
    result = fmt::format(FMT_STRING("{}"), 42);
    result = fmt::format(FMT_COMPILE("{}"), 42);
    result = fmt::format("{}"_cf, 42);
#endif

    // wchar_t
  {
    fmt::wstring_view wv{L"wide: bla"};
  }
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    auto wresult = fmt::format(L"{}", 42.0);
    static_assert(sizeof(decltype(wresult)::value_type) == sizeof(wchar_t));
    wresult = fmt::to_wstring(42);
    wresult = L"{}"_format(L"value"_a = 42);
    auto wgreetings = fmt::format(L"{} {}!", L"Greetings from", L"Nuremberg");
    fmt::print(L"wide: {}\n", wresult);
    fmt::print(L"wide: {}\n", wgreetings);
    wresult = fmt::format(FMT_STRING(L"{}"), 42);
    wresult = fmt::format(FMT_COMPILE(L"{}"), 42);
#endif

#if defined(NO_MODULE) || defined(MODULE_WORKS)
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

  {
    auto Now = std::chrono::system_clock::now(); // this leaks from the module BMI!
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    result = fmt::format("{:%Y-%m-%d %H:%M:%S}", Now);
    wresult = fmt::format(L"{:%Y-%m-%d %H:%M:%S}", Now);
#endif
  }
}