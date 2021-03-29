#if defined(NAMED_MODULE)
import fmt;
#elif defined(HEADER_MODULE)
import "fmt.hpp";
#else
#include "includes.h"
#define FMT_USE_NONTYPE_TEMPLATE_PARAMETERS 1
#include "format.cc"
#endif

int main() {
	fmt::format("{}", 42);
}