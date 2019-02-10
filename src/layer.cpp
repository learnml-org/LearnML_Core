#include <lml/layer.hpp>

namespace lml
{
	wrap_layer::wrap_layer(const lml_edk::layer_base_ptr& layer) noexcept
		: layer_(layer)
	{}

	std::uint32_t wrap_layer::id() const noexcept
	{
		return layer_->id();
	}
	lml_pae::string wrap_layer::name() const
	{
		return layer_->name();
	}
	lml_edk::description wrap_layer::description() const
	{
		return layer_->description();
	}

	lml_edk::matrix wrap_layer::forward(const lml_edk::matrix& x)
	{
		return std::any_cast<lml_edk::matrix>(layer_->functions().at("forward").first(layer_.get(), { { "x", x } }));
	}
	lml_edk::matrix wrap_layer::backward(const lml_edk::matrix& g)
	{
		return std::any_cast<lml_edk::matrix>(layer_->functions().at("backward").first(layer_.get(), { { "g", g } }));
	}
	void wrap_layer::update(double lr)
	{
		layer_->functions().at("update").first(layer_.get(), { { "lr", lr } });
	}
}

namespace lml
{
	layer_extension::layer_extension(const lml_edk::layer_base_ptr& extension) noexcept
		: extension_(extension)
	{}

	std::uint32_t layer_extension::id() const noexcept
	{
		return extension_.id();
	}
	lml_pae::string layer_extension::name() const
	{
		return extension_.name();
	}
	lml_edk::description layer_extension::description() const
	{
		return extension_.description();
	}
	lml_edk::matrix layer_extension::forward(const lml_edk::matrix& x)
	{
		return extension_.forward(x);
	}
	lml_edk::matrix layer_extension::backward(const lml_edk::matrix& g)
	{
		return extension_.backward(g);
	}
	void layer_extension::update(double lr)
	{
		extension_.update(lr);
	}
}