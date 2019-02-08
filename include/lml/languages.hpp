#pragma once

#include <lml_pae/string.hpp>

#include <map>
#include <string>

namespace lml
{
	class languages final
	{
	public:
		languages() = default;
		explicit languages(const lml_pae::string& path);
		languages(const languages&) = delete;
		~languages() = default;

	public:
		languages& operator=(const languages&) = delete;
		const lml_pae::string& operator[](const std::string& key) const noexcept;
		lml_pae::string& operator[](const std::string& key);

	public:
		void load(const lml_pae::string& path);
		void save(const lml_pae::string& path) const;

	private:
		std::map<std::string, lml_pae::string> strings_;
	};
}