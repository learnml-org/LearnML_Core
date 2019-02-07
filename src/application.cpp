#include <lml/application.hpp>

#include <lml/errorcode.hpp>
#include <lml_le/engine.hpp>
#include <lml_pae/engine.hpp>
#include <lml_pae/filesystem.hpp>

#include <iomanip>
#include <ios>
#include <sstream>

#if __has_include(<filesystem>)
#	include <filesystem>

namespace fs = std::filesystem;
#elif __has_include(<filesystem>)
#	include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
#else
#	error Not supported
#endif

namespace lml
{
	std::uint32_t application::initialize() noexcept
	{
		if (std::uint32_t errorcode = lml_le::initialize(application::version_int); errorcode) return errorcode;
		if (std::uint32_t errorcode = lml_pae::initialize(); errorcode) return errorcode;

		const lml_pae::string data_directory = lml_pae::get_data_file(STR(""));
		const lml_pae::string options_path = lml_pae::get_data_file(STR("options.lmlo"));
		const lml_pae::string logs_path = lml_pae::get_data_file(STR("logs.lmll"));

		if (!fs::exists(data_directory) && !fs::create_directories(data_directory))
			return LML_ERRORCODE_FAILED_TO_CREATE_APPDATA;
		
		try
		{
			application::options.load(options_path);
		}
		catch (std::uint32_t)
		{}
		application::options.autosave(options_path);

		application::logger.autosave(logs_path);
		application::logger.autosave_include_additional_data(application::options.include_additional_data());

		application::logger.add_log(lml_le::make_message(STR("Initialization succeeded."), lml_le::log_type::info));
		return 0;
	}
}

namespace lml
{
	lml_pae::string make_error_message(std::uint32_t errorcode)
	{
		std::basic_ostringstream<lml_pae::character> oss;
		oss << STR("Error! Please report to the developers.\nErrorcode: 0x") << std::hex << std::setw(8) << std::setfill(STR('0')) << errorcode << ')';
		return oss.str();
	}
}