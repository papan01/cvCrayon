#ifndef CVCRAYON_IMGPROC_IMGPROC_H
#define CVCRAYON_IMGPROC_IMGPROC_H

#include "mat.h"
#include "color.h"

namespace imgproc
{
	/*
	* Using Cimg to display image
	*/
	void Display(const Matf& mat);

	/*
	* RGB to Gray
	* Y'=0.299R'+0.587G'+0.114B'
	*/
	Matf RgbToGray(const Matf& mat);

	/*
	* Fill color
	*/
	void Fill(Matf& mat, const Color& c);
	void Fill(Matf& mat, const float& c);

}

#endif // !CVCRAYON_IMGPROC_IMGPROC_H
