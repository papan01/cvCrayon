#include "imgproc.h"

#include "../utils/utils.h"
#include "planedrawer.h"


#include "CImg.h"

namespace imgproc
{
	void Display(const Matf & mat)
	{
		cimg_library::CImg<unsigned char> img(mat.cols(), mat.rows(), 1, mat.channels());
		if (mat.channels() == 3)
		{
			REP(i, mat.rows())
				REP(j, mat.cols()) {
				img(j, i, 0) = static_cast<unsigned char>((mat.at(i, j, 0) < 0 ? 1 : mat.at(i, j, 0)) * 255);
				img(j, i, 1) = static_cast<unsigned char>((mat.at(i, j, 1) < 0 ? 1 : mat.at(i, j, 1)) * 255);
				img(j, i, 2) = static_cast<unsigned char>((mat.at(i, j, 2) < 0 ? 1 : mat.at(i, j, 2)) * 255);
			}
			img.display();
		}
		else if (mat.channels() == 1)
		{
			REP(i, mat.rows())
				REP(j, mat.cols()) {
				img(j, i, 0) = static_cast<unsigned char>((mat.at(i, j, 0) < 0 ? 1 : mat.at(i, j, 0)) * 255);
			}
			img.display();
		}
	}

	Matf RgbToGray(const Matf & mat)
	{
		ASSERT(mat.channels() == 3);
		Matf ret(mat.height(), mat.width(), 1);
		const float* src = mat.ptr();
		float* dst = ret.ptr();
		int n = mat.pixels();
		int idx = 0;
		for (int i = 0; i < n; ++i) {
			dst[i] = 0.299f * src[idx] + 0.587f * src[idx + 1] + 0.114f * src[idx + 2];
			idx += 3;
		}
		return ret;
	}

	void Fill(Matf & mat, const Color & c)
	{
		float* ptr = mat.ptr();
		int n = mat.pixels();
		REP(i, n) {
			c.write_to(ptr);
			ptr += 3;
		}
	}

	void Fill(Matf & mat, const float& c)
	{
		float* ptr = mat.ptr();
		int n = mat.pixels() * mat.channels();
		REP(i, n) {
			*ptr = c;
			ptr++;
		}
	}
}

