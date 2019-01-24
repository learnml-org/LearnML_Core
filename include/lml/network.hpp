#pragma once

#include <lml/layer.hpp>
#include <lml_edk/matrix.hpp>

#include <vector>

namespace lml
{
	class network final
	{
	public:
		network() noexcept = default;
		network(const network&) = delete;
		~network() = default;

	public:
		network& operator=(const network&) = delete;
		layer_cptr operator[](std::size_t index) const noexcept;
		layer_ptr operator[](std::size_t index) noexcept;

	public:
		void clear() noexcept;
		bool empty() const noexcept;
		void add_layer(const layer_ptr& layer);
		void remove_layer(std::size_t index);
		std::size_t depth() const noexcept;

		lml_edk::matrix forward(const lml_edk::matrix& x);
		void backward(const lml_edk::matrix& g);
		void update(double lr);

	private:
		std::vector<layer_ptr> layers_;
	};
}