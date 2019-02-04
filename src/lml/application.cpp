#include <lml/application.hpp>

#include <lml/errorcode.hpp>
#include <lml_le/engine.hpp>
#include <lml_ue/engine.hpp>

#include <filesystem>
#include <iomanip>
#include <ios>
#include <ShlObj.h>
#include <Shlwapi.h>
#include <sstream>

namespace lml
{
	std::uint32_t application::initialize(HINSTANCE instance, int show) noexcept
	{
		// Initialize variables
		application::instance = instance;
		application::show = show;

		// Initialize user interface
		if (std::uint32_t errorcode = lml_ue::initialize(instance); errorcode) return errorcode;

		try
		{
			application::main_form = std::make_shared<lml_ue::main_form>();
			application::main_form->minimum_size(640, 480);
		}
		catch (std::uint32_t errorcode)
		{
			return errorcode;
		}

		// Initialize directories
		TCHAR appdata_buf[32767]{ 0, };
		if (SHGetFolderPath(nullptr, CSIDL_APPDATA, nullptr, 0, appdata_buf) != S_OK) return LML_ERRORCODE_FAILED_TO_GET_APPDATA;
		application::path_appdata = appdata_buf;
		application::path_appdata += TEXT("\\Staticom\\LearnML");

		if (!std::filesystem::exists(application::path_appdata) && !std::filesystem::create_directories(application::path_appdata)) return LML_ERRORCODE_FAILED_TO_CREATE_APPDATA;

		// Load options
		try
		{
			application::options.load(path_appdata + TEXT("\\options.lmlo"));
		}
		catch (std::uint32_t)
		{}
		application::options.autosave(path_appdata + TEXT("\\options.lmlo"));

		// Initialize logger
		lml_le::initialize(application::version_int, &application::get_temp_file);
		application::logger.autosave(path_appdata + TEXT("\\latest_logs.lmll"));
		application::logger.autosave_include_additional_data(application::options.include_additional_data());

		application::logger.add_log(lml_le::make_message(TEXT("Initialization succeeded."), lml_le::log_type::info));

		return 0;
	}
	int application::messagebox(HWND owner, const std::basic_string<TCHAR>& message, UINT option) noexcept
	{
		return MessageBox(owner, message.data(), application::title, option);
	}
	void application::run() noexcept
	{
		try
		{
			application::main_form->show(application::show);

			MSG message;

			while (GetMessage(&message, nullptr, 0, 0))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		catch (std::uint32_t errorcode)
		{
			application::messagebox(nullptr, lml::make_error_message(errorcode), MB_OK | MB_ICONERROR);
		}
	}

	std::basic_string<TCHAR> application::get_temp_file()
	{
		static std::basic_string<TCHAR> temp_path;

		if (temp_path.empty())
		{
			TCHAR temp_path_buf[32767]{ 0, };
			if (GetTempPath(sizeof(temp_path_buf) / sizeof(TCHAR), temp_path_buf) == 0) throw LML_ERRORCODE_FAILED_TO_GET_TEMP_DIRECTORY;
			temp_path = temp_path_buf;
		}

		TCHAR temp_file_buf[32767]{ 0, };
		if (GetTempFileName(temp_path.c_str(), TEXT("lml"), 0, temp_file_buf) == 0) throw LML_ERRORCODE_FAILED_TO_GET_TEMP_FILE;
		
		return temp_file_buf;
	}
}

namespace lml
{
	std::basic_string<TCHAR> make_error_message(std::uint32_t errorcode)
	{
		std::basic_ostringstream<TCHAR> oss;
		oss << TEXT("Error! Please report to the developers.\nErrorcode: 0x") << std::hex << std::setw(8) << std::setfill(TEXT('0')) << errorcode << ')';
		return oss.str();
	}
}