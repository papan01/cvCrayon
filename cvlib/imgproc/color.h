#ifndef CVCRAYON_IMGPROC_COLOR_H
#define CVCRAYON_IMGPROC_COLOR_H

#include "../utils/utils.h"
#include "../geometry/vectors.h"

namespace imgproc
{
	class Color : public Geometry::Vector3D<float>
	{
	public:
		constexpr explicit Color(float r = 0, float g = 0, float b = 0) :
			Geometry::Vector3D<float>(r, g, b) {}

		explicit Color(const Geometry::Vector3D<float>& v) :
			Geometry::Vector3D<float>(v) {}

		explicit Color(const float* p) : Geometry::Vector3D<float>(p) {}

		bool black() const
		{
			return is_zero(static_cast<float>(C_EPS));
		}

		void check() const {
			ASSERT(x >= 0 && x <= 1 + std::numeric_limits<double>::epsilon());
			ASSERT(y >= 0 && y <= 1 + std::numeric_limits<double>::epsilon());
			ASSERT(z >= 0 && z <= 1 + std::numeric_limits<double>::epsilon());
		}

		Color operator * (float p) const
		{
			return Color(x * p, y * p, z * p);
		}

		Color operator * (const Color& c) const
		{
			return Color(x * c.x, y * c.y, z * c.z);
		}

		Color operator + (const Color &v) const
		{
			return Color(x + v.x, y + v.y, z + v.z);
		}	
	public:
		static const Color WHITE, BLACK, RED, BLUE, NO;
	};
}
#endif // !CVCRAYON_IMGPROC_COLOR_H
