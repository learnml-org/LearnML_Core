#include <lml/network.hpp>

namespace lml
{
	layer_cptr network::operator[](std::size_t index) const noexcept
	{
		return layers_[index];
	}
	layer_ptr network::operator[](std::size_t index) noexcept
	{
		return layers_[index];
	}

	void network::clear() noexcept
	{
		layers_.clear();
	}
	bool network::empty() const noexcept
	{
		return layers_.empty();
	}
	void network::add_layer(const layer_ptr& layer)
	{
		layers_.push_back(layer);
	}
	void network::remove_layer(std::size_t index)
	{
		layers_.erase(layers_.begin() + index);
	}
	std::size_t network::depth() const noexcept
	{
		return layers_.size();
	}

	lml_edk::matrix network::forward(const lml_edk::matrix& x)
	{
		lml_edk::matrix h = x;
		
		for (layer_ptr layer : layers_)
		{
			h = layer->forward(h);
		}

		return h;
	}
	void network::backward(const lml_edk::matrix& g)
	{
		lml_edk::matrix d = g;

		for (auto iter = layers_.rbegin(); iter < layers_.rend(); ++iter)
		{
			d = (*iter)->backward(d);
		}
	}
	void network::update(double lr)
	{
		for (layer_ptr layer : layers_)
		{
			layer->update(lr);
		}
	}
}