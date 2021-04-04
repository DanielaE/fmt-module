// alternative non-macro-based implementations of compile-time strings
// using exportable C++20 templates with NTTPs similar to {fmt}'s udl ""_cf
#pragma once
FMT_BEGIN_NAMESPACE
FMT_MODULE_EXPORT_BEGIN

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

FMT_MODULE_EXPORT_END
FMT_END_NAMESPACE
