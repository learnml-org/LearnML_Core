#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>
#include <variant>

namespace lml_edk
{
	template<typename Ty_>
	class ok final
	{
	public:
		ok(const Ty_& value) noexcept(std::is_nothrow_copy_assignable_v<Ty_>)
			: value(value)
		{}
		ok(Ty_&& value) noexcept(std::is_nothrow_move_assignable_v<Ty_>)
			: value(std::move(value))
		{}
		ok(const ok& ok) noexcept(std::is_nothrow_copy_constructible_v<Ty_>)
			: value(ok.value)
		{}
		ok(ok&& ok) noexcept(std::is_nothrow_move_constructible_v<Ty_>)
			: value(std::move(ok.value))
		{}
		~ok() = default;

	public:
		ok& operator=(const ok&) = delete;

	public:
		Ty_ value;
	};

	template<typename Ty_>
	class error final
	{
	public:
		error(const Ty_& value) noexcept(std::is_nothrow_copy_assignable_v<Ty_>)
			: value(value)
		{}
		error(Ty_&& value) noexcept(std::is_nothrow_move_assignable_v<Ty_>)
			: value(std::move(value))
		{}
		error(const error& error) noexcept(std::is_nothrow_copy_constructible_v<Ty_>)
			: value(error.value)
		{}
		error(error&& error) noexcept(std::is_nothrow_move_constructible_v<Ty_>)
			: value(std::move(error.value))
		{}
		~error() = default;

	public:
		error& operator=(const error&) = delete;

	public:
		Ty_ value;
	};

	template<typename Ok_, typename Error_ = std::uint32_t>
	class result final
	{
	public:
		using value_type = Ok_;
		using error_type = Error_;

	private:
		using data_type_ = std::variant<ok<Ok_>, error<Error_>>;

	public:
		result(const ok<Ok_>& ok) noexcept(std::is_nothrow_constructible_v<data_type_, const lml_edk::ok<Ok_>&>)
			: data_(ok)
		{}
		result(ok<Ok_>&& ok) noexcept(std::is_nothrow_constructible_v<data_type_, lml_edk::ok<Ok_>&&>)
			: data_(std::move(ok))
		{}
		result(const error<Error_>& error) noexcept(std::is_nothrow_constructible_v<data_type_, const lml_edk::error<Error_>&>)
			: data_(error)
		{}
		result(error<Error_>&& error) noexcept(std::is_nothrow_constructible_v<data_type_, lml_edk::error<Error_>&&>)
			: data_(std::move(error))
		{}
		result(const result& result) noexcept(std::is_nothrow_copy_constructible_v<data_type_>)
			: data_(result.data_)
		{}
		result(result&& result) noexcept(std::is_nothrow_move_constructible_v<data_type_>)
			: data_(std::move(result.data_))
		{}
		~result() = default;

	public:
		result& operator=(const result& result) noexcept(std::is_nothrow_copy_assignable_v<data_type_>)
		{
			data_ = result.data_;
			return *this;
		}
		result& operator=(result&& result) noexcept(std::is_nothrow_move_assignable_v<data_type_>)
		{
			data_ = std::move(result.data_);
			return *this;
		}

	public:
		bool is_ok() const noexcept
		{
			return data_.index() == 0;
		}
		bool is_error() const noexcept
		{
			return data_.index() == 1;
		}

		Ok_& unwrap()
		{
			if (is_error()) throw std::get<1>(data_).value;
			else return std::get<0>(data_).value;
		}

	private:
		data_type_ data_;
	};
}