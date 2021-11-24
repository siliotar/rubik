#include "Shape.hpp"

Shape::Shape(float x, float y, float z, unsigned int size) : _x(x), _y(y), _z(z), _size(size)
{
	_up = y + 0.5f >= (float)size / 2 ? White : Black;
	_left = x - 1.5f <= -(float)size / 2 ? Orange : Black;
	_front = z - 1.5f <= -(float)size / 2 ? Green : Black;
	_right = x + 0.5f >= (float)size / 2 ? Red : Black;
	_back = z + 0.5f >= (float)size / 2 ? Blue : Black;
	_down = y - 1.5f <= -(float)size / 2 ? Yellow : Black;
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

