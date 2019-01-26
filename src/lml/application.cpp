#include <lml/application.hpp>

#include <lml/details/errorcode.hpp>

#include <iomanip>
#include <ios>
#include <sstream>

namespace lml
{
	std::uint32_t application::initialize(HINSTANCE instance, int show) noexcept
	{
		application::instance = instance;
		application::show = show;

		static WNDCLASS wndclass;
		ZeroMemory(&wndclass, sizeof(wndclass));

		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wndclass.hInstance = instance;
		wndclass.lpfnWndProc = form::wnd_proc_;
		wndclass.lpszClassName = TEXT("form");
		wndclass.lpszMenuName = nullptr;
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		
		if (RegisterClass(&wndclass) == 0) return LML_ERRORCODE_FAILED_TO_REGISTER_FORM;

		try
		{
			application::main_form = std::make_shared<lml::main_form>();
		}
		catch (std::uint32_t errorcode)
		{
			return errorcode;
		}

		return 0;
	}
	int application::messagebox(HWND owner, const std::basic_string<TCHAR>& message, UINT option) noexcept
	{
		return MessageBox(owner, message.data(), application::title, option);
	}
	void application::run() noexcept
	{
		try
		{
			application::main_form->show(application::show);

			MSG message;

			while (GetMessage(&message, nullptr, 0, 0))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		catch (std::uint32_t errorcode)
		{
			application::messagebox(nullptr, lml::make_error_message(errorcode), MB_OK | MB_ICONERROR);
		}
	}
}

namespace lml
{
	std::basic_string<TCHAR> make_error_message(std::uint32_t errorcode)
	{
		std::basic_ostringstream<TCHAR> oss;
		oss << TEXT("Error! Please report to the developers.\nErrorcode: 0x") << std::hex << std::setw(8) << std::setfill(TEXT('0')) << errorcode << ')';
		return oss.str();
	}
}