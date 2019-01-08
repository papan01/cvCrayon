#ifndef CVCRAYON_GEOMETRY_VECTORS_H
#define CVCRAYON_GEOMETRY_VECTORS_H

#include <math.h>
#include <algorithm>
#include <limits>
#include "../utils/debugutils.h"

#undef max
#undef min

namespace Geometry
{
	template <typename T>
	class Vector3D
	{
	public:
		T x, y, z;
	public:
		constexpr explicit Vector3D(const T& m_x = 0, const T& m_y = 0, const T& m_z = 0) :
			x(m_x), y(m_y), z(m_z) {}

		Vector3D(const Vector3D &p0, const Vector3D &p1) :
			x(p1.x - p0.x), y(p1.y - p0.y), z(p1.z - p0.z) {}

		explicit Vector3D(const T* p) :
			x(p[0]), y(p[1]), z(p[2]) {}

		static Vector3D max()
		{
			return Vector3D(std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
		}

		static Vector3D infinity()
		{
			return Vector3D(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
		}

		static Vector3D zero()
		{
			return Vector3D(0, 0, 0);
		}

		static Vector3D NaN() { return Vector3D(NAN, NAN, NAN); }

		void write_to(T* p) const
		{
			p[0] = x, p[1] = y, p[2] = z;
		}

		T get_max() const
		{
			return std::max(x, std::max(y, z));
		}

		T get_min() const
		{
			return std::min(x, std::min(y, z));
		}

		T get_abs_max()
		{
			return max(fabs(x), max(fabs(y), fabs(z)));
		}

		T sqr() const
		{
			return x * x + y * y + z * z;
		}

		// |v|: length
		T length() const
		{
			return static_cast<T>(sqrt(sqr()));
		}

		T dot(const Vector3D &v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		Vector3D cross(const Vector3D &v) const
		{
			return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}

		//^v = v / |v|
		void normalize() {
			T m = 1 / length();
			*this *= m;
			ASSERT(std::isnormal(m));
		}

		Vector3D get_normalized() const
		{
			Vector3D ret(*this); ret.normalize(); return ret;
		}

		bool is_zero(T threshold = EPS) const
		{
			return fabs(x) < threshold && fabs(y) < threshold && fabs(z) < threshold;
		}

		bool is_positive(T threshold = EPS) const
		{
			return x > threshold && y > threshold && z > threshold;
		}

		bool isNaN() const { return std::isnan(x); }

		void update_min(const Vector3D &v) {
			utils::update_min(x, v.x);
			utils::update_min(y, v.y);
			utils::update_min(z, v.z);
		}

		void update_max(const Vector3D &v) {
			utils::update_max(x, v.x);
			utils::update_max(y, v.y);
			utils::update_max(z, v.z);
		}

		//need normalization
		//r = d - 2(d ¡C ^n)^n   => r = d - ((2d¡Cn)/(|n|**2))n 
		Vector3D reflection(const Vector3D& v) const {
			ASSERT(fabs(v.sqr() - 1) < EPS && (sqr() - 1 < EPS));
			return *this * 2 * dot(v) - v;
		}

		Vector3D& operator = (const Vector3D& v)
		{
			x = v.x, y = v.y, z = v.z; return *this;
		}

		Vector3D operator+(const Vector3D &v) const
		{
			return Vector3D(x + v.x, y + v.y, z + v.z);
		}

		Vector3D& operator+=(const Vector3D &v)
		{
			x += v.x; y += v.y; z += v.z; return *this;
		}

		Vector3D operator-(const Vector3D &v) const
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
		}

		Vector3D operator-() const
		{
			return Vector3D(-x, -y, -z);
		}

		Vector3D& operator-=(const Vector3D &v)
		{
			x -= v.x; y -= v.y; z -= v.z; return *this;
		}

		Vector3D operator*(const T& p) const
		{
			return Vector3D(x * p, y * p, z * p);
		}

		Vector3D& operator*=(const T& p)
		{
			x *= p; y *= p; z *= p; return *this;
		}

		Vector3D operator/(const T& p) const
		{
			return *this * (1.0 / p);
		}

		Vector3D& operator/=(const T& p)
		{
			x /= p; y /= p; z /= p; return *this;
		}

		bool operator==(const Vector3D &v) const
		{
			return fabs(x - v.x) < EPS && fabs(y - v.y) < EPS && fabs(z - v.z) < EPS;
		}

		bool operator != (const Vector3D &v) const
		{
			return fabs(x - v.x) >= EPS || fabs(y - v.y) >= EPS || fabs(z - v.z) >= EPS;
		}

		friend std::ostream& operator<<(std::ostream &os, const Vector3D& vec)
		{
			return os << vec.x << " " << vec.y << " " << vec.z;
		}
	};

	template <typename T>
	class Vector2D
	{
	public:
		T x, y;
	public:
		constexpr explicit Vector2D(const T& m_x = 0, const T& m_y = 0) :
			x(m_x), y(m_y) {}
		Vector2D(const Vector2D &p0, const Vector2D &p1) :
			x(p1.x - p0.x), y(p1.y - p0.y) {}

		explicit Vector2D(const T* p) :
			x(p[0]), y(p[1]) {}

		static Vector2D max()
		{
			return Vector2D(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
		}

		static Vector2D infinity()
		{
			return Vector2D(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
		}

		static Vector2D zero() { return Vector2D(0, 0); }

		static Vector2D NaN() { return Vector2D(NAN, NAN); }

		void write_to(T* p) const
		{
			p[0] = x, p[1] = y;
		}

		T get_max() const
		{
			return std::max(x, y);
		}

		T get_min() const
		{
			return std::min(x, y);
		}

		T get_abs_max()
		{
			return max(fabs(x), fabs(y));
		}

		T sqr() const
		{
			return x * x + y * y;
		}

		// |v|: length
		T length() const
		{
			return static_cast<T>(sqrt(sqr()));
		}

		T dot(const Vector2D &v) const
		{
			return x * v.x + y * v.y;
		}

		//^v = v / |v|
		void normalize() {
			T m = 1 / length();
			*this *= m;
			ASSERT(std::isnormal(m));
		}

		Vector2D get_normalized() const
		{
			Vector2D ret(*this); ret.normalize(); return ret;
		}

		bool is_zero(T threshold = EPS) const
		{
			return fabs(x) < threshold && fabs(y) < threshold;
		}

		bool is_positive(T threshold = EPS) const
		{
			return x > threshold && y > threshold;
		}

		bool isNaN() const { return std::isnan(x); }

		void update_min(const Vector2D &v) {
			utils::update_min(x, v.x);
			utils::update_min(y, v.y);
		}

		void update_max(const Vector2D &v) {
			utils::update_max(x, v.x);
			utils::update_max(y, v.y);
		}

		//need normalization
		//r = d - 2(d ¡C ^n)^n   => r = d - ((2d¡Cn)/(|n|**2))n 
		Vector2D reflection(const Vector2D& v) const {
			auto a = v.sqr();
			auto b = sqr();
			ASSERT(fabs(v.sqr() - 1) < EPS && (sqr() - 1 < EPS));
			return *this * 2 * dot(v) - v;
		}

		Vector2D& operator=(const Vector2D& v)
		{
			x = v.x, y = v.y; return *this;
		}

		Vector2D operator+(const Vector2D &v) const
		{
			return Vector2D(x + v.x, y + v.y);
		}

		Vector2D& operator+=(const Vector2D &v)
		{
			x += v.x; y += v.y; return *this;
		}

		Vector2D operator-(const Vector2D &v) const
		{
			return Vector2D(x - v.x, y - v.y);
		}

		Vector2D operator-() const
		{
			return Vector2D(-x, -y);
		}

		Vector2D& operator-=(const Vector2D &v)
		{
			x -= v.x; y -= v.y; return *this;
		}

		Vector2D operator*(const T& p) const
		{
			return Vector2D(x * p, y * p);
		}

		Vector2D& operator*=(const T& p)
		{
			x *= p; y *= p; return *this;
		}

		Vector2D operator/(const T& p) const
		{
			return *this * (1.0 / p);
		}

		Vector2D& operator/=(const T& p)
		{
			x /= p; y /= p; return *this;
		}

		// take negative of the second component
		Vector2D operator ! () const
		{
			return Vector2D(x, -y);
		}

		// swap the two component
		Vector2D operator ~ () const
		{
			return Vector2D(y, x);
		}

		bool operator==(const Vector2D &v) const
		{
			return fabs(x - v.x) < EPS && fabs(y - v.y) < EPS;
		}

		bool operator != (const Vector2D &v) const
		{
			return fabs(x - v.x) >= EPS || fabs(y - v.y) >= EPS;
		}

		friend std::ostream& operator<<(std::ostream &os, const Vector2D& vec)
		{
			return os << vec.x << " " << vec.y;
		}
	};

	using Vec3D = Vector3D<double>;
	using Vec2D = Vector2D<double>;
	using Coor = Vector2D<int>;
	using Line2D = std::pair<Geometry::Coor, Geometry::Coor>;
}
#endif // !CVCRAYON_GEOMETRY_VECTORS_H
