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

Shape::Shape(const Shape &copy) :
_up(copy._up),
_left(copy._left),
_front(copy._front),
_right(copy._right),
_back(copy._back),
_down(copy._down)
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

bool	Shape::hasColor(Color c)
{
	return _up == c || _left == c || _front == c || _right == c || _back == c || _down == c;
}

bool	Shape::equals(Color a, Color b, Color c)
{
	return hasColor(a) && hasColor(b) && hasColor(c);
}

const Color	&Shape::getFirstNot(Color color)
{
	return _up != Black && _up != color ? _up : _left != Black && _left != color ? _left : _front != Black && _front != color ? _front \
	: _right != Black && _right != color ? _right : _back != Black && _back != color ? _back : _down;
}

bool	Shape::horisontalEqual(const Shape &other)
{
	return _left == other._left && _back == other._back \
	&& _right == other._right && _front == other._front;
}
