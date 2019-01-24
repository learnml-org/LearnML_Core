#pragma once
#include <lml_edk/config.hpp>

#include <lml_edk/function_table.hpp>
#include <lml_edk/language.hpp>
#include <lml_edk/matrix.hpp>

#include <any>
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace lml_edk
{
	class LML_EDK_EXPORT layer_base
	{
	public:
		layer_base(const layer_base&) = delete;
		virtual ~layer_base() = default;
		
	protected:
		layer_base() noexcept = default;

	public:
		layer_base& operator=(const layer_base&) = delete;

	public:
		virtual std::uint32_t id() const noexcept = 0;
		virtual global_string name() const = 0;
		virtual global_pair_string description() const = 0;
		virtual const function_table<layer_base>& functions() const = 0;
	};

	inline namespace v1_0_0
	{
		class LML_EDK_EXPORT layer : public layer_base
		{
		public:
			layer(const layer&) = delete;
			virtual ~layer() = default;

		protected:
			layer() noexcept = default;

		public:
			layer& operator=(const layer&) = delete;

		public:
			virtual const function_table<layer_base>& functions() const override final;

			virtual function_result forward(function_parameter arg) = 0;
			virtual function_result backward(function_parameter arg) = 0;
			virtual function_result update(function_parameter arg) = 0;
		};
	}
}