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

static void	rotate(Shape *&a, Shape *&b, Shape *&c, Shape *&d, Rotation rot)
{
	Shape *tmp = a;
	a = b;
	b = c;
	c = d;
	d = tmp;
	switch (rot)
	{
	case Rrot:
		a->R();
		b->R();
		c->R();
		d->R();
		break;
	case Lrot:
		a->L();
		b->L();
		c->L();
		d->L();
		break;
	case Frot:
		a->F();
		b->F();
		c->F();
		d->F();
		break;
	case Brot:
		a->B();
		b->B();
		c->B();
		d->B();
		break;
	case Rr:
		a->Rr();
		b->Rr();
		c->Rr();
		d->Rr();
		break;
	case Lr:
		a->Lr();
		b->Lr();
		c->Lr();
		d->Lr();
		break;
	default:
		break;
	}
}

void	Cube::F()
{
	rotate(_shapes[0][2][0], _shapes[0][0][0], _shapes[2][0][0], _shapes[2][2][0], Rrot);
	rotate(_shapes[0][1][0], _shapes[1][0][0], _shapes[2][1][0], _shapes[1][2][0], Rrot);
}

void	Cube::rF() { F(); F(); F(); }

void	Cube::R()
{
	rotate(_shapes[2][0][0], _shapes[2][0][2], _shapes[2][2][2], _shapes[2][2][0], Frot);
	rotate(_shapes[2][1][0], _shapes[2][0][1], _shapes[2][1][2], _shapes[2][2][1], Frot);
}

void	Cube::rR() { R(); R(); R(); }

void	Cube::U()
{
	rotate(_shapes[0][2][0], _shapes[2][2][0], _shapes[2][2][2], _shapes[0][2][2], Rr);
	rotate(_shapes[1][2][0], _shapes[2][2][1], _shapes[1][2][2], _shapes[0][2][1], Rr);
}

void	Cube::rU() { U(); U(); U(); }

void	Cube::B()
{
	rotate(_shapes[0][0][2], _shapes[0][2][2], _shapes[2][2][2], _shapes[2][0][2], Lrot);
	rotate(_shapes[0][1][2], _shapes[1][2][2], _shapes[2][1][2], _shapes[1][0][2], Lrot);
}

void	Cube::rB() { B(); B(); B(); }

void	Cube::L()
{
	rotate(_shapes[0][0][0], _shapes[0][2][0], _shapes[0][2][2], _shapes[0][0][2], Brot);
	rotate(_shapes[0][0][1], _shapes[0][1][0], _shapes[0][2][1], _shapes[0][1][2], Brot);
}

void	Cube::rL() { L(); L(); L(); }

void	Cube::D()
{
	rotate(_shapes[0][0][0], _shapes[0][0][2], _shapes[2][0][2], _shapes[2][0][0], Lr);
	rotate(_shapes[1][0][0], _shapes[0][0][1], _shapes[1][0][2], _shapes[2][0][1], Lr);
}

void	Cube::rD() { D(); D(); D(); }


void	Cube::print()
{
	std::cout << "\t\t\t" << _shapes[0][2][2]->_up << "\t" << _shapes[1][2][2]->_up << "\t" << _shapes[2][2][2]->_up << "\t" << std::endl;
	std::cout << "\t\t\t" << _shapes[0][2][1]->_up << "\t" << _shapes[1][2][1]->_up << "\t" << _shapes[2][2][1]->_up << "\t" << std::endl;
	std::cout << "\t\t\t" << _shapes[0][2][0]->_up << "\t" << _shapes[1][2][0]->_up << "\t" << _shapes[2][2][0]->_up << "\t" << std::endl;

	std::cout << _shapes[0][2][2]->_left << "\t" << _shapes[0][2][1]->_left << "\t" << _shapes[0][2][0]->_left << "\t";
	std::cout << _shapes[0][2][0]->_front << "\t" << _shapes[1][2][0]->_front << "\t" << _shapes[2][2][0]->_front << "\t";
	std::cout << _shapes[2][2][0]->_right << "\t" << _shapes[2][2][1]->_right << "\t" << _shapes[2][2][2]->_right << "\t";
	std::cout << _shapes[2][2][2]->_back << "\t" << _shapes[1][2][2]->_back << "\t" << _shapes[0][2][2]->_back << "\t" << std::endl;

	std::cout << _shapes[0][1][2]->_left << "\t" << _shapes[0][1][1]->_left << "\t" << _shapes[0][1][0]->_left << "\t";
	std::cout << _shapes[0][1][0]->_front << "\t" << _shapes[1][1][0]->_front << "\t" << _shapes[2][1][0]->_front << "\t";
	std::cout << _shapes[2][1][0]->_right << "\t" << _shapes[2][1][1]->_right << "\t" << _shapes[2][1][2]->_right << "\t";
	std::cout << _shapes[2][1][2]->_back << "\t" << _shapes[1][1][2]->_back << "\t" << _shapes[0][1][2]->_back << "\t" << std::endl;

	std::cout << _shapes[0][0][2]->_left << "\t" << _shapes[0][0][1]->_left << "\t" << _shapes[0][0][0]->_left << "\t";
	std::cout << _shapes[0][0][0]->_front << "\t" << _shapes[1][0][0]->_front << "\t" << _shapes[2][0][0]->_front << "\t";
	std::cout << _shapes[2][0][0]->_right << "\t" << _shapes[2][0][1]->_right << "\t" << _shapes[2][0][2]->_right << "\t";
	std::cout << _shapes[2][0][2]->_back << "\t" << _shapes[1][0][2]->_back << "\t" << _shapes[0][0][2]->_back << "\t" << std::endl;

	std::cout << "\t\t\t" << _shapes[0][0][0]->_down << "\t" << _shapes[1][0][0]->_down << "\t" << _shapes[2][0][0]->_down << "\t" << std::endl;
	std::cout << "\t\t\t" << _shapes[0][0][1]->_down << "\t" << _shapes[1][0][1]->_down << "\t" << _shapes[2][0][1]->_down << "\t" << std::endl;
	std::cout << "\t\t\t" << _shapes[0][0][2]->_down << "\t" << _shapes[1][0][2]->_down << "\t" << _shapes[2][0][2]->_down << "\t" << std::endl;
}
