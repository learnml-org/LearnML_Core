#pragma once
#include <lml_edk/config.hpp>

#include <any>
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <utility>

namespace lml_edk
{
	using function_result = std::any;
	using function_parameter = std::map<std::string, std::any>;

	template<typename Base_>
	using function_table = std::map<std::string, std::pair<std::function<function_result(Base_*, function_parameter)>, std::uint64_t>>;

	template<typename Base_, typename Ty_>
	decltype(auto) function_cast(function_result(Ty_::*function)(function_parameter)) noexcept
	{
		return reinterpret_cast<function_result(Base_::*)(function_parameter)>(function);
	}

	struct no_return_t
	{};
	static inline const no_return_t no_return;
}