#pragma once

#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include "vec3.hpp"

#define COMMANDLINE		0b00001
#define SHUFFLE			0b00010
#define VISUALIZE		0b00100
#define BEGINNERALGO	0b01000
#define TEST			0b10000

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
std::string		readFile(const std::string &filePath);
