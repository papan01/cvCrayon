#include "smoothing.h"

namespace imgproc
{
	GaussCache::GaussCache(const float& sigma, const int& gauss_window_factor)
	{
		kernel_window_factor = static_cast<int>(ceil(0.3 * (sigma / 2 - 1) + 0.8) * gauss_window_factor);

		if (kernel_window_factor % 2 == 0) kernel_window_factor++;
		kernel_horizontal_buf.reset(new float[kernel_window_factor]);
		kernel_vertical_buf.reset(new float[kernel_window_factor]);

		const int center = kernel_window_factor / 2;
		kernel_horizontal = kernel_horizontal_buf.get() + center;
		kernel_vertical = kernel_vertical_buf.get() + center;

		kernel_horizontal[0] = 1;

		float exp_coeff = -1.0f / (sigma * sigma * 2.0f), wsum = 1.0f;

		for (int i = 1; i <= center; i++)
		{
			wsum += (kernel_horizontal[i] = exp(i * i * exp_coeff)) * 2;
			kernel_vertical[i] = kernel_horizontal[i];
		}
			
		float fac = 1.0f / wsum;
		kernel_horizontal[0] = fac;
		kernel_vertical[0] = fac;

		for (int i = 1; i <= center; i++)
		{
			kernel_horizontal[-i] = (kernel_horizontal[i] *= fac);
			kernel_vertical[-i] = (kernel_vertical[i] *= fac);
			std::cout << kernel_horizontal[-i] << " " << kernel_horizontal[i] << std::endl;
			std::cout << kernel_vertical[-i] << " " << kernel_vertical[i] << std::endl;
		}
			

	}

	BoxCache::BoxCache(const int & box_window_factor)
	{
		kernel_window_factor = box_window_factor;

		if (kernel_window_factor % 2 == 0) kernel_window_factor++;
		kernel_horizontal_buf.reset(new float[kernel_window_factor]);
		kernel_vertical_buf.reset(new float[kernel_window_factor]);

		const int center = kernel_window_factor / 2;
		kernel_horizontal = kernel_horizontal_buf.get() + center;
		kernel_vertical = kernel_vertical_buf.get() + center;

		float fac = 1.0f / static_cast<float>(kernel_window_factor);
		kernel_horizontal[0] = fac;
		kernel_vertical[0] = fac;

		for (int i = 1; i <= center; i++)
		{
			kernel_horizontal[-i] = kernel_horizontal[i] = fac;
			kernel_vertical[-i] = kernel_vertical[i] = fac;
		}		
	}

	SobelCache::SobelCache(SobelWindowFactor swf)
	{	
		if (swf == SobelWindowFactor::Size3x3)
		{
			kernel_window_factor = 3;
			kernel_horizontal_buf.reset(new float[kernel_window_factor]);
			kernel_vertical_buf.reset(new float[kernel_window_factor]);
			const int center = kernel_window_factor / 2;

			kernel_vertical = kernel_vertical_buf.get() + center;
			kernel_vertical[-1] = 1.0f, kernel_vertical[0] = 2.0f, kernel_vertical[1] = 1.0f;
			
			kernel_horizontal = kernel_horizontal_buf.get() + center;
			kernel_horizontal[-1] = 1.0f, kernel_horizontal[0] = 0.0f, kernel_horizontal[1] = -1.0f ;
		}
		else if (swf == SobelWindowFactor::Size5x5)
		{
			kernel_window_factor = 5;
			kernel_horizontal_buf.reset(new float[kernel_window_factor]);
			kernel_vertical_buf.reset(new float[kernel_window_factor]);
			const int center = kernel_window_factor / 2;

			kernel_vertical = kernel_vertical_buf.get() + center;
			kernel_vertical[-2] = 1, kernel_vertical[-1] = 4, kernel_vertical[0] = 6, kernel_vertical[1] = 4, kernel_vertical[2] = 1;

			kernel_horizontal = kernel_horizontal_buf.get();
			kernel_horizontal[-2] = 1, kernel_horizontal[-1] = 2, kernel_horizontal[0] = 0, kernel_horizontal[1] = -2, kernel_horizontal[2] = -1;
		}	
	}
}

