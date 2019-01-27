#pragma once

#include <lml/form.hpp>
#include <lml/log.hpp>
#include <lml/logs/external_error.hpp>
#include <lml/logs/internal_error.hpp>
#include <lml/logs/message.hpp>

#include <cstdint>
#include <string>
#include <Windows.h>

namespace lml
{
	class application final
	{
	public:
		application() = delete;
		application(const application&) = delete;
		~application() = delete;

	public:
		application& operator=(const application&) = delete;

	public:
		static constexpr LPCTSTR name = TEXT("LearnML");
		static constexpr LPCTSTR title = TEXT("LearnML 1.0.0");
		static constexpr int version[] = { 1, 0, 0 };
		static constexpr std::uint64_t version_int = 0;

		static inline HINSTANCE instance = nullptr;
		static inline int show = 0;
		static inline std::basic_string<TCHAR> path_appdata;

		static inline logger logger;
		static inline form_ptr main_form;

	public:
		static std::uint32_t initialize(HINSTANCE instance, int show) noexcept;
		static int messagebox(HWND owner, const std::basic_string<TCHAR>& message, UINT option) noexcept;
		static void run() noexcept;
	};

	std::basic_string<TCHAR> make_error_message(std::uint32_t errorcode);
}