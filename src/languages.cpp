#include <lml/languages.hpp>

#include <lml/errorcode.hpp>
#include <lml_pae/string.hpp>
#include <nlohmann/json.hpp>

#include <cassert>
#include <fstream>

namespace lml
{
	languages::languages(const lml_pae::string& path)
	{
		load(path);
	}

	const lml_pae::string& languages::operator[](const std::string& key) const noexcept
	{
		assert(strings_.find(key) != strings_.end());
		return strings_.at(key);
	}
	lml_pae::string& languages::operator[](const std::string& key)
	{
		return strings_[key];
	}

	void languages::load(const lml_pae::string& path)
	{
		std::ifstream stream(path);
		if (!stream) throw LML_ERRORCODE_FAILED_TO_OPEN_LANGUAGE_FILE;

		nlohmann::json lang;
		stream >> lang;
		stream.close();

		for (auto iter = lang.begin(); iter != lang.end(); ++iter)
		{
			strings_[iter.key()] = lml_pae::from_utf8(iter.value().get<std::string>());
		}
	}
	void languages::save(const lml_pae::string& path) const
	{
		nlohmann::json lang;

		for (auto iter = strings_.begin(); iter != strings_.end(); ++iter)
		{
			lang[iter->first] = lml_pae::to_utf8(iter->second);
		}

		std::ofstream stream(path);
		if (!stream) throw LML_ERRORCODE_FAILED_TO_CREATE_LANGUAGE_FILE;

		stream << lang;
		stream.close();
	}
}