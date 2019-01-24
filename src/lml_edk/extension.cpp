#include <lml_edk/extension.hpp>

namespace lml_edk
{
	inline namespace v1_0_0
	{
		const function_table<extension_base>& extension::functions() const
		{
			static const function_table<extension_base> map = {
				{ "layers", { function_cast<extension_base>(&extension::layers), 0 } },
			};

			return map;
		}
	}
}