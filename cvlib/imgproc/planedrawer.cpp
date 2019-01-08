#include "planedrawer.h"


namespace imgproc
{
	void PlaneDrawer::circle(Geometry::Coor o, int r)
	{
		int x = 0, y = r,
			d = 1 - r;
		// 1.25 is the same as 1
		while (x <= y) {
			Geometry::Coor dd(x, y);
			point(o + dd); point(o - dd);
			point(o + !dd); point(o - !dd);
			point(o + ~dd); point(o - ~dd);
			point(o + !~dd); point(o - !~dd);
			if (d < 0) d += x + x + 3;
			else d += x + x - y - y + 5, y--;
			x++;
		}
	}
	void PlaneDrawer::cross(Geometry::Coor o, int r)
	{
		line(o - Geometry::Coor(r, r), o + Geometry::Coor(r, r));
		line(o - Geometry::Coor(r, -r), o + Geometry::Coor(r, -r));
	}

	void PlaneDrawer::arrow(Geometry::Coor o, double dir, int r)
	{
		circle(o, 2);
		double dx = r * cos(dir),
			dy = r * sin(dir);
		line(o, o + Geometry::Coor(static_cast<int>(dx), static_cast<int>(dy)));
	}


	void PlaneDrawer::Bresenham(Geometry::Coor s, Geometry::Coor t)
	{
		int deltaX = abs(t.x - s.x), deltaY = abs(t.y - s.y);
		short sx = s.x < t.x ? 1 : -1,
			sy = s.y < t.y ? 1 : -1;
		int e = deltaX - deltaY,
			x = s.x, y = s.y;
		do {
			point(x, y);
			if ((x == t.x) && (y == t.y))
				break;
			int e2 = e + e;
			if (e2 > -deltaY) e -= deltaY, x += sx;
			if (e2 < deltaX) e += deltaX, y += sy;
		} while (1);
	}
}




