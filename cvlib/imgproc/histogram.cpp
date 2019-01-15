#include "histogram.h"
#include "planedrawer.h"
#include "imgproc.h"

namespace imgproc
{
	std::vector<int> ImageHistogram(const Matf& mat)
	{
		ASSERT(mat.channels() == 1);
		std::vector<int> ret(256);
		REP(i, mat.rows())
			REP(j, mat.cols()) {
			ret[static_cast<unsigned char>((mat.at(i, j, 0) < 0 ? 1 : mat.at(i, j, 0)) * 255)]++;
		}
		return ret;
	}

	std::vector<float> ProbabilityDensityFunction(const Matf& mat)
	{
		ASSERT(mat.channels() == 1);
		auto hist = ImageHistogram(mat);
		std::vector<float> ret(256);
		auto size = mat.pixels();
		REP(i, hist.size())
			ret[i] = hist[i] / static_cast<float>(size);

		return ret;
	}

	std::vector<float> CumulativeDistributionFunction(const Matf& mat,float & cdf_min)
	{
		ASSERT(mat.channels() == 1);
		auto pdf = ProbabilityDensityFunction(mat);
		std::vector<float> ret(256);
		ret[0] = pdf[0];
		REPL(i, 1, static_cast<int>(pdf.size()))
		{
			ret[i] = pdf[i] + ret[i - 1];
			if (ret[i] < cdf_min && ret[i] > 0.0)
				cdf_min = ret[i];
		}
		return ret;
	}

	Matf HistogramEqualization(const Matf& mat)
	{
		ASSERT(mat.channels() == 1);
		float cdf_min = 1000.f;
		auto cdf = CumulativeDistributionFunction(mat,cdf_min);
		// Compute scale
		float scale = (256.f - 1.f) / (mat.pixels() - cdf_min);
		std::vector<int> histogram(256, 0);
		REP(i, cdf.size())
		{
			histogram[i] = std::max(0, std::min(static_cast<int>((cdf[i] - cdf_min) * mat.pixels() / (mat.pixels() - (cdf_min * mat.pixels())) * 255), 255));
		}

		Matf ret(mat.height(), mat.width(), 1);
		const float* src = mat.ptr();
		float* dst = ret.ptr();
		int n = mat.pixels();
		for (int i = 0; i < n; ++i) {
			dst[i] = histogram[static_cast<int>(src[i] * 255)] / 255.f;
		}
		return ret;
	}

	void HistogramDisplay(const std::vector<int>& histogram)
	{
		int hist_w = 1024, hist_h = 720;
		int bin_w = hist_w / 256;

		Matf histImage(hist_h, hist_w, 3);
		Fill(histImage, Color::BLACK);

		auto max = *std::max_element(histogram.begin(), histogram.end());

		PlaneDrawer p(histImage);
		p.set_rand_color();

		REP(i, 256)
		{
			auto hist = round(histogram[i] / static_cast<double>(max) * histImage.rows());
			p.line(Geometry::Vec2D(bin_w * i, hist_h), Geometry::Vec2D(bin_w * i, hist_h - hist));
		}

		Display(histImage);
	}
}