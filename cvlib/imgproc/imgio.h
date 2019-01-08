#ifndef CVCRAYON_IMGPROC_IMGIO_H
#define CVCRAYON_IMGPROC_IMGIO_H

#include "mat.h"

namespace imgproc
{
	Matf read_img(const char* fname);
	void write_rgb(const char* fname, const Matf& mat);
}

#endif //CVCRAYON_IMGPROC_IMGIO_H
