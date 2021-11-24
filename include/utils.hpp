#pragma once

#include <cmath>
#include "vec3.hpp"

template <typename T>
void	swap(T &a, T &b)
{
	T	&tmp = a;
	a = b;
	b = tmp;
}

mat3	getXrotmat(float alpha);
mat3	getYrotmat(float alpha);
mat3	getZrotmat(float alpha);
