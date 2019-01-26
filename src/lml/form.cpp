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

	void form::initialize_form_()
	{
		if ((handle_ = CreateWindow(TEXT("form"), application::title, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 980, 680,
			nullptr, nullptr, application::instance, nullptr)) == nullptr) throw LML_ERRORCODE_FAILED_TO_CREATE_FORM;

		SetLastError(0);
		if (SetWindowLongPtr(handle_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) == 0 && GetLastError() != 0) throw LML_ERRORCODE_FAILED_TO_CREATE_FORM;
	}
	LRESULT form::wnd_proc_(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		default:
			return DefWindowProc(handle, message, wparam, lparam);
		}
	}

	LRESULT form::static_wnd_proc_(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		form* address = reinterpret_cast<form*>(GetWindowLongPtr(handle, GWLP_USERDATA));
		
		if (address)
		{
			return address->wnd_proc_(handle, message, wparam, lparam);
		}
		else
		{
			return DefWindowProc(handle, message, wparam, lparam);
		}
	}
}