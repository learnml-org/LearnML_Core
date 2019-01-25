#pragma once

#include <any>
#include <cstdint>
#include <map>
#include <string>
#include <utility>

namespace lml_edk
{
	using function_result = std::any;
	using function_parameter = std::map<std::string, std::any>;
	
	namespace details
	{
		class function_data
		{
		public:
			function_data(const function_data&) = delete;
			virtual ~function_data() = default;

		protected:
			function_data() noexcept = default;

		public:
			function_data& operator=(const function_data&) = delete;

		public:
			virtual function_data* copy() const = 0;
			virtual function_result call(void* instance, const function_parameter& arg) const = 0;
		};

		template<typename Base_>
		class function_tdata final : public function_data
		{
		public:
			function_tdata(function_result(Base_::*function)(function_parameter)) noexcept
				: function_(function)
			{}
			function_tdata(const function_tdata&) = delete;
			virtual ~function_tdata() override = default;

		public:
			function_tdata& operator=(const function_tdata&) = delete;

		public:
			virtual function_data* copy() const override
			{
				return new function_tdata(function_);
			}
			virtual function_result call(void* instance, const function_parameter& arg) const override
			{
				return (reinterpret_cast<Base_*>(instance)->*function_)(arg);
			}

		private:
			function_result(Base_::*function_)(function_parameter) = nullptr;
		};
	}

	class function final
	{
	public:
		function() noexcept = default;
		template<typename Base_>
		function(function_result(Base_::*function)(function_parameter))
			: data_(new details::function_tdata<Base_>(function))
		{}
		function(const function& function);
		function(function&& function) noexcept;
		~function();

	public:
		function& operator=(const function& function);
		function& operator=(function&& function) noexcept;
		function_result operator()(void* instance, const function_parameter& arg) const;

	private:
		details::function_data* data_ = nullptr;
	};

	using function_table = std::map<std::string, std::pair<function, std::uint64_t>>;
	
	function get_function(const std::string& name, const function_table& table);

	struct no_return_t
	{};
	static inline const no_return_t no_return;
}