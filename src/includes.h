// format.h
#include <cerrno>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

// core.h
#include <cstdio>
#include <cstring>
#include <iterator>
#include <string>
#include <type_traits>
#include <string_view>

// format.h
#if _MSC_VER
#  include <intrin.h>  // _BitScanReverse[64], _BitScanForward[64], _umul128
#endif

// format-inl.h
#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdarg>
#include <exception>
#ifdef _WIN32
#  include <io.h>
#endif
#include <locale>

#ifdef FMT_WITH_OPTIONAL_COMPONENTS
// ostream.h
#include <ostream>

// ranges.h
#include <initializer_list>

// chrono.h
#include <chrono>
#include <ctime>
#include <sstream>

// args.h
#include <functional>
#include <vector>
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
