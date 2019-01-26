#include <lml_edk/matrix.hpp>

#include <cassert>
#include <utility>

namespace lml_edk
{
	matrix::matrix(std::size_t height, std::size_t width)
		: data_(height * width), height_(height)
	{}
	matrix::matrix(std::size_t height, std::size_t width, double value)
		: data_(height * width, value), height_(height)
	{}
	matrix::matrix(const std::vector<double>& array, std::size_t height)
		: data_(array), height_(height)
	{}
	matrix::matrix(std::vector<double>&& array, std::size_t height)
		: data_(std::move(array)), height_(height)
	{}
	matrix::matrix(const matrix& matrix)
		: data_(matrix.data_), height_(matrix.height_)
	{}
	matrix::matrix(matrix&& matrix) noexcept
		: data_(std::move(matrix.data_)), height_(matrix.height_)
	{
		matrix.height_ = 0;
	}

	matrix& matrix::operator=(const matrix& matrix)
	{
		data_ = matrix.data_;
		height_ = matrix.height_;
		return *this;
	}
	matrix& matrix::operator=(matrix&& matrix) noexcept
	{
		data_ = std::move(matrix.data_);
		height_ = matrix.height_;

		matrix.height_ = 0;

		return *this;
	}
	bool operator==(const matrix& a, const matrix& b) noexcept
	{
		if (&a == &b) return true;
		if (a.height() != b.height() ||
			a.width() != b.width()) return false;

		for (std::size_t i = 0; i < a.size(); ++i)
		{
			if (a.data_[i] != b.data_[i]) return false;
		}

		return true;
	}
	bool operator!=(const matrix& a, const matrix& b) noexcept
	{
		if (&a == &b) return false;
		if (a.height() != b.height() ||
			a.width() != b.width()) return true;

		for (std::size_t i = 0; i < a.size(); ++i)
		{
			if (a.data_[i] != b.data_[i]) return true;
		}

		return false;
	}
	double matrix::operator[](const matrix_index& index) const noexcept
	{
		assert(index.y < height());
		assert(index.x < width());

		return data_[index.y * width() + index.x];
	}
	double& matrix::operator[](const matrix_index& index) noexcept
	{
		assert(index.y < height());
		assert(index.x < width());

		return data_[index.y * width() + index.x];
	}
	matrix operator+(const matrix& a, const matrix& b)
	{
		return matrix(a) += b;
	}
	matrix operator-(const matrix& a, const matrix& b)
	{
		return matrix(a) -= b;
	}
	matrix operator*(double c, const matrix& matrix)
	{
		lml_edk::matrix result(matrix);

		for (std::size_t i = 0; i < matrix.size(); ++i)
		{
			result.data_[i] *= c;
		}

		return result;
	}
	matrix operator*(const matrix& a, const matrix& b)
	{
		return matrix(a) *= b;
	}
	matrix& matrix::operator+=(const matrix& other) noexcept
	{
		assert(height() == other.height());
		assert(width() == other.width());

		for (std::size_t i = 0; i < size(); ++i)
		{
			data_[i] += other.data_[i];
		}

		return *this;
	}
	matrix& matrix::operator-=(const matrix& other) noexcept
	{
		assert(height() == other.height());
		assert(width() == other.width());

		for (std::size_t i = 0; i < size(); ++i)
		{
			data_[i] -= other.data_[i];
		}

		return *this;
	}
	matrix& matrix::operator*=(const matrix& other) noexcept
	{
		assert(height() == other.height());
		assert(width() == other.width());

		for (std::size_t i = 0; i < size(); ++i)
		{
			data_[i] *= other.data_[i];
		}

		return *this;
	}

	void matrix::clear() noexcept
	{
		data_.clear();
		height_ = 0;
	}
	bool matrix::empty() const noexcept
	{
		return data_.empty();
	}
	void matrix::swap(matrix& matrix) noexcept
	{
		data_.swap(matrix.data_);
		std::swap(height_, matrix.height_);
	}
	bool matrix::zero() const noexcept
	{
		for (double x : data_)
		{
			if (x != 0.) return false;
		}
		
		return true;
	}
	std::size_t matrix::height() const noexcept
	{
		return height_;
	}
	std::size_t matrix::width() const noexcept
	{
		return size() / height_;
	}
	std::size_t matrix::size() const noexcept
	{
		return data_.size();
	}

	matrix::iterator matrix::begin() noexcept
	{
		return data_.begin();
	}
	matrix::const_iterator matrix::begin() const noexcept
	{
		return data_.begin();
	}
	matrix::const_iterator matrix::cbegin() const noexcept
	{
		return data_.cbegin();
	}
	matrix::iterator matrix::end() noexcept
	{
		return data_.end();
	}
	matrix::const_iterator matrix::end() const noexcept
	{
		return data_.end();
	}
	matrix::const_iterator matrix::cend() const noexcept
	{
		return data_.cend();
	}
	matrix::reverse_iterator matrix::rbegin() noexcept
	{
		return data_.rbegin();
	}
	matrix::const_reverse_iterator matrix::rbegin() const noexcept
	{
		return data_.rbegin();
	}
	matrix::const_reverse_iterator matrix::crbegin() const noexcept
	{
		return data_.crbegin();
	}
	matrix::reverse_iterator matrix::rend() noexcept
	{
		return data_.rend();
	}
	matrix::const_reverse_iterator matrix::rend() const noexcept
	{
		return data_.rend();
	}
	matrix::const_reverse_iterator matrix::crend() const noexcept
	{
		return data_.crend();
	}

	matrix matrix::transpose() const
	{
		matrix result(width(), height());

		for (std::size_t i = 0; i < height(); ++i)
		{
			for (std::size_t j = 0; j < width(); ++j)
			{
				result[{ j, i }] = (*this)[{ i, j }];
			}
		}

		return result;
	}
	matrix matrix::dot(const matrix& other) const
	{
		assert(width() == other.height());

		matrix result(height(), other.width());

		for (std::size_t i = 0; i < height(); ++i)
		{
			for (std::size_t j = 0; j < other.width(); ++j)
			{
				for (std::size_t k = 0; k < width(); ++k)
				{
					result[{ i, j }] += (*this)[{ i, k }] * other[{ k, j }];
				}
			}
		}

		return result;
	}

	std::ostream& operator<<(std::ostream& stream, const matrix& matrix)
	{
		stream << '[';
		
		for (std::size_t i = 0; i < matrix.height(); ++i)
		{
			if (i != 0)
			{
				stream << "\n ";
			}
			stream << "[ ";
			
			for (std::size_t j = 0; j < matrix.width(); ++j)
			{
				stream << matrix[{ i, j }] << ' ';
			}

			stream << ']';
		}

		stream << ']';
		return stream;
	}

	matrix transpose(const matrix& matrix)
	{
		return matrix.transpose();
	}
	matrix dot(const matrix& a, const matrix & b)
	{
		return a.dot(b);
	}
}