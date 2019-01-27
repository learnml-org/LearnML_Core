#include <lml/form.hpp>

#include <lml/application.hpp>
#include <lml/details/errorcode.hpp>

namespace lml
{
	form::form()
		: control(initialize_form_())
	{}
	
	LRESULT form::wnd_proc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		default:
			return DefWindowProc(handle, message, wparam, lparam);
		}
	}

	HWND form::initialize_form_()
	{
		HWND handle;
		if ((handle = CreateWindow(TEXT("form"), application::title, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 980, 680,
			nullptr, nullptr, application::instance, nullptr)) == nullptr) throw LML_ERRORCODE_FAILED_TO_CREATE_FORM;

		SetLastError(0);
		if (SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) == 0 && GetLastError() != 0) throw LML_ERRORCODE_FAILED_TO_CREATE_FORM;

		return handle;
	}

	LRESULT form::wnd_proc_(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		form* address = reinterpret_cast<form*>(GetWindowLongPtr(handle, GWLP_USERDATA));
		
		if (address)
		{
			return address->wnd_proc(handle, message, wparam, lparam);
		}
		else
		{
			return DefWindowProc(handle, message, wparam, lparam);
		}
	}
}

namespace lml
{
	LRESULT main_form::wnd_proc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			return form::wnd_proc(handle, message, wparam, lparam);
		}
	}
}