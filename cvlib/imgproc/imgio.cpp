#include "imgio.h"

#include <vector>

#include "CImg.h"
#include "lodepng.h"
#include "..\utils\utils.h"

namespace
{
	void write_png(const char* fname, const imgproc::Matf& mat)
	{
		int n = mat.pixels();
		std::vector<unsigned char> img(n * 4);
		const float* p = mat.ptr();
		unsigned char* data = img.data();
		REP(i, n) {
			data[0] = static_cast<unsigned char>((p[0] < 0 ? 1 : p[0]) * 255);
			data[1] = static_cast<unsigned char>((p[1] < 0 ? 1 : p[1]) * 255);
			data[2] = static_cast<unsigned char>((p[2] < 0 ? 1 : p[2]) * 255);
			data[3] = 255;
			data += 4; p += 3;
		}
		unsigned error = lodepng::encode(fname, img, mat.width(), mat.height());
		if (error)
			error_exit(utils::ssprintf(
				"png encoder error %u: %s", error, lodepng_error_text(error)));
	}

	imgproc::Matf read_png(const char* fname)
	{
		std::vector<unsigned char> img;
		unsigned w, h;
		unsigned error = lodepng::decode(img, w, h, fname);
		if (error)
			error_exit(utils::ssprintf(
				"png encoder error %u: %s", error, lodepng_error_text(error)));
		imgproc::Matf mat(h, w, 3);
		unsigned npixel = w * h;
		float* p = mat.ptr();
		unsigned char* data = img.data();
		REP(i, npixel) {
			*(p++) = static_cast<float>(*(data++) / 255.0);
			*(p++) = static_cast<float>(*(data++) / 255.0);
			*(p++) = static_cast<float>(*(data++) / 255.0);
			data++;	// rgba
		}
		return mat;
	}
}



namespace imgproc
{
	Matf read_img(const char * fname)
	{
		if (!utils::exists_file(fname))
			error_exit(utils::ssprintf("File \"%s\" not exists!", fname));
		if (utils::endswith(fname, ".png"))
			return read_png(fname);
		cimg_library::CImg<unsigned char> img(fname);
		ASSERT(img.spectrum() == 3 || img.spectrum() == 1);
		Matf mat(img.height(), img.width(), 3);
		if (img.spectrum() == 3) {
			REP(i, mat.rows())
				REP(j, mat.cols()) {
				mat.at(i, j, 0) = static_cast<float>(img(j, i, 0) / 255.0);
				mat.at(i, j, 1) = static_cast<float>(img(j, i, 1) / 255.0);
				mat.at(i, j, 2) = static_cast<float>(img(j, i, 2) / 255.0);
			}
		}
		else {
			REP(i, mat.rows())
				REP(j, mat.cols()) {
				mat.at(i, j, 0) = mat.at(i, j, 1) = mat.at(i, j, 2) = img(j, i);
			}
		}
		ASSERT(mat.rows() > 1 && mat.cols() > 1);
		return mat;
	}

	void write_rgb(const char * fname, const Matf & mat)
	{
		ASSERT(mat.channels() == 3);
		if (utils::endswith(fname, ".png")) {
			write_png(fname, mat);
			return;
		}
		cimg_library::CImg<unsigned char> img(mat.cols(), mat.rows(), 1, 3);
		REP(i, mat.rows())
			REP(j, mat.cols()) {
			img(j, i, 0) = static_cast<unsigned char>((mat.at(i, j, 0) < 0 ? 1 : mat.at(i, j, 0)) * 255);
			img(j, i, 1) = static_cast<unsigned char>((mat.at(i, j, 1) < 0 ? 1 : mat.at(i, j, 1)) * 255);
			img(j, i, 2) = static_cast<unsigned char>((mat.at(i, j, 2) < 0 ? 1 : mat.at(i, j, 2)) * 255);
		}
		img.save(fname);
	}
}

