#include <lml/vector.hpp>

#include <cassert>
#include <utility>

namespace lml
{
	vector::vector(std::size_t dimension)
		: data_(dimension)
	{}
	vector::vector(const std::vector<double>& vector)
		: data_(vector)
	{}
	vector::vector(std::vector<double>&& vector) noexcept
		: data_(std::move(vector))
	{}
	vector::vector(const vector& vector)
		: data_(vector.data_)
	{}
	vector::vector(vector&& vector) noexcept
		: data_(std::move(vector.data_))
	{}
	vector::vector(std::initializer_list<double> ilist)
		: data_(ilist)
	{}

	vector& vector::operator=(const std::vector<double>& vector)
	{
		data_ = vector;
		return *this;
	}
	vector& vector::operator=(std::vector<double>&& vector) noexcept
	{
		data_ = std::move(vector);
		return *this;
	}
	vector& vector::operator=(const vector& vector)
	{
		data_ = vector.data_;
		return *this;
	}
	vector& vector::operator=(vector&& vector) noexcept
	{
		data_ = std::move(vector.data_);
		return *this;
	}
	vector& vector::operator=(std::initializer_list<double> ilist)
	{
		data_ = ilist;
		return *this;
	}
	bool operator==(const vector& a, const vector& b) noexcept
	{
		if (&a == &b) return true;
		if (a.dimension() != b.dimension()) return false;

		for (std::size_t i = 0; i < a.dimension(); ++i)
		{
			if (a[i] != b[i]) return false;
		}

		return true;
	}
	bool operator!=(const vector& a, const vector& b) noexcept
	{
		if (&a == &b) return false;
		if (a.dimension() != b.dimension()) return true;

		for (std::size_t i = 0; i < a.dimension(); ++i)
		{
			if (a[i] != b[i]) return true;
		}

		return false;
	}
	double vector::operator[](std::size_t index) const noexcept
	{
		return data_[index];
	}
	double& vector::operator[](std::size_t index) noexcept
	{
		return data_[index];
	}
	vector operator+(const vector& a, const vector& b)
	{
		return vector(a) += b;
	}
	vector operator-(const vector& a, const vector& b)
	{
		return vector(a) -= b;
	}
	vector operator*(double c, const vector& vector)
	{
		lml::vector result(vector);

		for (double& x : result)
		{
			x *= c;
		}

		return result;
	}
	double operator*(const vector& a, const vector& b) noexcept
	{
		assert(a.dimension() == b.dimension());

		double result = 0.;

		for (std::size_t i = 0; i < a.dimension(); ++i)
		{
			result += a[i] * b[i];
		}

		return result;
	}
	vector operator-(const vector& vector)
	{
		return -1. * vector;
	}
	vector& vector::operator+=(const vector& other) noexcept
	{
		assert(dimension() == other.dimension());

		for (std::size_t i = 0; i < dimension(); ++i)
		{
			data_[i] += other[i];
		}

		return *this;
	}
	vector& vector::operator-=(const vector& other) noexcept
	{
		assert(dimension() == other.dimension());

		for (std::size_t i = 0; i < dimension(); ++i)
		{
			data_[i] -= other[i];
		}

		return *this;
	}

	void vector::clear() noexcept
	{
		data_.clear();
	}
	bool vector::empty() const noexcept
	{
		return data_.empty();
	}
	void vector::swap(vector& other) noexcept
	{
		data_.swap(other.data_);
	}
	std::size_t vector::dimension() const noexcept
	{
		return data_.size();
	}
	bool vector::zero() const noexcept
	{
		for (double component : data_)
		{
			if (component != 0.) return false;
		}

		return true;
	}

	vector::iterator vector::begin() noexcept
	{
		return data_.begin();
	}
	vector::const_iterator vector::begin() const noexcept
	{
		return data_.begin();
	}
	vector::const_iterator vector::cbegin() const noexcept
	{
		return data_.cbegin();
	}
	vector::iterator vector::end() noexcept
	{
		return data_.end();
	}
	vector::const_iterator vector::end() const noexcept
	{
		return data_.end();
	}
	vector::const_iterator vector::cend() const noexcept
	{
		return data_.cend();
	}
	vector::reverse_iterator vector::rbegin() noexcept
	{
		return data_.rbegin();
	}
	vector::const_reverse_iterator vector::rbegin() const noexcept
	{
		return data_.rbegin();
	}
	vector::const_reverse_iterator vector::crbegin() const noexcept
	{
		return data_.crbegin();
	}
	vector::reverse_iterator vector::rend() noexcept
	{
		return data_.rend();
	}
	vector::const_reverse_iterator vector::rend() const noexcept
	{
		return data_.rend();
	}
	vector::const_reverse_iterator vector::crend() const noexcept
	{
		return data_.crend();
	}
}