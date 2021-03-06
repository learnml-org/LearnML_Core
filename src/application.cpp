#include <lml/application.hpp>

#include <lml/errorcode.hpp>
#include <lml_le/engine.hpp>
#include <lml_pae/engine.hpp>
#include <lml_pae/filesystem.hpp>
#include <lml_pae/os.hpp>

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
		const lml_pae::string options_path = lml_pae::get_data_file(STR("options.json"));
		const lml_pae::string logs_path = lml_pae::get_data_file(STR("logs.bin"));

		if (!fs::exists(data_directory) && !fs::create_directories(data_directory))
			return LML_ERRORCODE_FAILED_TO_CREATE_APPDATA;
		
		try
		{
			application::options.load(options_path);
		}
		catch (std::uint32_t)
		{}
		application::options.autosave(options_path);

		try
		{
#if defined(LML_PAE_WINDOWS)
#if defined(UNICODE) || defined(_UNICODE)
			application::languages.load(lml_pae::get_data_file(STR("lang\\") + std::to_wstring(static_cast<int>(application::options.language()))) + STR(".json"));
#else
			application::languages.load(lml_pae::get_data_file(STR("lang\\") + std::to_string(static_cast<int>(application::options.language()))) + STR(".json"));
#endif
#else
			application::languages.load(lml_pae::get_data_file(STR("lang/") + std::to_string(static_cast<int>(application::options.language()))) + STR(".json"));
#endif
		}
		catch (std::uint32_t errorcode)
		{
			return errorcode;
		}

		application::logger.autosave(logs_path);
		application::logger.autosave_include_additional_data(application::options.include_additional_data());

		application::logger.add_log(lml_le::make_message(STR("Initialization succeeded."), lml_le::log_type::info));
		return 0;
	}
}