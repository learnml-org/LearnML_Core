#include <lml_edk/function.hpp>

#include <functional>

namespace lml_edk
{
	function::function(const function& function)
		: data_(function.data_ ? function.data_->copy() : nullptr)
	{}
	function::function(function&& function) noexcept
		: data_(function.data_)
	{
		function.data_ = nullptr;
	}
	function::~function()
	{
		delete data_;
		data_ = nullptr;
	}

	function& function::operator=(const function& function)
	{
		data_ = function.data_ ? function.data_->copy() : nullptr;
		return *this;
	}
	function& function::operator=(function&& function) noexcept
	{
		data_ = function.data_;
		function.data_ = nullptr;
		return *this;
	}
	function_result function::operator()(void* instance, const function_parameter& arg) const
	{
		if (!data_) throw std::bad_function_call();
		else return data_->call(instance, arg);
	}
}

namespace lml_edk
{
	function get_function(const std::string& name, const function_table& table)
	{
		if (table.find(name) == table.end()) return {};
		else return table.at(name).first;
	}
}