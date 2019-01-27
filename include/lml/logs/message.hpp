#pragma once

#include <lml/log.hpp>

namespace lml::logs
{
	class message final : public log
	{
	public:
		message(LML_LOG_BASE_PARAM, log_type type);
		message(const message&) = delete;
		virtual ~message() override = default;

	public:
		message& operator=(const message&) = delete;

	protected:
		virtual void save_prtd(std::ostream& stream) const override;
		virtual void save_prtd_additional_data(std::ostream& stream) const override;
	};

	log_ptr make_message(LML_LOG_BASE_PARAM_MAKE_FUNC, log_type type);
}