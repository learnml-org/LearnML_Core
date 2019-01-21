#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace lml
{
	class vector final
	{
	public:
		using iterator = std::vector<double>::iterator;
		using const_iterator = std::vector<double>::const_iterator;
		using reverse_iterator = std::vector<double>::reverse_iterator;
		using const_reverse_iterator = std::vector<double>::const_reverse_iterator;

	public:
		vector() noexcept = default;
		vector(std::size_t dimension);
		vector(const std::vector<double>& vector);
		vector(std::vector<double>&& vector) noexcept;
		vector(const vector& vector);
		vector(vector&& vector) noexcept;
		vector(std::initializer_list<double> ilist);
		~vector() = default;

	public:
		vector& operator=(const std::vector<double>& vector);
		vector& operator=(std::vector<double>&& vector) noexcept;
		vector& operator=(const vector& vector);
		vector& operator=(vector&& vector) noexcept;
		vector& operator=(std::initializer_list<double> ilist);
		friend bool operator==(const vector& a, const vector& b) noexcept;
		friend bool operator!=(const vector& a, const vector& b) noexcept;
		double operator[](std::size_t index) const noexcept;
		double& operator[](std::size_t index) noexcept;
		friend vector operator+(const vector& a, const vector& b);
		friend vector operator-(const vector& a, const vector& b);
		friend vector operator*(double c, const vector& vector);
		friend double operator*(const vector& a, const vector& b) noexcept;
		friend vector operator-(const vector& vector);
		vector& operator+=(const vector& other) noexcept;
		vector& operator-=(const vector& other) noexcept;

	public:
		void clear() noexcept;
		bool empty() const noexcept;
		void swap(vector& other) noexcept;
		std::size_t dimension() const noexcept;
		bool zero() const noexcept;

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

	private:
		std::vector<double> data_;
	};
}