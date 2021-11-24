#pragma once

#include "Color.hpp"

class Shape
{
	protected:
		float			_x;
		float			_y;
		float			_z;
		unsigned int	_size;
	public:
		Color	_up;
		Color	_left;
		Color	_front;
		Color	_right;
		Color	_back;
		Color	_down;
		Shape(float x, float y, float z, unsigned int size);
		virtual ~Shape();
		void	R();
		void	L();
		void	F();
		void	B();
		void	Lr();
		void	Rr();
};