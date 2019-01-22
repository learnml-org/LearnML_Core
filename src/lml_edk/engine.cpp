#include <lml_edk/engine.hpp>

namespace lml_edk
{
	std::array<int, 3> engine::edk_version() const noexcept
	{
		return { 1, 0, 0 };
	}
}

extern "C" void* make_engine() noexcept
{
	return new lml_edk::engine();
}