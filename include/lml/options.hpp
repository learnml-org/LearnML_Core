#pragma once

#include <lml_edk/language.hpp>
#include <lml_pae/string.hpp>

namespace lml
{
	class options final
	{
	public:
		options() noexcept = default;
		explicit options(const lml_pae::string& option_path);
		options(const options&) = delete;
		~options();

	public:
		options& operator=(const options&) = delete;

	public:
		void load(const lml_pae::string& option_path);
		void save(const lml_pae::string& option_path) const;

	public:
		lml_pae::string autosave() const;
		void autosave(const lml_pae::string& new_autosave);

		lml_edk::language language() const noexcept;
		void language(lml_edk::language new_language) noexcept;

		bool include_additional_data() const noexcept;
		void include_additional_data(bool new_include_additional_data) noexcept;

	private:
		lml_pae::string autosave_;

		lml_edk::language language_ = lml_edk::language::ko;

		bool include_additional_data_ = false;
	};
}