#include "Shape.hpp"

Shape::Shape(Color up, Color left, Color front, Color right, Color back, Color down) :
_up(up),
_left(left),
_front(front),
_right(right),
_back(back),
_down(down)
{}

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

