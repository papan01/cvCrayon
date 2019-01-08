#ifndef CVCRAYON_UTILS_DEBUGUTILS_H
#define CVCRAYON_UTILS_DEBUGUTILS_H
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

#ifdef _MSC_VER
#define __attribute__(x)
#endif

#define P(a) std::cout << (a) << std::endl
#define PP(a) std::cout << #a << ": " << (a) << std::endl
#define PA(arr)                    \
	{							   \
		std::cout << #arr << ": "; \
		std::copy(begin(arr), end(arr), std::ostream_iterator<std::remove_reference<decltype(arr)>::type::value_type>(std::cout, " ")); \
		std::cout << std::endl;    \
	} 

#define ASSERT(expr) assert_check((expr), # expr, __FILE__, __FUNCTION__ , __LINE__)
void assert_check(const bool val, const char *expr, const char *file, const char *func, const int line);

#define PRINT_DEBUG(fmt, ...) __print_debug__(__FILE__, __FUNCTION__, __LINE__, fmt, ## __VA_ARGS__)
void __print_debug__(const char *file, const char *func, const int line, const char *fmt, ...)__attribute__((format(printf, 4, 5)));

void error_exit(const char *msg) __attribute__((noreturn));
inline void error_exit(const std::string& s) __attribute__((noreturn));
void error_exit(const std::string& s) {
	error_exit(s.c_str());
}

#endif // !CVCRAYON_UTILS_DEBUGUTILS_H

