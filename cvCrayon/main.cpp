#include <iostream>
#include <vector>

#include <imgproc/imgio.h>
#include <imgproc/imgproc.h>
#include <imgproc/histogram.h>
#include <imgproc/planedrawer.h>
#include <geometry/vectors.h>

using namespace imgproc;

int main(int argc, char** argv)
{
	auto src = imgproc::read_img("Lena.png");	
	auto gray = imgproc::RgbToGray(src);
	auto src_hist = imgproc::ImageHistogram(gray);
	imgproc::HistogramDisplay(src_hist);
	imgproc::Display(gray);

	auto histE = imgproc::HistogramEqualization(gray);
	auto histE_hist = imgproc::ImageHistogram(histE);
	imgproc::HistogramDisplay(histE_hist);
	imgproc::Display(histE);

	return 0;
}

