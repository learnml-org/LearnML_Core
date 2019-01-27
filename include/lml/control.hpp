#pragma once

#include <memory>
#include <Windows.h>

namespace lml
{
	class control
	{
	public:
		control(const control&) = delete;
		virtual ~control();

	protected:
		control(HWND handle) noexcept;

	public:
		control& operator=(const control&) = delete;

	public:
		void show();
		void show(int show);
		void hide();

	private:
		HWND handle_;
	};

	using control_ptr = std::shared_ptr<control>;
}