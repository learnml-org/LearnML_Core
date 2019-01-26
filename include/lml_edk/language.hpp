#pragma once

#include <map>
#include <optional>
#include <string>
#include <utility>
#include <Windows.h>

namespace lml_edk
{
	enum class language
	{
		ko, kor = ko,
		en, eng = en,
	};

	class description final
	{
	public:
		description(const std::basic_string<TCHAR>& text);
		description(const std::basic_string<TCHAR>& title, const std::basic_string<TCHAR>& text);
		description(const description& description);
		description(description&& description) noexcept;
		~description() = default;

	public:
		description& operator=(const description& description);
		description& operator=(description&& description) noexcept;

	public:
		std::basic_string<TCHAR> title;
		std::basic_string<TCHAR> text;
	};

	using global_string = std::map<language, std::basic_string<TCHAR>>;
	using global_description = std::map<language, description>;

	std::optional<std::basic_string<TCHAR>> get_string(const global_string& string, language language) noexcept;
	std::optional<description> get_string(const global_description& string, language language) noexcept;
}