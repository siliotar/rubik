#include "Cube3.hpp"

Cube3::Cube3() : Cube(3)
{}

Cube3::~Cube3()
{}

void	Cube3::F()
{
	rotateFace(-1, -1, 2, getZrotmat(-M_PI_2), Rrot);
}

void	Cube3::rF()
{
	rotateFace(-1, -1, 2, getZrotmat(M_PI_2), Lrot);
}

void	Cube3::R()
{
	rotateFace(2, -1, -1, getXrotmat(-M_PI_2), Frot);
}

void	Cube3::rR()
{
	rotateFace(2, -1, -1, getXrotmat(M_PI_2), Brot);
}

void	Cube3::U()
{
	rotateFace(-1, 2, -1, getYrotmat(-M_PI_2), Rr);
}

void	Cube3::rU()
{
	rotateFace(-1, 2, -1, getYrotmat(M_PI_2), Lr);
}

void	Cube3::B()
{
	rotateFace(-1, -1, 0, getZrotmat(M_PI_2), Lrot);
}

void	Cube3::rB()
{
	rotateFace(-1, -1, 0, getZrotmat(-M_PI_2), Rrot);
}

void	Cube3::L()
{
	rotateFace(0, -1, -1, getXrotmat(M_PI_2), Brot);
}

void	Cube3::rL()
{
	rotateFace(0, -1, -1, getXrotmat(-M_PI_2), Frot);
}

void	Cube3::D()
{
	rotateFace(-1, 0, -1, getYrotmat(M_PI_2), Lr);
}

void	Cube3::rD()
{
	rotateFace(-1, 0, -1, getYrotmat(-M_PI_2), Rr);
}
