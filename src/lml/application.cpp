#include <lml/application.hpp>

#include <iomanip>
#include <ios>
#include <sstream>

namespace lml
{
	int application::initialize(HINSTANCE instance, int show) noexcept
	{
		application::instance = instance;
		application::show = show;

		return 0;
	}
	int application::messagebox(HWND owner, const std::basic_string<TCHAR>& message, UINT option) noexcept
	{
		return MessageBox(owner, message.data(), application::title, option);
	}
}

namespace lml
{
	std::basic_string<TCHAR> make_error_message(const std::basic_string_view<TCHAR>& message, std::uint32_t errorcode)
	{
		std::basic_ostringstream<TCHAR> oss;
		oss << message << TEXT("\n(Errorcode 0x") << std::hex << std::setw(8) << std::setfill(TEXT('0')) << errorcode << ')';
		return oss.str();
	}
}