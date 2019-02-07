#include <lml/layers/fully_connected_layer.hpp>

#include <lml/details/string.hpp>
#include <lml_pae/string.hpp>

#include <algorithm>
#include <random>

namespace lml::layers
{
	fully_connected_layer::fully_connected_layer(std::uint64_t input, std::uint64_t output) noexcept
		: weights_(static_cast<std::size_t>(output), static_cast<std::size_t>(input)), bias_(static_cast<std::size_t>(output), 1)
	{
		std::random_device seed;
		std::mt19937_64 rd(seed());
		std::uniform_real_distribution<double> dist(0, 1);

		auto rand = [&rd, &dist](double) mutable
		{
			double result;
			do
			{
				result = dist(rd);
			} while (!result);
			return result;
		};

		std::transform(weights_.begin(), weights_.end(), weights_.begin(), rand);
		std::transform(bias_.begin(), bias_.end(), bias_.begin(), rand);
	}

	std::uint32_t fully_connected_layer::id() const noexcept
	{
		return 0;
	}
	lml_edk::global_string fully_connected_layer::name() const
	{
		return {
			{ lml_edk::language::ko, LML_STRING_LAYERS_FULLY_CONNECTED_LAYER_METHOD_NAME_KOR },
			{ lml_edk::language::en, LML_STRING_LAYERS_FULLY_CONNECTED_LAYER_METHOD_NAME_ENG }
		};
	}
	lml_edk::global_description fully_connected_layer::description() const
	{
		return {
			{ lml_edk::language::ko, {
				{ STR(""), LML_STRING_LAYERS_FULLY_CONNECTED_LAYER_METHOD_DESCRIPTION_KOR }
			} },
			{ lml_edk::language::en, {
				{ STR(""), LML_STRING_LAYERS_FULLY_CONNECTED_LAYER_METHOD_DESCRIPTION_ENG }
			} }
		};
	}
	lml_edk::matrix fully_connected_layer::forward(const lml_edk::matrix& x)
	{
		x_ = x;
		y_ = lml_edk::dot(weights_, x) + lml_edk::dot(bias_, lml_edk::matrix(1, x.width(), 1));
		return y_;
	}
	lml_edk::matrix fully_connected_layer::backward(const lml_edk::matrix& g)
	{
		dweights_ = lml_edk::dot(g, x_.transpose());
		dbias_ = lml_edk::dot(g, lml_edk::matrix(x_.width(), 1, 1));
		return lml_edk::dot(weights_.transpose(), g);
	}
	void fully_connected_layer::update(double lr)
	{
		weights_ -= lr * dweights_;
		bias_ -= lr * dbias_;
	}
}