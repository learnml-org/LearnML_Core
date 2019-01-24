#pragma once
#include <lml_edk/config.hpp>

#include <lml_edk/function_table.hpp>
#include <lml_edk/language.hpp>
#include <lml_edk/matrix.hpp>
#include <lml_edk/type.hpp>

#include <any>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

namespace lml_edk
{
	class layer_base;

	class LML_EDK_EXPORT layer_allocator
	{
	public:
		layer_allocator(const layer_allocator&) = delete;
		virtual ~layer_allocator() = default;

	protected:
		layer_allocator() noexcept = default;

	public:
		layer_allocator& operator=(const layer_allocator&) = delete;

	public:
		virtual std::shared_ptr<layer_base> allocate(function_parameter arg) const = 0;
		virtual std::vector<std::tuple<std::basic_string<TCHAR>, type, global_string, bool>> constructor_parameters() const = 0;

		virtual std::uint32_t id() const;
		virtual global_string name() const;
		virtual global_pair_string description() const;
	};

	using layer_allocator_ptr = std::shared_ptr<const layer_allocator>;

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
		virtual layer_allocator_ptr allocator() const = 0;
	};

	inline namespace v1_0_0
	{
		class LML_EDK_EXPORT layer : public layer_base
		{
		public:
			layer(const layer&) = delete;
			virtual ~layer() override = default;

		protected:
			layer() noexcept = default;

		public:
			layer& operator=(const layer&) = delete;

		public:
			virtual const function_table<layer_base>& functions() const override final;

			// Parameter:
			// - x: matrix
			// Result: no_return_t
			virtual function_result forward(function_parameter arg) = 0;
			// Parameter:
			// - g: matrix
			// Result: no_return_t
			virtual function_result backward(function_parameter arg) = 0;
			// Parameter:
			// - lr: double
			// Result: no_return_t
			virtual function_result update(function_parameter arg) = 0;
		};
	}
}