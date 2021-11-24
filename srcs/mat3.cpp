#include "mat3.hpp"

mat3::mat3()
{
	_values = new vec3[3];
	for (int i = 0; i < 3; ++i)
		_values[i] = vec3(0.0f, 0.0f, 0.0f);
}

mat3::mat3(float value)
{
	_values = new vec3[3];
	_values[0] = vec3(value, 0.0f, 0.0f);
	_values[1] = vec3(0.0f, value, 0.0f);
	_values[2] = vec3(0.0f, 0.0f, value);
}

mat3::mat3(const mat3& copy)
{
	_values = new vec3[3];
	*this = copy;
}

mat3	&mat3::operator=(const mat3& other)
{
	if (this != &other)
		for (int i = 0; i < 3; ++i)
			_values[i] = other._values[i];
	return (*this);
}

mat3::~mat3() { delete[] _values; }

vec3	&mat3::operator[](size_t idx)
{
	if (idx > 2)
		throw WrongIndex();
	return _values[idx];
}

vec3	mat3::operator[](size_t idx) const
{
	if (idx > 2)
		throw WrongIndex();
	return _values[idx];
}
