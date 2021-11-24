#pragma once

class vec3;

#include <exception>
#include <stddef.h>
#include "vec3.hpp"

class mat3
{
	private:
		vec3	*_values;
	public:
		mat3();
		mat3(float value);
		mat3(const mat3& copy);
		mat3	&operator=(const mat3& other);
		virtual ~mat3();
		class	WrongIndex : public std::exception
		{
			public:
				WrongIndex() {}
				virtual const char*	what() const throw () { return "wrong index"; }
				virtual ~WrongIndex() throw () {}
		};
		vec3	&operator[](size_t idx);
		vec3	operator[](size_t idx) const;
};