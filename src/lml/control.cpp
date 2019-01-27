#include <lml/control.hpp>

#include <algorithm>
#include <cassert>

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

	void control::add_control(const std::shared_ptr<control>& control)
	{
		assert(this != control.get());
		assert(std::find(controls_.begin(), controls_.end(), control) == controls_.end());

		controls_.push_back(control);

		SetParent(control->handle_, handle_);
	}
	void control::remove_control(const std::shared_ptr<control>& control)
	{
		const auto iter = std::find(controls_.begin(), controls_.end(), control);
		assert(iter != controls_.end());

		SetParent((*iter)->handle_, nullptr);
		controls_.erase(iter);
	}
}