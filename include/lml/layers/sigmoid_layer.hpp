#pragma once

#include <cstdint>

#include <lml/layer.hpp>
#include <lml_edk/language.hpp>
#include <lml_edk/matrix.hpp>

namespace lml::layers
{
	class sigmoid_layer final : public layer
	{
	public:
		sigmoid_layer() noexcept = default;
		sigmoid_layer(const sigmoid_layer&) = delete;
		virtual ~sigmoid_layer() override = default;

	public:
		sigmoid_layer& operator=(const sigmoid_layer&) = delete;

	public:
		virtual std::uint32_t id() const noexcept override;
		virtual lml_edk::global_string name() const override;
		virtual lml_edk::global_description description() const override;
		virtual lml_edk::matrix forward(const lml_edk::matrix& x) override;
		virtual lml_edk::matrix backward(const lml_edk::matrix& g) override;
		virtual void update(double lr) override;

	private:
		lml_edk::matrix x_, y_;
	};
}