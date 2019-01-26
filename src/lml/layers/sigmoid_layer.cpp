#include <lml/layers/sigmoid_layer.hpp>

#include <algorithm>
#include <cmath>

namespace lml::layers
{
	std::uint32_t sigmoid_layer::id() const noexcept
	{
		return 1;
	}
	lml_edk::global_string sigmoid_layer::name() const
	{
		return {
			{ lml_edk::language::ko, TEXT("Sigmoid층") },
			{ lml_edk::language::en, TEXT("Sigmoid layer") }
		};
	}
	lml_edk::global_description sigmoid_layer::description() const
	{
		return {
			{ lml_edk::language::ko, {
				{ TEXT(""), TEXT("Sigmoid의 활성값을 계산합니다.") }
			} },
			{ lml_edk::language::en, {
				{ TEXT(""), TEXT("Calculate the value of Sigmoid function.") }
			} }
		};
	}
	lml_edk::matrix sigmoid_layer::forward(const lml_edk::matrix& x)
	{
		x_ = x;
		y_ = x;

		std::transform(y_.begin(), y_.end(), y_.begin(), [](double x)
		{
			return 1. / (1. + std::exp(-x));
		});

		return y_;
	}
	lml_edk::matrix sigmoid_layer::backward(const lml_edk::matrix& g)
	{
		lml_edk::matrix d = y_;
		std::transform(d.begin(), d.end(), d.begin(), [](double y)
		{
			return y * (1. - y);
		});

		return d * g;
	}
	void sigmoid_layer::update(double)
	{}
}