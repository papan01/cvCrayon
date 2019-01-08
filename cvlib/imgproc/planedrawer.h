#ifndef CVCRAYON_IMGPROC_PLANEDRAWER_H
#define CVCRAYON_IMGPROC_PLANEDRAWER_H

#include <vector>

#include "../utils/utils.h"
#include "mat.h"
#include "color.h"

namespace imgproc
{
	class PlaneDrawer
	{
	public:
		explicit PlaneDrawer(Matf mat) :
			mat(mat) {
			ASSERT(mat.channels() == 3);
		}
		virtual ~PlaneDrawer() {}

		void set_color(Color m_color) { color = m_color; }

		void set_rand_color() {
			auto gen_rand = []() { return (float)rand() / RAND_MAX; };
			set_color(Color(gen_rand(), gen_rand(), gen_rand()));
		}

		//drawing point
		void point(int x, int y) {
			// drawing algorithms are easy to draw out-of-range
			if (!utils::is_between(x, 0, mat.width()) ||
				!utils::is_between(y, 0, mat.height()))
				return;
			float* p = mat.ptr(y, x);
			color.write_to(p);
		}
		void point(Geometry::Coor v) { point(v.x, v.y); }


		//drawing line
		void line(Geometry::Coor s, Geometry::Coor t) { Bresenham(s, t); }
		void line(Geometry::Vec2D s, Geometry::Vec2D t) { 
			line(Geometry::Coor(static_cast<int>(s.x), static_cast<int>(s.y)), 
				Geometry::Coor(static_cast<int>(t.x), static_cast<int>(t.y))); }
		void line(Geometry::Line2D l) { line(l.first, l.second); }
		void line(std::pair<Geometry::Vec2D, Geometry::Vec2D> l) { line(l.first, l.second); }

		//drawing circle
		void circle(Geometry::Coor o, int r);
		void circle(Geometry::Vec2D o, int r) { circle(Geometry::Coor(static_cast<int>(o.x), static_cast<int>(o.y)), r); }

		//drawing cross
		void cross(Geometry::Coor o, int r);
		void cross(Geometry::Vec2D o, int r) { cross(Geometry::Coor(static_cast<int>(o.x), static_cast<int>(o.y)), r); }

		//drawing arrow
		void arrow(Geometry::Coor o, double dir, int r);

		//drawing arrow
		void polygon(const std::vector<Geometry::Coor>& p) {
			for (unsigned int i = 0; i < p.size() - 1; i++)
				line(p[i], p[i + 1]);
			line(p.back(), p.front());
		}
		void polygon(std::vector<Geometry::Vec2D> p) { polygon(vecf_to_polygon(p)); }

	private :
		//Bresenham's line algorithm 
		void Bresenham(Geometry::Coor s, Geometry::Coor t);
	protected:
		Matf mat;
		Color color = Color::BLACK;

		// convert float coordinates to integer coordinate polygon
		std::vector<Geometry::Coor> vecf_to_polygon(std::vector<Geometry::Vec2D> p) {
			std::vector<Geometry::Coor> ret;
			for (auto v : p)
				ret.push_back(Geometry::Coor(static_cast<int>(v.x), static_cast<int>(v.y)));
			return ret;
		}
	};
}


#endif // !CVCRAYON_IMGPROC_PLANEDRAWER_H


