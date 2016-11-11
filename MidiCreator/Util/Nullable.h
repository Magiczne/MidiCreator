#pragma once

//http://stackoverflow.com/a/28811646/7101876

#include "..\stdafx.h"

template<typename T>
class Nullable final
{
	template<typename T2>
	friend bool operator==(const Nullable<T2>& lhs, const Nullable<T2>& rhs);

	template<typename T2>
	friend bool operator==(const Nullable<T2>& lhs, const T2& rhs);

	template<typename T2>
	friend bool operator==(const T2& lhs, const Nullable<T2>& rhs);

	template<typename T2>
	friend bool operator==(const Nullable<T2>& lhs, nullptr_t rhs);

	template<typename T2>
	friend bool operator==(nullptr_t lhs, const Nullable<T2>& rhs);

private:
	bool _hasValue;
	T _value;

public:
	const T& Value;

	Nullable();
	Nullable(const T& val);
	Nullable(nullptr_t np);

	const Nullable<T>& operator=(const Nullable<T>& val);
	const Nullable<T>& operator=(const T& val);
	const Nullable<T>& operator=(nullptr_t np);
};

template<typename T>
Nullable<T>::Nullable() :
	_hasValue(false), _value(T()), Value(_value) {}

template<typename T>
Nullable<T>::Nullable(const T& val) :
	_hasValue(true), _value(val), Value(_value) {}

template<typename T>
Nullable<T>::Nullable(nullptr_t np) :
	_hasValue(false), _value(T()), Value(_value)
{
	(void)np;
}

template<typename T2>
bool operator==(const Nullable<T2>& lhs, const Nullable<T2>& rhs)
{
	if (lhs._hasValue != rhs._hasValue)
	{
		return false;
	}

	if (lhs._hasValue)
	{
		return lhs._value == rhs._value;
	}
	else
	{
		return true;
	}
}

template <typename T2>
bool operator==(const Nullable<T2>& lhs, const T2& rhs)
{
	if (!lhs._hasValue)
	{
		return false;
	}

	return lhs._value == rhs;
}

template <typename T2>
bool operator==(const T2& lhs, const Nullable<T2>& rhs)
{
	if (!rhs._hasValue)
	{
		return false;
	}

	return lhs == rhs._value;
}

template <typename T2>
bool operator==(const Nullable<T2>& lhs, nullptr_t rhs)
{
	(void)rhs;

	return !lhs._hasValue;
}

template <typename T2>
bool operator==(nullptr_t lhs, const Nullable<T2>& rhs)
{
	(void)lhs;

	return !rhs._hasValue;
}

template<typename T>
const Nullable<T>& Nullable<T>::operator=(const Nullable<T>& val)
{
	_hasValue = val._hasValue;
	_value = val._value;
	return *this;
}

template<typename T>
const Nullable<T>& Nullable<T>::operator=(const T& val)
{
	_hasValue = true;
	_value = val;
	return *this;
}

template<typename T>
const Nullable<T>& Nullable<T>::operator=(nullptr_t np)
{
	(void)np;
	_hasValue = false;
	_value = T();
	return *this;
}