#if !defined(NO_MODULE)

import fmt;

#else

#pragma warning(disable: 4702)

#include "includes.h"
#define FMT_USE_NONTYPE_TEMPLATE_PARAMETERS 1
#include "fmt/format.h"
#include "fmt/compile.h"
#include "fmt/printf.h"
#ifdef FMT_WITH_OPTIONAL_COMPONENTS
#	include "fmt/args.h"
#	include "fmt/chrono.h"
#	include "fmt/color.h"
#	include "fmt/locale.h"
#	include "fmt/ostream.h"
#	include "fmt/ranges.h"
#endif
#ifndef FMT_HEADER_ONLY
#include "format.cc"
#endif

FMT_BEGIN_NAMESPACE

template <detail::fixed_string Str>
struct _compile : detail::compiled_string {
	using char_type = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr operator basic_string_view<char_type>() const {
		return {Str.data, sizeof(Str.data) / sizeof(char_type) - 1};
	}
};

template <detail::fixed_string Str>
struct _string : compile_string {
	using char_type = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr operator basic_string_view<char_type>() const {
		return {Str.data, sizeof(Str.data) / sizeof(char_type) - 1};
	}
};

FMT_END_NAMESPACE
#endif

#undef FMT_COMPILE
#define FMT_COMPILE(s) fmt::_compile<s>{}
#undef FMT_STRING
#define FMT_STRING(s) fmt::_string<s>{}

using namespace fmt::literals;

int main() {
	auto result = fmt::format("{} ", 42.0);
	static_assert(sizeof(decltype(result)::value_type) == sizeof(char));
	fmt::print("{}\n", result);
	fmt::print("{}", "Grüße aus Nürnberg!");
#ifdef NO_MODULE
	result = fmt::format(FMT_STRING("{}"), 42);
	result = fmt::format(FMT_COMPILE("{}"), 42);
	const auto x = fmt::_compile<"{}">{};
	const auto y = "{}"_cf;
#endif
	// wchar_t
#ifdef NO_MODULE
	auto wresult = fmt::format(L"{} ", 42.0);
	static_assert(sizeof(decltype(wresult)::value_type) == sizeof(wchar_t));
	wresult = fmt::format(FMT_COMPILE(L"{}"), 42);
	fmt::print(L"{}\n", wresult);
#endif
}