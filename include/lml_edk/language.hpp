#pragma once

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

	std::optional<std::basic_string<TCHAR>> get_string(const global_string& string, language language) noexcept;
	std::optional<std::pair<std::basic_string<TCHAR>, std::basic_string<TCHAR>>> get_string(const global_pair_string& string, language language) noexcept;
}