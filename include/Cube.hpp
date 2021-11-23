#pragma once

#include <stddef.h>
#include "Color.hpp"
#include "Shape.hpp"

class Cube
{
	private:
		Shape	*_shapes[3][3][3];
		Cube(const Cube& copy);
		Cube	&operator=(const Cube& other);
	public:
		Cube();
		virtual ~Cube();
		void	F();
		void	print();
};