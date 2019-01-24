#pragma once

#include <lml_edk/extension.hpp>

#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <Windows.h>

namespace lml
{
	class extension_engine final
	{
	public:
		extension_engine() = default;
		extension_engine(const extension_engine&) = delete;
		~extension_engine() = default;

	public:
		extension_engine& operator=(const extension_engine&) = delete;

	public:
		std::uint64_t add_extension(const std::basic_string<TCHAR>& path);
		
	private:
		std::map<std::uint64_t, std::pair<lml_edk::extension_base_ptr, HMODULE>> extensions_;
	};
}