#pragma once

#include <cstdint>

#include <lml/layer.hpp>
#include <lml_edk/language.hpp>
#include <lml_edk/matrix.hpp>

namespace lml::layers
{
	class fully_connected_layer final : public layer
	{
	public:
		explicit fully_connected_layer(std::uint64_t input, std::uint64_t output) noexcept;
		fully_connected_layer(const fully_connected_layer&) = delete;
		virtual ~fully_connected_layer() override = default;

	public:
		fully_connected_layer& operator=(const fully_connected_layer&) = delete;

	public:
		virtual std::uint32_t id() const noexcept override;
		virtual lml_pae::string name() const override;
		virtual lml_edk::description description() const override;
		virtual lml_edk::matrix forward(const lml_edk::matrix& x) override;
		virtual lml_edk::matrix backward(const lml_edk::matrix& g) override;
		virtual void update(double lr) override;

	private:
		lml_edk::matrix weights_, bias_;
		lml_edk::matrix dweights_, dbias_;
		lml_edk::matrix x_, y_;
	};
}