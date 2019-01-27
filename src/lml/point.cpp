#include <lml/point.hpp>

namespace lml
{
	point::point(std::int32_t x, std::int32_t y) noexcept
		: x(x), y(y)
	{}
	point::point(const point& point) noexcept
		: x(point.x), y(point.y)
	{}

	point& point::operator=(const point& point) noexcept
	{
		x = point.x;
		y = point.y;
		return *this;
	}
	bool operator==(const point& a, const point& b) noexcept
	{
		return a.x == b.x && a.y == b.y;
	}
	bool operator!=(const point& a, const point& b) noexcept
	{
		return a.x != b.x || a.y != b.y;
	}
}