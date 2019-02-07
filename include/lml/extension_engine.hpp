#pragma once

#include <lml_edk/extension.hpp>
#include <lml_pae/dll.hpp>
#include <lml_pae/string.hpp>

#include <cstdint>
#include <map>
#include <utility>

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
		std::uint64_t add_extension(const lml_pae::string&path);
		lml_edk::extension_base_ptr get_extension(std::uint64_t id) const noexcept;
		std::uint64_t get_id(const lml_edk::extension_base_ptr& extension) const noexcept;
		
	private:
		std::map<std::uint64_t, std::pair<lml_edk::extension_base_ptr, lml_pae::dll_handle>> extensions_;
	};
}