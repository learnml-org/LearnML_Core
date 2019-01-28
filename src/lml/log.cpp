#include <lml/log.hpp>

#include <lml/application.hpp>
#include <lml/errorcode.hpp>
#include <lml/platform.hpp>

#include <lml/string.hpp>

#include <fstream>
#include <thread>
#include <utility>
#include <VersionHelpers.h>

namespace lml
{
	log::log(log_type type, log_event event, const std::basic_string<TCHAR>& message, std::chrono::system_clock::time_point time)
		: type(type), event(event), message(message), time(time)
	{}

	void log::save(std::ostream& stream, bool include_additional_data) const
	{
		stream.write(reinterpret_cast<const char*>(&type), sizeof(type));
		stream.write(reinterpret_cast<const char*>(&event), sizeof(event));
		
		const std::uint64_t message_size = static_cast<std::uint64_t>(message.size());
		stream.write(reinterpret_cast<const char*>(&message_size), sizeof(message_size));
		const std::string message_utf8 = encode_utf8(message);
		stream.write(message_utf8.c_str(), static_cast<std::streamsize>(message_size));

		const std::int64_t time = this->time.time_since_epoch().count();
		stream.write(reinterpret_cast<const char*>(&time), sizeof(time));

		save_prtd(stream);
		
		if (include_additional_data)
		{
			save_prtd_additional_data(stream);
		}
	}
}

namespace lml
{
	logger::~logger()
	{
		if (!autosave_.empty())
		{
			save(autosave_, autosave_include_additional_data_);
		}
	}

	void logger::add_log(log_ptr&& log)
	{
		logs_.push_back(std::move(log));
	}

	void logger::save(const std::basic_string<TCHAR>& path) const
	{
		save(path, false);
	}
	void logger::save(const std::basic_string<TCHAR>& path, bool include_additional_data) const
	{
		std::ofstream stream(path);
		for (int i = 0; i < 6 && !stream; ++i)
		{
			using namespace std::chrono_literals;

			if (i == 5) throw LML_ERRORCODE_FAILED_TO_SAVE_LOG;

			stream.open(path);
			std::this_thread::sleep_for(0.5s);
		}

		static constexpr char magic_number[] = { 'L', 'M', 'L', 'L' };
		static constexpr std::uint32_t version = 0;
		static constexpr std::uint32_t bom = 0x12345678;

		// Header (64 Bytes)
		stream.write(magic_number, sizeof(magic_number));															// Magic Number				(4 Bytes)
		stream.write(reinterpret_cast<const char*>(&version), sizeof(version));										// Log System Veresion		(4 Bytes)
		stream.write(reinterpret_cast<const char*>(&bom), sizeof(bom));												// Byte Order Mark			(4 Bytes)
		stream.write(reinterpret_cast<const char*>(&include_additional_data), sizeof(include_additional_data));		//							(1 Bytes)
		stream.write(reinterpret_cast<const char*>(&application::version_int), sizeof(application::version_int));	// Application Version		(8 Bytes)
		
		std::uint8_t buffer_u8 = static_cast<std::uint8_t>(architecture::target);
		stream.write(reinterpret_cast<const char*>(&buffer_u8), sizeof(buffer_u8));									// Platform Architecture	(1 Bytes)
		buffer_u8 = static_cast<std::uint8_t>(os::target);
		stream.write(reinterpret_cast<const char*>(&buffer_u8), sizeof(buffer_u8));									// Platform OS				(1 Bytes)
		const std::string os_name = get_os_name();
		const std::uint64_t os_name_size = static_cast<std::uint64_t>(os_name.size());
		stream.write(reinterpret_cast<const char*>(&os_name_size), sizeof(os_name_size));							// Platform OS Name Size	(8 Bytes)
		stream.write(os_name.c_str(), static_cast<std::streamsize>(os_name_size));									// Platform OS Name

		// Logs
		const std::uint64_t count_of_logs(logs_.size());
		stream.write(reinterpret_cast<const char*>(&count_of_logs), sizeof(count_of_logs));							//							(8 Bytes)
		
		for (const log_ptr& l : logs_)
		{
			l->save(stream, include_additional_data);
		}
	}

	std::basic_string<TCHAR> logger::autosave() const
	{
		return autosave_;
	}
	void logger::autosave(const std::basic_string<TCHAR>& new_autosave)
	{
		autosave_ = new_autosave;
	}
	bool logger::autosave_include_additional_data() const noexcept
	{
		return autosave_include_additional_data_;
	}
	void logger::autosave_include_additional_data(bool new_autosave_include_additional_data) noexcept
	{
		autosave_include_additional_data_ = new_autosave_include_additional_data;
	}
}