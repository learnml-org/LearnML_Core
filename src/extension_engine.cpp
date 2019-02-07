#include <lml/extension_engine.hpp>

#include <lml/application.hpp>

#include <algorithm>
#include <memory>
#include <stdexcept>

namespace lml
{
	std::uint64_t extension_engine::add_extension(const std::basic_string<TCHAR>& path)
	{
		HMODULE library = LoadLibrary(path.c_str());
		lml_edk::extension_base_ptr extension;
		if (!library) throw std::runtime_error("Failed to load extension.");
		std::shared_ptr<void> library_raii(library, [&extension](void* module)
		{
			if (!extension)
			{
				FreeLibrary(reinterpret_cast<HMODULE>(module));
			}
		});
		if (std::find_if(extensions_.begin(), extensions_.end(), [library](const std::pair<std::uint64_t, std::pair<lml_edk::extension_base_ptr, HMODULE>>& pair)
			{
				return library == pair.second.second;
			}) != extensions_.end()) throw std::runtime_error("This extension has already added.");

		void*(*allocate_extension)() = reinterpret_cast<void*(*)()>(GetProcAddress(library, "allocate_extension"));
		if (!allocate_extension) throw std::runtime_error("This extension has no entrypoint.");

		extension = lml_edk::extension_base_ptr(reinterpret_cast<lml_edk::extension_base*>(allocate_extension()));
		if (!extension) throw std::runtime_error("Failed to create instance.");

		static std::uint64_t last_id = 0;
		extensions_.insert(std::make_pair(last_id++, std::make_pair(extension, library)));

		auto enabled = lml_edk::get_function("enabled", extension->functions());
		enabled(extension.get(), { { "version", application::version_int }  });

		return last_id - 1;
	}
	lml_edk::extension_base_ptr extension_engine::get_extension(std::uint64_t id) const noexcept
	{
		return extensions_.at(id).first;
	}
	std::uint64_t extension_engine::get_id(const lml_edk::extension_base_ptr& extension) const noexcept
	{
		return std::find_if(extensions_.begin(), extensions_.end(), [&extension](auto pair)
		{
			return pair.second.first == extension;
		})->first;
	}
}