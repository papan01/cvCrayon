/*
* Separable filtering
*/
#ifndef CVCRAYON_IMGPROC_SMOOTHING_H
#define CVCRAYON_IMGPROC_SMOOTHING_H

#include <memory>
#include <vector>
#include "mat.h"
#include "../utils/utils.h"
#include "../utils/timer.h"

namespace imgproc
{
	enum SobelWindowFactor
	{
		Size3x3,
		Size5x5,

	};

	class BaseKernel
	{
	public:		
		float* kernel_horizontal;
		float* kernel_vertical;
		int kernel_window_factor;
	protected:
		std::unique_ptr<float, std::default_delete<float[]>> kernel_horizontal_buf;
		std::unique_ptr<float, std::default_delete<float[]>> kernel_vertical_buf;
	};

	class BaseFilter
	{
	protected:
		//Here is implemented by applying two 1-D convolutions
		template <typename T>
		Mat<T> convolution(const Mat<T>& img, const int& kernel_window_factor,const float* kernel_horizontal, const float* kernel_vertical) const
		{
			ASSERT(img.channels() == 1);
			const int w = img.width(), h = img.height();
			Mat<T> ret(h, w, img.channels());
			const int center = kernel_window_factor / 2;

			std::vector<T> cur_line_mem(center * 2 + std::max(w, h), 0);
			T *cur_line = cur_line_mem.data() + center;

			// apply to columns
			REP(j, w) {
				const T* src = img.ptr(0, j);
				// copy a column of src
				REP(i, h) {
					cur_line[i] = *src;
					src += w;
				}

				// pad the border with border value
				// Using constant padding, computer vision, Szeliski, p114
				T v0 = cur_line[0];
				for (int i = 1; i <= center; i++)
					cur_line[-i] = v0;
				v0 = cur_line[h - 1];
				for (int i = 0; i < center; i++)
					cur_line[h + i] = v0;

				T *dest = ret.ptr(0, j);
				REP(i, h) {
					T tmp{ 0 };
					for (int k = -center; k <= center; k++)
						tmp += cur_line[i + k] * kernel_vertical[k];
					*dest = tmp;
					dest += w;
				}
			}

			// apply to rows
			REP(i, h) {
				T *dest = ret.ptr(i);
				memcpy(cur_line, dest, sizeof(T) * w);
				{
					// pad the border with border value
					// Using constant padding, computer vision, Szeliski, p114
					T v0 = cur_line[0];
					for (int j = 1; j <= center; j++)
						cur_line[-j] = v0;
					v0 = cur_line[w - 1];
					for (int j = 0; j < center; j++)
						cur_line[w + j] = v0;
				}
				REP(j, w) {
					T tmp{ 0 };
					for (int k = -center; k <= center; k++)
						tmp += cur_line[j + k] * kernel_horizontal[k];
					*(dest++) = tmp;
				}
			}
			return ret;
		}
	};

	class GaussCache : public BaseKernel{
	public:	
		GaussCache(const float& sigma, const int& gauss_window_factor);
	};

	class GaussianBlur : BaseFilter
	{
	public:
		GaussianBlur(const float& sigma, const int& gauss_window_factor) : gcache(sigma, gauss_window_factor) {};
		~GaussianBlur() {};

		template <typename T>
		Mat<T> blur(const Mat<T>& img) const
		{
			GUARDED_TIMER;
			return BaseFilter::convolution(img, gcache.kernel_window_factor, gcache.kernel_horizontal,gcache.kernel_vertical);
		}
	private:
		GaussCache gcache;
	};

	class BoxCache : public BaseKernel
	{
	public:
		BoxCache(const int& box_window_factor);
	};

	class BoxFilter : BaseFilter
	{
	public:
		BoxFilter(const int& box_window_factor) : bcache(box_window_factor) {};
		~BoxFilter() {};

		template <typename T>
		Mat<T> blur(const Mat<T>& img) const
		{
			GUARDED_TIMER;
			return BaseFilter::convolution(img, bcache.kernel_window_factor, bcache.kernel_horizontal,bcache.kernel_vertical);
		}

	private:
		BoxCache bcache;
	};

	class SobelCache : public BaseKernel
	{
	public:
		SobelCache(SobelWindowFactor swf = SobelWindowFactor::Size3x3);
	};

	class Sobel : BaseFilter
	{
	public:
		Sobel(SobelWindowFactor swf = SobelWindowFactor::Size3x3) : scache(swf) {}

		template <typename T>
		Mat<T> sobel(const Mat<T>& img)
		{
			ASSERT(img.channels() == 1);
			GUARDED_TIMER;
			Mat<T> Gx = convolution(img, scache.kernel_window_factor, scache.kernel_horizontal, scache.kernel_vertical);
			Mat<T> Gy = convolution(img, scache.kernel_window_factor, scache.kernel_vertical, scache.kernel_horizontal);

			const float* pGx = Gx.ptr();
			const float* pGy = Gy.ptr();

			const int w = img.width(), h = img.height();
			Mat<T> ret(h, w, img.channels());
			float* dst = ret.ptr();
			int n = img.pixels();

			REP(i, n)
			{
				dst[i] = sqrt(pow(pGx[i],2) + pow(pGy[i],2));
			}
			
			return ret;
		}
	private:
		SobelCache scache;
	};

}
#endif // !CVCRAYON_IMGPROC_SMOOTHING_H
