#include <lml/result.hpp>

namespace lml
{
	std::basic_string<TCHAR> make_error_message(const std::basic_string_view<TCHAR>& message, std::uint32_t errorcode)
	{
		std::basic_ostringstream<TCHAR> oss;
		oss << message << TEXT("\n(Errorcode 0x") << std::hex << std::setw(8) << std::setfill(TEXT('0')) << errorcode << ')';
		return oss.str();
	}
}