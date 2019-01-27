#pragma once

#include <string>

namespace lml
{
	std::string encode_utf8(const std::wstring& utf16);
	std::string encode_utf8(const std::string& system_encoding);
	std::string encode_system_encoding(const std::wstring& utf16);
	std::string encode_system_encoding(const std::string& utf8);
	std::wstring encode_utf16_from_utf8(const std::string& utf8);
	std::wstring encode_utf16_from_system_encoding(const std::string& system_encoding);
}