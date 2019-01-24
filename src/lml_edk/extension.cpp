#include <lml_edk/extension.hpp>

namespace lml_edk
{
	inline namespace v1_0_0
	{
		const function_table& extension::functions() const
		{
			static const function_table map = {
				{ "enabled", { &extension::enabled, 0 } },
				{ "disabled", { &extension::disabled, 0 } },

				{ "layers", { &extension::layers, 0 } },
			};

			return map;
		}
	}
}