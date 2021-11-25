#include "Shape.hpp"
#include <iostream>
Shape::Shape(int x, int y, int z, int size)
{
	_up = y == size - 1 ? White : Black;
	_left = x == 0 ? Orange : Black;
	_front = z == size - 1 ? Green : Black;
	_right = x == size - 1 ? Red : Black;
	_back = z == 0 ? Blue : Black;
	_down = y == 0 ? Yellow : Black;
}

Shape::~Shape()
{}

static void	rotate(Color &a, Color &b, Color &c, Color &d)
{
	Color tmp = a;
	a = b;
	b = c;
	c = d;
	d = tmp;
}

void	Shape::R()
{
	rotate(_up, _left, _down, _right);
}

void	Shape::L()
{
	rotate(_up, _right, _down, _left);
}

void	Shape::F()
{
	rotate(_up, _front, _down, _back);
}

void	Shape::B()
{
	rotate(_up, _back, _down, _front);
}

void	Shape::Lr()
{
	rotate(_back, _right, _front, _left);
}

void	Shape::Rr()
{
	rotate(_back, _left, _front, _right);
}

