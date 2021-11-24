#include "vec3.hpp"

vec3::vec3() : x(0), y(0), z(0) {}

vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}

vec3::vec3(const vec3& copy) : x(copy.x), y(copy.y), z(copy.z) {}

vec3	&vec3::operator=(const vec3& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	return (*this);
}

vec3::~vec3() {}

float	&vec3::operator[](size_t idx)
{
	if (idx == 0)
		return x;
	if (idx == 1)
		return y;
	if (idx == 2)
		return z;
	throw WrongIndex();
}

vec3	operator*(const vec3 &vec, const mat3 &mat)
{
	vec3	res;
	res.x = vec.x * mat[0].x + vec.y * mat[1].x + vec.z * mat[2].x;
	res.y = vec.x * mat[0].y + vec.y * mat[1].y + vec.z * mat[2].y;
	res.z = vec.x * mat[0].z + vec.y * mat[1].z + vec.z * mat[2].z;
	return res;
}
