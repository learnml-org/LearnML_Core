#pragma once

#include <cstddef>
#include <vector>

namespace lml
{
	struct matrix_index final
	{
		std::size_t y, x;
	};

	class matrix final
	{
	public:
		matrix() noexcept = default;
		matrix(const matrix& matrix);
		matrix(matrix&& matrix) noexcept;
		~matrix() = default;

	public:
		matrix& operator=(const matrix& matrix);
		matrix& operator=(matrix&& matrix) noexcept;
		friend bool operator==(const matrix& a, const matrix& b) noexcept;
		friend bool operator!=(const matrix& a, const matrix& b) noexcept;
		double operator[](const matrix_index& index) const noexcept;
		double& operator[](const matrix_index& index) noexcept;
		friend matrix operator+(const matrix& a, const matrix& b);
		friend matrix operator-(const matrix& a, const matrix& b);
		friend matrix operator*(double c, const matrix& matrix);
		friend matrix operator*(const matrix& a, const matrix& b);
		matrix& operator+=(const matrix& other) noexcept;
		matrix& operator-=(const matrix& other) noexcept;
		matrix& operator*=(const matrix& other) noexcept;

	public:
		void clear() noexcept;
		bool empty() const noexcept;
		void swap(matrix& matrix) noexcept;
		bool zero() const noexcept;
		std::size_t height() const noexcept;
		std::size_t width() const noexcept;
		std::size_t size() const noexcept;

	private:
		std::vector<double> data_;
		std::size_t height_;
	};
}