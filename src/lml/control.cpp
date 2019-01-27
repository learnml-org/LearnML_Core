#include <lml/control.hpp>

namespace lml
{
	control::~control()
	{
		DestroyWindow(handle_);
		handle_ = nullptr;
	}

	control::control(HWND handle) noexcept
		: handle_(handle)
	{}

	void control::show()
	{
		show(SW_SHOW);
	}
	void control::show(int show)
	{
		ShowWindow(handle_, show);
	}
	void control::hide()
	{
		show(SW_HIDE);
	}
}