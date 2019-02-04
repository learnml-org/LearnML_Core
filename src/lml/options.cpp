#include <lml/options.hpp>

#include <lml/errorcode.hpp>
#include <nlohmann/json.hpp>

#include <fstream>

namespace lml
{
	options::options(const std::basic_string<TCHAR>& option_path)
	{
		load(option_path);
	}
	options::~options()
	{
		if (!autosave_.empty())
		{
			save(autosave_);
		}
	}

	void options::load(const std::basic_string<TCHAR>& option_path)
	{
		std::ifstream stream(option_path);
		if (!stream) throw LML_ERRORCODE_FAILED_TO_OPEN_OPTION_FILE;

		nlohmann::json root;
		stream >> root;
		stream.close();
		
		language_ = static_cast<lml_edk::language>(root["language"].get<int>());

		const nlohmann::json& privacy = root["privacy"];
		include_additional_data_ = privacy["include_additional_data"].get<bool>();
	}
	void options::save(const std::basic_string<TCHAR>& option_path) const
	{
		std::ofstream stream(option_path);
		if (!stream) throw LML_ERRORCODE_FAILED_TO_CREATE_OPTION_FILE;

		nlohmann::json option =
		{
			{ "language", static_cast<int>(language_) },
			{ "privacy",
				{
					{ "include_additional_data", include_additional_data_ }
				}
			}
		};
		stream << option;
		stream.close();
	}

	std::basic_string<TCHAR> options::autosave() const
	{
		return autosave_;
	}
	void options::autosave(const std::basic_string<TCHAR>& new_autosave)
	{
		autosave_ = new_autosave;
	}

	lml_edk::language options::language() const noexcept
	{
		return language_;
	}
	void options::language(lml_edk::language new_language) noexcept
	{
		language_ = new_language;
	}

	bool options::include_additional_data() const noexcept
	{
		return include_additional_data_;
	}
	void options::include_additional_data(bool new_include_additional_data) noexcept
	{
		include_additional_data_ = new_include_additional_data;
	}
}