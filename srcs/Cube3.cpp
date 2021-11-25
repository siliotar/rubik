#include "Cube3.hpp"

Cube3::Cube3() : Cube(3)
{
	_methods["F"] = &Cube3::F;
	_methods["F\'"] = &Cube3::rF;
	_methods["R"] = &Cube3::R;
	_methods["R\'"] = &Cube3::rR;
	_methods["U"] = &Cube3::U;
	_methods["U\'"] = &Cube3::rU;
	_methods["B"] = &Cube3::B;
	_methods["B\'"] = &Cube3::rB;
	_methods["L"] = &Cube3::L;
	_methods["L\'"] = &Cube3::rL;
	_methods["D"] = &Cube3::D;
	_methods["D\'"] = &Cube3::rD;
}

Cube3::~Cube3() {}

void	Cube3::F() { rotateFace(-1, -1, 2, getZrotmat(-M_PI_2), Rrot); }

void	Cube3::rF() { rotateFace(-1, -1, 2, getZrotmat(M_PI_2), Lrot); }

void	Cube3::R() { rotateFace(2, -1, -1, getXrotmat(-M_PI_2), Frot); }

void	Cube3::rR() { rotateFace(2, -1, -1, getXrotmat(M_PI_2), Brot); }

void	Cube3::U() { rotateFace(-1, 2, -1, getYrotmat(-M_PI_2), Rr); }

void	Cube3::rU() { rotateFace(-1, 2, -1, getYrotmat(M_PI_2), Lr); }

void	Cube3::B() { rotateFace(-1, -1, 0, getZrotmat(M_PI_2), Lrot); }

void	Cube3::rB() { rotateFace(-1, -1, 0, getZrotmat(-M_PI_2), Rrot); }

void	Cube3::L() { rotateFace(0, -1, -1, getXrotmat(M_PI_2), Brot); }

void	Cube3::rL() { rotateFace(0, -1, -1, getXrotmat(-M_PI_2), Frot); }

void	Cube3::D() { rotateFace(-1, 0, -1, getYrotmat(M_PI_2), Lr); }

void	Cube3::rD() { rotateFace(-1, 0, -1, getYrotmat(-M_PI_2), Rr); }

void	Cube3::shuffle(size_t count) { _shuffle(*this, _methods, count); }
