#pragma once

#include <lml_edk/language.hpp>
#include <lml_edk/layer.hpp>
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
		virtual lml_edk::global_string name() const = 0;
		virtual lml_edk::global_pair_string description() const = 0;
		virtual lml_edk::matrix forward(const lml_edk::matrix& x) = 0;
		virtual lml_edk::matrix backward(const lml_edk::matrix& g) = 0;
		virtual void update(double lr) = 0;
	};

	using layer_ptr = std::shared_ptr<layer>;
	using layer_cptr = std::shared_ptr<const layer>;

	class wrap_layer final
	{
	public:
		wrap_layer() noexcept = default;
		explicit wrap_layer(const lml_edk::layer_base_ptr& layer) noexcept;
		wrap_layer(const wrap_layer& layer) = delete;
		~wrap_layer() = default;

	public:
		wrap_layer& operator=(const wrap_layer&) = delete;

	public:
		std::uint32_t id() const noexcept;
		lml_edk::global_string name() const;
		lml_edk::global_pair_string description() const;

		lml_edk::matrix forward(const lml_edk::matrix& x);
		lml_edk::matrix backward(const lml_edk::matrix& g);
		void update(double lr);

	private:
		lml_edk::layer_base_ptr layer_;
	};
}