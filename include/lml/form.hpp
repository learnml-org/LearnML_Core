#pragma once

#include <memory>
#include <Windows.h>

namespace lml
{
	class form
	{
		friend class application;

	public:
		form(const form&) = delete;
		virtual ~form();

	protected:
		form();

	public:
		form& operator=(const form&) = delete;

	public:
		void show();
		void show(int show);

	protected:
		virtual LRESULT CALLBACK wnd_proc(UINT message, WPARAM wparam, LPARAM lparam);

	private:
		void initialize_form_();

	public:
		HWND handle() noexcept;

	private:
		HWND handle_;

	private:
		static LRESULT CALLBACK wnd_proc_(HWND handle, UINT message, WPARAM wparam, LPARAM lparam);
	};

	using form_ptr = std::shared_ptr<form>;

	class main_form final : public form
	{
	public:
		main_form() = default;
		main_form(const main_form&) = delete;
		virtual ~main_form() = default;

	public:
		main_form& operator=(const main_form&) = delete;

	protected:
		virtual LRESULT CALLBACK wnd_proc(UINT message, WPARAM wparam, LPARAM lparam) override;
	};
}