#include <lml_edk/engine.hpp>

namespace lml_edk
{
	std::array<int, 3> engine::edk_version() const noexcept
	{
		return { 1, 0, 0 };
	}

	std::optional<std::array<int, 3>> engine::application_version() const noexcept
	{
		return application_version_;
	}
	void engine::application_version(int major, int minor, int patch) noexcept
	{
		if (!application_version_)
		{
			application_version_ = std::array<int, 3>();
		}

		(*application_version_)[0] = major;
		(*application_version_)[1] = minor;
		(*application_version_)[2] = patch;
	}
}

extern "C" void* make_engine() noexcept
{
	return new lml_edk::engine();
}