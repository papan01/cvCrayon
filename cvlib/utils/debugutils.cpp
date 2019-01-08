#include "debugutils.h"

#include <unordered_map>
#ifdef _MSC_VER
#include <filesystem>
#else
#include <libgen.h>
#endif

#include "utils.h"

void assert_check(const bool val, const char * expr, const char * file, const char * func, const int line)
{
	if (val)
		return;
	utils::c_fprintf(color_red, stderr, "assertion \"%s\" failed, in %s, (%s:%d)\n",
		expr, func, file, line);
	abort();
}

void __print_debug__(const char * file, const char * func, const int line, const char * fmt, ...)
{
	static std::unordered_map<int, std::string> colormap;
	if (!colormap[line].length()) {
		const auto color = std::hash<int>()(line) % 5;
#pragma omp critical
		colormap[line] = utils::term_color(color);
	}

#ifdef _MSC_VER
	std::tr2::sys::path _fbase(file);
	utils::c_fprintf(colormap[line].c_str(), stderr, "[%s@%s:%d] ", func, _fbase.stem().u8string().c_str(), line);
#else
	char *fdup = strdup(file);
	char *_fbase = basename(fdup);
	utils::c_fprintf(colormap[line].c_str(), stderr, "[%s@%s:%d] ", func, _fbase, line);
	free(fdup);
#endif

	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}

void error_exit(const char *msg) {
	utils::c_fprintf(color_red, stderr, "error: %s\n", msg);
	exit(1);
}