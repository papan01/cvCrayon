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
		REP(i, n) {
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

	std::vector<Matf> BitPlane(const Matf & mat)
	{
		ASSERT(mat.channels() == 1);
		
		Matf b1(mat.height(), mat.width(), 1), b2(mat.height(), mat.width(), 1), b3(mat.height(), mat.width(), 1),
			 b4(mat.height(), mat.width(), 1), b5(mat.height(), mat.width(), 1), b6(mat.height(), mat.width(), 1),
			 b7(mat.height(), mat.width(), 1), b8(mat.height(), mat.width(), 1);

		const float* src = mat.ptr();
		float* d1 = b1.ptr(), *d2 = b2.ptr(), *d3 = b3.ptr(), 
			  *d4 = b4.ptr(), *d5 = b5.ptr(), *d6 = b6.ptr(),
			  *d7 = b7.ptr(), *d8 = b8.ptr();

		int n = mat.pixels();

		REP(i, n) {
			d1[i] = (static_cast<unsigned char>(src[i] * 255) % 2) / 255.0f;
			d2[i] = ((static_cast<unsigned char>(src[i] * 255) >> 1) % 2) / 255.0f;
			d3[i] = ((static_cast<unsigned char>(src[i] * 255) >> 2) % 2) / 255.0f;
			d4[i] = ((static_cast<unsigned char>(src[i] * 255) >> 3) % 2) / 255.0f;
			d5[i] = ((static_cast<unsigned char>(src[i] * 255) >> 4) % 2) / 255.0f;
			d6[i] = ((static_cast<unsigned char>(src[i] * 255) >> 5) % 2) / 255.0f;
			d7[i] = ((static_cast<unsigned char>(src[i] * 255) >> 6) % 2) / 255.0f;
			d8[i] = ((static_cast<unsigned char>(src[i] * 255) >> 7) % 2) / 255.0f;
		}

		return std::vector<Matf>{ b1, b2, b3, b4, b5, b6, b7, b8 };
	}
}

