#pragma once

#include <lml_edk/matrix.hpp>

#include <cstdint>
#include <memory>

namespace lml
{
	class layer
	{
	public:
		layer(const layer&) = delete;
		virtual ~layer() = default;

	protected:
		layer() noexcept = default;

	public:
		virtual std::uint32_t id() const noexcept = 0;
		virtual lml_edk::matrix forward(const lml_edk::matrix& x) = 0;
		virtual lml_edk::matrix backward(const lml_edk::matrix& g) = 0;
		virtual void update(double lr) = 0;
	};

	using layer_ptr = std::shared_ptr<layer>;
	using layer_cptr = std::shared_ptr<const layer>;
}