#include <lml/application.hpp>

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