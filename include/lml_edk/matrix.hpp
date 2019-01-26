#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

namespace lml_edk
{
	struct matrix_index final
	{
		std::size_t y, x;
	};

	class matrix final
	{
	public:
		using iterator = std::vector<double>::iterator;
		using const_iterator = std::vector<double>::const_iterator;
		using reverse_iterator = std::vector<double>::reverse_iterator;
		using const_reverse_iterator = std::vector<double>::const_reverse_iterator;

	public:
		matrix() noexcept = default;
		matrix(std::size_t height, std::size_t width);
		matrix(std::size_t height, std::size_t width, double value);
		matrix(const std::vector<double>& array, std::size_t height);
		matrix(std::vector<double>&& array, std::size_t height);
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

		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;
		const_reverse_iterator crend() const noexcept;

		matrix transpose() const;
		matrix dot(const matrix& other) const;

	private:
		std::vector<double> data_;
		std::size_t height_;
	};

	std::ostream& operator<<(std::ostream& stream, const matrix& matrix);

	matrix transpose(const matrix& matrix);
	matrix dot(const matrix& a, const matrix& b);
}