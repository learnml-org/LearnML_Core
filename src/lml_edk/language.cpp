#include <lml_edk/language.hpp>

namespace lml_edk
{
	LML_EDK_EXPORT std::optional<std::basic_string<TCHAR>> get_string(const global_string& string, language language) noexcept
	{
		if (auto iter = string.find(language); iter != string.end()) return iter->second;
		else return std::nullopt;
	}
}