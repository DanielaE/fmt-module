#include <cctype>
#include <cerrno>
#include <climits>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cwchar>

#include <algorithm>
#include <chrono>
#include <compare>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <locale>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#if _MSC_VER
#  include <intrin.h>  // _BitScanReverse[64], _BitScanForward[64], _umul128
#endif
#ifdef _WIN32
#  include <io.h>
#endif

// os.h
#ifdef FMT_WITH_OS
  #include <cstdlib>
  #include <clocale>
  #if __has_include(<winapifamily.h>)
    #include <winapifamily.h>
  #endif
  #if __has_include(<fcntl.h>)
    #include <fcntl.h>
  #endif
#endif
