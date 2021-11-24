#pragma once

#include "Color.hpp"

class Shape
{
	protected:
	public:
		Color	_up;
		Color	_left;
		Color	_front;
		Color	_right;
		Color	_back;
		Color	_down;
		Shape(Color up, Color left, Color front, Color right, Color back, Color down);
		virtual ~Shape();
		void	R();
		void	L();
		void	F();
		void	B();
		void	Lr();
		void	Rr();
};