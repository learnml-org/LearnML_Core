#include <lml/string.hpp>

#include <lml/errorcode.hpp>

#include <Windows.h>

namespace lml
{
	std::string encode_utf8(const std::wstring& utf16)
	{
		if (utf16.empty()) return {};

		const int size = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), static_cast<int>(utf16.size()), nullptr, 0, nullptr, nullptr);
		std::string result(static_cast<std::size_t>(size), 0);

		if (WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), static_cast<int>(utf16.size()), result.data(), size, nullptr, nullptr) == 0 &&
			GetLastError() == ERROR_NO_UNICODE_TRANSLATION) throw LML_ERRORCODE_FAILED_TO_ENCODE_16TO8;
		
		return result;
	}
	std::string encode_utf8(const std::string& system_encoding)
	{
		if (system_encoding.empty()) return {};

		const std::wstring utf16 = encode_utf16_from_system_encoding(system_encoding);
		const int size = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), static_cast<int>(utf16.size()), nullptr, 0, nullptr, nullptr);
		std::string result(static_cast<std::size_t>(size), 0);

		if (WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), static_cast<int>(utf16.size()), result.data(), size, nullptr, nullptr) == 0 &&
			GetLastError() == ERROR_NO_UNICODE_TRANSLATION) throw LML_ERRORCODE_FAILED_TO_ENCODE_DTO8;

		return result;
	}
	std::string encode_system_encoding(const std::wstring& utf16)
	{
		if (utf16.empty()) return {};

		const int size = WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), static_cast<int>(utf16.size()), nullptr, 0, nullptr, nullptr);
		std::string result(static_cast<std::size_t>(size), 0);

		if (WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), static_cast<int>(utf16.size()), result.data(), size, nullptr, nullptr) == 0 &&
			GetLastError() == ERROR_NO_UNICODE_TRANSLATION) throw LML_ERRORCODE_FAILED_TO_ENCODE_16TOD;

		return result;
	}
	std::string encode_system_encoding(const std::string& utf8)
	{
		if (utf8.empty()) return {};

		const std::wstring utf16 = encode_utf16_from_utf8(utf8);
		const int size = WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), static_cast<int>(utf16.size()), nullptr, 0, nullptr, nullptr);
		std::string result(static_cast<std::size_t>(size), 0);

		if (WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), static_cast<int>(utf16.size()), result.data(), size, nullptr, nullptr) == 0 &&
			GetLastError() == ERROR_NO_UNICODE_TRANSLATION) throw LML_ERRORCODE_FAILED_TO_ENCODE_DTO8;

		return result;
	}
	std::wstring encode_utf16_from_utf8(const std::string& utf8)
	{
		if (utf8.empty()) return {};

		const int size = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), nullptr, 0);
		std::wstring result(static_cast<std::size_t>(size), 0);

		MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), result.data(), size);
		return result;
	}
	std::wstring encode_utf16_from_system_encoding(const std::string& system_encoding)
	{
		if (system_encoding.empty()) return {};

		const int size = MultiByteToWideChar(CP_ACP, 0, system_encoding.c_str(), static_cast<int>(system_encoding.size()), nullptr, 0);
		std::wstring result(static_cast<std::size_t>(size), 0);

		MultiByteToWideChar(CP_ACP, 0, system_encoding.c_str(), static_cast<int>(system_encoding.size()), result.data(), size);
		return result;
	}
}