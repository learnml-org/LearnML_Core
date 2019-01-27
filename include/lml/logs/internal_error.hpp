#pragma once

#include <lml/log.hpp>

#include <cstdint>

namespace lml::logs
{
	class internal_error final : public log
	{
	public:
		internal_error(LML_LOG_BASE_PARAM, std::uint32_t errorcode);
		internal_error(const internal_error&) = delete;
		virtual ~internal_error() override = default;

	public:
		internal_error& operator=(const internal_error&) = delete;

	protected:
		virtual void save_prtd(std::ostream& stream) const override;
		virtual void save_prtd_additional_data(std::ostream& stream) const override;

	public:
		std::uint32_t errorcode;
	};
	
	log_ptr make_internal_error(LML_LOG_BASE_PARAM_MAKE_FUNC, std::uint32_t errorcode);
}