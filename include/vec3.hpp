#pragma once

class mat3;

#include <exception>
#include <stddef.h>
#include "mat3.hpp"

class vec3
{
	public:
		float	x;
		float	y;
		float	z;
		vec3();
		vec3(float x, float y, float z);
		vec3(const vec3& copy);
		vec3	&operator=(const vec3& other);
		virtual ~vec3();
		float	&operator[](size_t idx);
		class	WrongIndex : public std::exception
		{
			public:
				WrongIndex() {}
				virtual const char*	what() const throw () { return "wrong index"; }
				virtual ~WrongIndex() throw () {}
		};
		friend vec3	operator*(const vec3 &vec, const mat3 &mat);
};