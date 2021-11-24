#pragma once

#include <iostream>
#include "Color.hpp"
#include "Shape.hpp"

enum Rotation
{
	Rrot,
	Lrot,
	Frot,
	Brot,
	Rr,
	Lr
};

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
		void	rF();
		void	R();
		void	rR();
		void	U();
		void	rU();
		void	B();
		void	rB();
		void	L();
		void	rL();
		void	D();
		void	rD();
		void	print();
};