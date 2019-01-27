#include <lml/logs/external_error.hpp>

#include <lml/string.hpp>

#include <cstring>
#include <memory>

namespace lml::logs
{
	external_error::external_error(LML_LOG_BASE_PARAM, const std::exception& exception)
		: LML_LOG_BASE_INIT(log_type::error, log_event::external_error), exception(exception)
	{}

	void external_error::save_prtd(std::ostream& stream) const
	{
		const std::string what = exception.what();
		const std::string what_utf8 = encode_utf8(what);
		const std::uint64_t what_size = static_cast<std::uint64_t>(what_utf8.size());

		stream.write(reinterpret_cast<const char*>(&what_size), sizeof(what_size));
		stream.write(what_utf8.c_str(), static_cast<std::streamsize>(what_size));
	}
	void external_error::save_prtd_additional_data(std::ostream&) const
	{}

	log_ptr make_external_error(LML_LOG_BASE_PARAM_MAKE_FUNC, const std::exception& exception)
	{
		return std::make_unique<external_error>(LML_LOG_BASE_INIT_MAKE_FUNC, exception);
	}
}