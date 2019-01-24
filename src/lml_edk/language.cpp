#include <lml_edk/language.hpp>

namespace lml_edk
{
	std::optional<std::basic_string<TCHAR>> get_string(const global_string& string, language language) noexcept
	{
		if (auto iter = string.find(language); iter != string.end()) return iter->second;
		else return std::nullopt;
	}
	std::optional<std::pair<std::basic_string<TCHAR>, std::basic_string<TCHAR>>> get_string(const global_pair_string& string, language language) noexcept
	{
		if (auto iter = string.find(language); iter != string.end()) return iter->second;
		else return std::nullopt;
	}
}