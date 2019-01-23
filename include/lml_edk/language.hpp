#pragma once
#include <lml_edk/config.hpp>

#include <map>
#include <optional>
#include <string>
#include <utility>
#include <Windows.h>

namespace lml_edk
{
	enum class language
	{
		ko, kor = ko,
		en, eng = en,
	};

	using global_string = std::map<language, std::basic_string<TCHAR>>;
	using global_pair_string = std::map<language, std::pair<std::basic_string<TCHAR>, std::basic_string<TCHAR>>>;

	LML_EDK_EXPORT std::optional<std::basic_string<TCHAR>> get_string(const global_string& string, language language) noexcept;
	LML_EDK_EXPORT std::optional<std::pair<std::basic_string<TCHAR>, std::basic_string<TCHAR>>> get_string(const global_pair_string& string, language language) noexcept;
}