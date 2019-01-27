#include <lml/platform.hpp>

#include <Windows.h>

namespace lml
{
	std::string get_os_name()
	{
		if constexpr (os::target == os::windows)
		{
			return get_windows_name();
		}

		return "Unknown";
	}
	std::string get_windows_name()
	{
		BOOL is_wow64 = FALSE;
		IsWow64Process(GetCurrentProcess(), &is_wow64);
		REGSAM wow64 = is_wow64 ? KEY_WOW64_64KEY : 0;

		HKEY version;
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), 0, KEY_QUERY_VALUE | wow64, &version) != ERROR_SUCCESS)
			return "Unknown";
		
		DWORD string_size;
		if (RegQueryValueExA(version, "ProductName", nullptr, nullptr, nullptr, &string_size) != ERROR_SUCCESS)
			return "Unknown";
		std::string result(static_cast<std::size_t>(string_size), 0);
		if (RegQueryValueExA(version, "ProductName", nullptr, nullptr, reinterpret_cast<LPBYTE>(result.data()), &string_size) != ERROR_SUCCESS)
			return "Unknown";
		
		result.erase(result.end() - 1);
		return result;
	}
}