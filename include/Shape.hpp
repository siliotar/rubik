#pragma once

#include "Color.hpp"

class Shape
{
	public:
		Color	_up;
		Color	_left;
		Color	_front;
		Color	_right;
		Color	_back;
		Color	_down;
		Shape(int x, int y, int z, int size);
		virtual ~Shape();
		void	R();
		void	L();
		void	F();
		void	B();
		void	Lr();
		void	Rr();
};