#pragma once

class Shape;
class mat3;

#include <iostream>
#include "Color.hpp"
#include "Shape.hpp"
#include "mat3.hpp"
#include "utils.hpp"

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
		Cube();
		Cube(const Cube& copy);
		Cube	&operator=(const Cube& other);
	protected:
		int		_size;
		Shape	**_shapes;
	public:
		Cube(int size);
		virtual ~Cube();
		void	print();
		void	rotateFace(int x, int y, int z, mat3 rotmat, Rotation rot);
		class	SizeTooHigh : public std::exception
		{
			public:
				SizeTooHigh();
				virtual const char* what() const throw ();
				virtual ~SizeTooHigh() throw ();
		};
		class	SizeTooLow : public std::exception
		{
			public:
				SizeTooLow();
				virtual const char* what() const throw ();
				virtual ~SizeTooLow() throw ();
		};
};