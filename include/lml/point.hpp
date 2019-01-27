#pragma once

#include <cstdint>

namespace lml
{
	class point final
	{
	public:
		point() noexcept = default;
		point(std::int32_t x, std::int32_t y) noexcept;
		point(const point& point) noexcept;
		~point() = default;

	public:
		point& operator=(const point& point) noexcept;
		friend bool operator==(const point& a, const point& b) noexcept;
		friend bool operator!=(const point& a, const point& b) noexcept;

	public:
		std::int32_t x, y;
	};
}