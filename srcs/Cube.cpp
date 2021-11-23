#include "Cube.hpp"

Cube::Cube()
{
	for (size_t x = 0; x < 3; ++x)
	{
		for (size_t y = 0; y < 3; ++y)
		{
			for (size_t z = 0; z < 3; ++z)
			{
				_shapes[x][y][z] = new Shape(y == 2 ? White : Black,
											x == 0 ? Orange : Black,
											z == 0 ? Green : Black,
											x == 2 ? Red : Black,
											z == 2 ? Blue : Black,
											y == 0 ? Yellow : Black);
			}
		}
	}
}

Cube::~Cube()
{}

static void	rotate(Shape &a, Shape &b, Shape &c, Shape &d)
{
	Shape tmp = a;
	a = b;
	b = c;
	c = d;
	d = tmp;
}

void	Cube::F()
{
	rotate(*(_shapes[0][2][0]), *(_shapes[2][2][0]), *(_shapes[2][0][0]), *(_shapes[0][0][0]));
	_shapes[0][2][0]->R();
	_shapes[2][2][0]->R();
	_shapes[2][0][0]->R();
	_shapes[0][0][0]->R();
	rotate(*(_shapes[0][1][0]), *(_shapes[1][2][0]), *(_shapes[2][1][0]), *(_shapes[1][0][0]));
	_shapes[0][1][0]->R();
	_shapes[1][2][0]->R();
	_shapes[2][1][0]->R();
	_shapes[1][0][0]->R();
}

void	Cube::print()
{
	
}
