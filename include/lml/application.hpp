#pragma once

#include <lml/options.hpp>
#include <lml_le/external_error.hpp>
#include <lml_le/internal_error.hpp>
#include <lml_le/log.hpp>
#include <lml_le/message.hpp>
#include <lml_pae/string.hpp>

#include <cstdint>

namespace lml
{
	class application final
	{
	public:
		application() = delete;
		application(const application&) = delete;
		~application() = delete;

	public:
		application& operator=(const application&) = delete;

	public:
		static constexpr const lml_pae::character* name = STR("LearnML");
		static constexpr const lml_pae::character* title = STR("LearnML 1.0.0");
		static constexpr int version[] = { 1, 0, 0 };
		static constexpr std::uint64_t version_int = 0;

		static inline lml_le::logger logger;
		static inline lml::options options;

	public:
		static std::uint32_t initialize() noexcept;
	};
}