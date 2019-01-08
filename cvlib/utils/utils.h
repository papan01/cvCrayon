#ifndef CVCRAYON_UTILS_UTILS_H
#define CVCRAYON_UTILS_UTILS_H

#include <string>
#include <sys/stat.h>
#include <math.h>
#include <memory>
#include <cstdarg>
#include <limits>

#ifdef _MSC_VER
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#include <Windows.h>
#endif

extern const char* color_red;
extern const char* color_green;
extern const char* color_yellow;
extern const char* color_blue;
extern const char* color_magenta;
extern const char* color_cyan;
extern const char* color_reset;

constexpr double EPS = 1e-6;
constexpr double C_EPS = 1e-4;
constexpr double PI = 3.14159265;


#define REP(x, y)	  for (typename std::remove_cv<typename std::remove_reference<decltype(y)>::type>::type x = 0; x < (y); x ++)
#define REPL(x, y, z) for (typename std::remove_cv<typename std::remove_reference<decltype(y)>::type>::type x = y; x < (z); x ++)
#define REPD(x, y, z) for (typename std::remove_cv<typename std::remove_reference<decltype(y)>::type>::type x = y; x >= (z); x --)


namespace utils
{
#ifdef _MSC_VER
	inline int init_ansi_escape_code()
	{
		// Set output mode to handle virtual terminal sequences
		const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut == INVALID_HANDLE_VALUE)
		{
			return GetLastError();
		}

		DWORD dwMode = 0;
		if (!GetConsoleMode(hOut, &dwMode))
		{
			return GetLastError();
		}

		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		if (!SetConsoleMode(hOut, dwMode))
		{
			return GetLastError();
		}

		return GetLastError();
	}
#endif

	std::string term_color(const int k);

	void c_printf(const char* col, const char* fmt, ...);

	void c_fprintf(const char* col, FILE* fp, const char* fmt, ...);

	std::string ssprintf(const char *fmt, ...);

	template<typename T>
	T sqr(const T& x) { return  x * x; }

	template<typename T>
	bool is_between(const T& a, const T& b, const T& c) {
		return ((a >= b) && (a <= c - 1));
	}

	template<typename T>
	bool update_min(T &dest, const T &val) {
		if (val < dest) {
			dest = val; return true;
		}
		return false;
	}

	template<typename T>
	bool update_max(T &dest, const T &val) {
		if (dest < val) {
			dest = val; return true;
		}
		return false;
	}

	template <typename T>
	void free_2_dimension(T** ptr, const int w) {
		if (ptr != nullptr)
			for (auto i = 0; i < w; i++)
				delete[] ptr[i];
		delete[] ptr;
	}

	template <typename T>
	std::shared_ptr<T> create_auto_buf(const size_t len, const bool init_zero = false) {
		std::shared_ptr<T> ret(new T[len], std::default_delete<T[]>());
		if (init_zero)
			memset(ret.get(), 0, sizeof(T) * len);
		return ret;
	}


	inline bool exists_file(const char* name) {
		struct stat buffer;
		return stat(name, &buffer) == 0;
	}

	inline bool endswith(const char* str, const char* suffix) {
		if (!str || !suffix)
			return false;
		auto const l1 = strlen(str), l2 = strlen(suffix);
		if (l2 > l1)
			return false;
		return strncmp(str + l1 - l2, suffix, l2) == 0;
	}

	inline double degree2radian(const double& degree)
	{
		return degree * PI / 180.0;
	}

	inline double radian2degree(const double& radian)
	{
		return radian * 180.0 / PI;
	}
}
#endif // !CV_CRAYON_UTILS_UTILS_H

