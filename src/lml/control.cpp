#include <lml/control.hpp>

#include <lml/details/errorcode.hpp>

#include <lml/application.hpp>
#include <lml/form.hpp>

#include <algorithm>
#include <cassert>

namespace lml
{
	control::~control()
	{
		DestroyWindow(handle_);
		handle_ = nullptr;
	}

	control::control()
	{
		if ((handle_ = CreateWindow(TEXT("static"), TEXT(""), WS_CHILD | WS_VISIBLE, 0, 0, 200, 100, nullptr, nullptr, application::instance, nullptr)) == nullptr)
			throw LML_ERRORCODE_FAILED_TO_CREATE_CONTROL;
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
		assert(dynamic_cast<form*>(control.get()) == nullptr);

		controls_.push_back(control);

		SetParent(control->handle_, handle_);
		SetMenu(control->handle_, reinterpret_cast<HMENU>(controls_.size()));
	}
	void control::remove_control(const std::shared_ptr<control>& control)
	{
		const auto iter = std::find(controls_.begin(), controls_.end(), control);
		assert(iter != controls_.end());

		SetParent((*iter)->handle_, nullptr);
		SetMenu(control->handle_, nullptr);

		controls_.erase(iter);
	}
}