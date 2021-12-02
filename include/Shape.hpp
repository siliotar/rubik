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
		Shape(const Shape &copy);
		virtual ~Shape();
		void	R();
		void	L();
		void	F();
		void	B();
		void	Lr();
		void	Rr();
		bool	hasColor(Color c);
		bool	equals(Color a = Black, Color b = Black, Color c = Black);
		const Color	&getFirstNot(Color color);
		bool	horisontalEqual(const Shape &other);
};