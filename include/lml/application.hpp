#pragma once

#include <cstdint>
#include <string>
#include <string_view>
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

		static inline HINSTANCE instance = nullptr;
		static inline int show = 0;

	public:
		static int initialize(HINSTANCE instance, int show) noexcept;
		static int messagebox(HWND owner, const std::basic_string<TCHAR>& message, UINT option) noexcept;
	};

	std::basic_string<TCHAR> make_error_message(const std::basic_string_view<TCHAR>& message, std::uint32_t errorcode);
}