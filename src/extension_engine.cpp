#include <lml/extension_engine.hpp>

#include <lml/application.hpp>
#include <lml/errorcode.hpp>

#include <algorithm>
#include <memory>
#include <stdexcept>

namespace lml
{
	std::uint64_t extension_engine::add_extension(const lml_pae::string& path)
	{
		lml_pae::dll_handle library = lml_pae::open_dll(path);
		if (!library) throw LML_ERRORCODE_FAILED_TO_OPEN_EXTENSION;

		lml_edk::extension_base_ptr extension;
		std::shared_ptr<void> library_raii(library, [&extension](void* module)
		{
			if (!extension)
			{
				lml_pae::close_dll(module);
			}
		});
		if (std::find_if(extensions_.begin(), extensions_.end(), [library](const std::pair<std::uint64_t, std::pair<lml_edk::extension_base_ptr, lml_pae::dll_handle>>& pair)
			{
				return library == pair.second.second;
			}) != extensions_.end()) throw LML_ERRORCODE_ALREADY_LOADED_EXTENSION;

		void*(*allocate_function)() = lml_pae::get_function_from_dll<void*(*)()>(library, "allocate_function");
		if (!allocate_function) throw LML_ERRORCODE_FAILED_TO_LOAD_EXTENSION_ENTRYPOINT;

		extension = lml_edk::extension_base_ptr(reinterpret_cast<lml_edk::extension_base*>(allocate_function()));
		if (!extension) throw LML_ERRORCODE_FAILED_TO_CREATE_EXTENSION_INSTANCE;

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