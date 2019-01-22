#pragma once
#include <lml_edk/config.hpp>

#include <array>
#include <optional>

namespace lml_edk
{
	class LML_EDK_EXPORT engine final
	{
	public:
		engine() noexcept = default;
		engine(const engine&) = delete;
		~engine() = default;

	public:
		engine& operator=(const engine&) = delete;
		
	public:
		std::array<int, 3> edk_version() const noexcept;

	public:
		std::optional<std::array<int, 3>> application_version() const noexcept;
		void application_version(int major, int minor, int patch) noexcept;

	private:
		std::optional<std::array<int, 3>> application_version_;
	};
}