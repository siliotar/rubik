#include "utils.hpp"

mat3	getXrotmat(float alpha)
{
	mat3	res;

	res[0] = vec3(1.0f, 0.0f, 0.0f);
	res[1] = vec3(0.0f, cos(alpha), -sin(alpha));
	res[2] = vec3(0.0f, sin(alpha), cos(alpha));
	return res;
}

mat3	getYrotmat(float alpha)
{
	mat3	res;

	res[0] = vec3(cos(alpha), 0.0, sin(alpha));
	res[1] = vec3(0.0, 1.0, 0.0);
	res[2] = vec3(-sin(alpha), 0.0, cos(alpha));
	return res;
}

mat3	getZrotmat(float alpha)
{
	mat3	res;

	res[0] = vec3(cos(alpha), -sin(alpha), 0.0);
	res[1] = vec3(sin(alpha), cos(alpha), 0.0);
	res[2] = vec3(0.0, 0.0, 1.0);
	return res;
}
