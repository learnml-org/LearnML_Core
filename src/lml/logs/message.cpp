#include <lml/logs/message.hpp>

namespace lml::logs
{
	message::message(LML_LOG_BASE_PARAM, log_type type)
		: LML_LOG_BASE_INIT(type, log_event::message)
	{}

	void message::save_prtd(std::ostream&) const
	{}
	void message::save_prtd_additional_data(std::ostream&) const
	{}

	log_ptr logs::make_message(LML_LOG_BASE_PARAM_MAKE_FUNC, log_type type)
	{
		return std::make_unique<logs::message>(LML_LOG_BASE_INIT_MAKE_FUNC, type);
	}
}