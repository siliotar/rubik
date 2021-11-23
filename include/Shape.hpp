#pragma once

#include "Color.hpp"

class Shape
{
	protected:
		Color	_up;
		Color	_left;
		Color	_front;
		Color	_right;
		Color	_back;
		Color	_down;
	public:
		Shape(Color up, Color left, Color front, Color right, Color back, Color down);
		virtual ~Shape() {}
		void	R();
		void	L();
		void	F();
		void	B();
};