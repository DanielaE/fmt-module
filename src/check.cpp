//#define MODULE_WORKS
//#define EXPOSE_MSVC_MODULE_LEAK_HEADER_GUARD_BUG
//#define EXPOSE_MSVC_MODULE_LEAK_GLOBAL_MODULE_BUG
//#define EXPOSE_MSVC_MODULE_ICE

#pragma warning(disable: 4127)
#if !defined(NO_MODULE)

import fmt;
#if !defined(EXPOSE_MSVC_MODULE_LEAK_GLOBAL_MODULE_BUG) && defined(EXPOSE_MSVC_MODULE_ICE)
#include <chrono>
#include <string_view>
#endif
#include <compare>

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

#include "fmt/format.h"
#include "fmt/args.h"
#include "fmt/color.h"
#include "fmt/compile.h"
#include "fmt/locale.h"
#include "fmt/chrono.h"
#include "fmt/printf.h"
#include "fmt/ostream.h"
#include "fmt/ranges.h"
#include "fmt/os.h"

#include "fmt-ct-strings.h"

#include <chrono>
#endif

// provide FMT_* macros using templates from fmt-ct-strings.h
#undef FMT_COMPILE
#define FMT_COMPILE(s) fmt::_compile<s>{}
#undef FMT_STRING
#define FMT_STRING(s) fmt::_string<s>{}

enum class check_color {red, green, blue};

namespace fmt {
template<typename Char>
struct formatter<check_color, Char> : formatter<basic_string_view<Char>, Char> {
    using sv = basic_string_view<Char>;
    template <typename FormatContext>
    auto format(check_color c, FormatContext& ctx) {
        string_view name = "?";
        switch (c) {
            case check_color::red:   name = "red"; break;
            case check_color::green: name = "green"; break;
            case check_color::blue:  name = "blue"; break;
        }
		Char buffer[6];
		Char * p = buffer;
		for (auto Ch : name)
			*(p++) = Ch;
		return formatter<sv, Char>::format(sv{buffer, name.size()}, ctx);
    }
};    
}

#if !defined(NO_MODULE) && defined(EXPOSE_MSVC_MODULE_LEAK_GLOBAL_MODULE_BUG)
// this leaks from the module BMI!
// if you move this to line 56 or above, std::chrono is correctly unknown because <chrono> was never included
auto gNow = std::chrono::system_clock::now();
#error BMI leaks stuff from the global module fragment!
#endif

using namespace fmt::literals; // for udl ""_cf

int main() {
    auto result = fmt::format("{}", 42.0);
    static_assert(sizeof(decltype(result)::value_type) == sizeof(char));
    result = fmt::to_string(42);
    auto greetings = fmt::format("{} {city}!", "Grüße aus", fmt::arg("city", "Nürnberg"));
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    result = "{value}"_format("value"_a = 42);
    greetings = fmt::format("{greeting} {city}!", "greeting"_a = "Grüße aus", fmt::arg("city", "Nürnberg"));
#endif
    fmt::print("{}\n", result);
    fmt::print("{}\n", greetings);
  {
    fmt::memory_buffer out_buffer;
    const auto format_to_result = fmt::format_to(out_buffer, "{}", 42);
  }
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
    result = fmt::format("{}", check_color::blue);
    fmt::format_args args = fmt::make_format_args("hi", result);
    result = fmt::vformat("{},{}", args);
#if defined(NO_MODULE) || _MSC_FULL_VER > 192930031
    result = fmt::format(std::locale(), "{}", 42);
    result = fmt::vformat(std::locale(), "{},{}", args);
#endif
    fmt::vprint("{},{}\n", args);
  }
    const auto fg_check = fg(fmt::rgb(255, 200, 30));
    const auto emphasis_check = fmt::emphasis::italic | fmt::emphasis::bold;
    const auto common_style = bg(fmt::color::dark_slate_gray) | fmt::emphasis::italic;
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    // ICEs in color.h
    fmt::print(fg(fmt::rgb(255, 200, 30)) | common_style, "{} ", "Greetings from");
    fmt::print(fg(fmt::rgb(255, 180, 180)) | common_style, "{}\n", "Nuremberg, Germany!");
#endif
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    result = fmt::format(FMT_STRING("{}"), 42);
    result = fmt::format(FMT_COMPILE("{}"), 42);
    result = fmt::format("{}"_cf, 42);
#endif

    // wchar_t
    auto wresult = fmt::format(L"{}", 42.0);
    static_assert(sizeof(decltype(wresult)::value_type) == sizeof(wchar_t));
    wresult = fmt::to_wstring(42);
    auto wgreetings = fmt::format(L"{} {city}!", L"Greetings from", fmt::arg(L"city", L"Nuremberg, Germany!"));
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    wresult = L"{}"_format(L"value"_a = 42);
    wgreetings = fmt::format(L"{greeting} {city}!", L"greeting"_a = "Greetings from", fmt::arg(L"city", L"Nuremberg, Germany!"));
#endif
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    // ICEs in format.h
    fmt::print(L"\nwide: {}\n", wresult);
    fmt::print(L"wide: {}\n", wgreetings);
#endif
  {
    fmt::wmemory_buffer out_buffer;
    const auto format_to_result = fmt::format_to(out_buffer, L"{}", 42);
  }
#if defined(NO_MODULE) || defined(MODULE_WORKS)
  {
    auto store = fmt::dynamic_format_arg_store<fmt::wformat_context>();
    store.push_back(42);
    store.push_back(1.5f);
    wresult = fmt::vformat(L"{} {}", store);
  }
#endif
  {
    fmt::wstring_view wv{L"wide: bla"};
    wresult = fmt::format(L"{}", check_color::blue);
    fmt::wformat_args args = fmt::make_format_args<fmt::wformat_context>(L"hi", wresult);
    wresult = fmt::vformat(L"{},{}", args);
#if defined(NO_MODULE) || _MSC_FULL_VER > 192930031
    wresult = fmt::format(std::locale(), L"{}", 42);
    wresult = fmt::vformat(std::locale(), L"{},{}", args);
//    fmt::vprint(L"{},{}\n", args);
#endif
  }
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    // ICEs in color.h
    fmt::print(fg(fmt::rgb(255, 200, 30)) | common_style, L"{} ", L"Greetings from");
    fmt::print(fg(fmt::rgb(255, 180, 180)) | common_style, L"{}\n", L"Nuremberg, Germany!");
#endif
#if defined(NO_MODULE) || defined(MODULE_WORKS)
    wresult = fmt::format(FMT_STRING(L"{}"), 42);
    wresult = fmt::format(FMT_COMPILE(L"{}"), 42);
    wresult = fmt::format(L"{}"_cf, 42);
#endif

#if defined(NO_MODULE) || defined(MODULE_WORKS)
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

  auto Now = std::chrono::system_clock::now();
  {
    result = fmt::format("{:%Y-%m-%d %H:%M:%S}", Now);
    wresult = fmt::format(L"{:%Y-%m-%d %H:%M:%S}", Now);
  }
}