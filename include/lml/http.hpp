#pragma once

#include <lml_pae/string.hpp>

#include <string>
#include <utility>

namespace lml::http
{
	std::string get_host(std::string url);
	std::string get_path(std::string url);
	std::pair<std::string, std::string> get_host_and_path(const std::string& url);

	void download_file(const std::string& url, const lml_pae::string& out_path);
}