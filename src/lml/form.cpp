#include <lml/form.hpp>

#include <lml/application.hpp>
#include <lml/details/errorcode.hpp>

namespace lml
{
	form::~form()
	{
		DestroyWindow(handle_);
		handle_ = nullptr;
	}

	form::form()
	{
		initialize_form_();
	}
	
	void form::show()
	{
		show(SW_SHOW);
	}
	void form::show(int show)
	{
		ShowWindow(handle_, show);
	}

	LRESULT form::wnd_proc(UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		default:
			return DefWindowProc(handle_, message, wparam, lparam);
		}
	}

	void form::initialize_form_()
	{
		if ((handle_ = CreateWindow(TEXT("form"), application::title, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 980, 680,
			nullptr, nullptr, application::instance, nullptr)) == nullptr) throw LML_ERRORCODE_FAILED_TO_CREATE_FORM;

		SetLastError(0);
		if (SetWindowLongPtr(handle_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) == 0 && GetLastError() != 0) throw LML_ERRORCODE_FAILED_TO_CREATE_FORM;
	}

	HWND form::handle() noexcept
	{
		return handle_;
	}

	LRESULT form::wnd_proc_(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		form* address = reinterpret_cast<form*>(GetWindowLongPtr(handle, GWLP_USERDATA));
		
		if (address)
		{
			return address->wnd_proc(message, wparam, lparam);
		}
		else
		{
			return DefWindowProc(handle, message, wparam, lparam);
		}
	}
}

namespace lml
{
	LRESULT main_form::wnd_proc(UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return form::wnd_proc(message, wparam, lparam);
		}
	}
}