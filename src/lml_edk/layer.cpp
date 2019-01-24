#include <lml_edk/layer.hpp>

namespace lml_edk
{
	std::uint32_t layer_allocator::id() const
	{
		return allocate({})->id();
	}
	global_string layer_allocator::name() const
	{
		return allocate({})->name();
	}
	global_pair_string layer_allocator::description() const
	{
		return allocate({})->description();
	}
}

namespace lml_edk
{
	inline namespace v1_0_0
	{
		const function_table<layer_base>& layer::functions() const
		{
			static const function_table<layer_base> map = {
				{ "forward", { function_cast<layer_base>(&layer::forward), 0 } },
				{ "backward", { function_cast<layer_base>(&layer::backward), 0 } },
				{ "update", { function_cast<layer_base>(&layer::update), 0 } },
			};

			return map;
		}
	}
}