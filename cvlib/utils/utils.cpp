#include "utils.h"
#include <sstream>

const char* color_red = "\x1b[31m";
const char* color_green = "\x1b[32m";
const char* color_yellow = "\x1b[33m";
const char* color_blue = "\x1b[34m";
const char* color_magenta = "\x1b[35m";
const char* color_cyan = "\x1b[36m";
const char* color_reset = "\x1b[0m";

namespace utils
{

	std::string term_color(const int k)
	{
		// k = 0 ~ 4
		std::ostringstream ss;
		ss << "\x1b[3" << k + 2 << "m";
		return ss.str();
	}

	void c_printf(const char * col, const char * fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		printf("%s", col);
		vprintf(fmt, ap);
		printf(color_reset);
		va_end(ap);
	}

	void c_fprintf(const char * col, FILE * fp, const char * fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		fprintf(fp, "%s", col);
		vfprintf(fp, fmt, ap);
		fprintf(fp, color_reset);
		va_end(ap);
	}

	std::string ssprintf(const char * fmt, ...)
	{
		int size = 100;
		char* buffer = new char[size];
		std::string ret;
		va_list ap;
		while (true)
		{
			va_start(ap, fmt);
			const int n = vsnprintf(buffer, size, fmt, ap);
			va_end(ap);

			if (n < 0)
			{
				delete[] buffer;
				return "";
			}

			if (n < size)
			{
				ret = buffer;
				delete[] buffer;
				return ret;
			}

			size = n + 1;
			delete[] buffer;
			buffer = new char[size];
		}
	}
}



