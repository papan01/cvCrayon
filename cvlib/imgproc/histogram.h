#ifndef CVCRAYON_IMGPROC_HISTOGRAM_H
#define CVCRAYON_IMGPROC_HISTOGRAM_H

#include <vector>

#include "mat.h"
#include "../utils/utils.h"

namespace imgproc
{
	/*
	* Histogram
	*/
	std::vector<int> ImageHistogram(const Matf& mat);

	/*
	* Probability density function
	*/
	std::vector<float> ProbabilityDensityFunction(const Matf& mat);

	/*
	* Cumulative distribution function
	*/
	std::vector<float> CumulativeDistributionFunction(const Matf& mat, float& cdf_min);

	/*
	* Histogram equalization
	*/
	Matf HistogramEqualization(const Matf& mat);

	/*
	* Display histogram
	*/
	void HistogramDisplay(const std::vector<int>& histogram);		
}
#endif // !CVCRAYON_IMGPROC_HISTOGRAM_H

