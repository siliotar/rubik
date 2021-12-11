#include "Cube3.hpp"

Cube3::Cube3() : Cube(3)
{
	_shuffleMethods["F"] = &Cube3::F;
	_shuffleMethods["F\'"] = &Cube3::rF;
	_shuffleMethods["R"] = &Cube3::R;
	_shuffleMethods["R\'"] = &Cube3::rR;
	_shuffleMethods["U"] = &Cube3::U;
	_shuffleMethods["U\'"] = &Cube3::rU;
	_shuffleMethods["B"] = &Cube3::B;
	_shuffleMethods["B\'"] = &Cube3::rB;
	_shuffleMethods["L"] = &Cube3::L;
	_shuffleMethods["L\'"] = &Cube3::rL;
	_shuffleMethods["D"] = &Cube3::D;
	_shuffleMethods["D\'"] = &Cube3::rD;
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
	_methods["x"] = &Cube3::x;
	_methods["x\'"] = &Cube3::rx;
	_methods["y"] = &Cube3::y;
	_methods["y\'"] = &Cube3::ry;
	_methods["z"] = &Cube3::z;
	_methods["z\'"] = &Cube3::rz;
}

Cube3::~Cube3() {}

std::string	Cube3::F() { rotateFace(-1, -1, 2, getZrotmat(-M_PI_2), Rrot); return "F"; }

std::string	Cube3::rF() { rotateFace(-1, -1, 2, getZrotmat(M_PI_2), Lrot); return "F\'"; }

std::string	Cube3::R() { rotateFace(2, -1, -1, getXrotmat(-M_PI_2), Frot); return "R"; }

std::string	Cube3::rR() { rotateFace(2, -1, -1, getXrotmat(M_PI_2), Brot); return "R\'"; }

std::string	Cube3::U() { rotateFace(-1, 2, -1, getYrotmat(-M_PI_2), Rr); return "U"; }

std::string	Cube3::rU() { rotateFace(-1, 2, -1, getYrotmat(M_PI_2), Lr); return "U\'"; }

std::string	Cube3::B() { rotateFace(-1, -1, 0, getZrotmat(M_PI_2), Lrot); return "B"; }

std::string	Cube3::rB() { rotateFace(-1, -1, 0, getZrotmat(-M_PI_2), Rrot); return "B\'"; }

std::string	Cube3::L() { rotateFace(0, -1, -1, getXrotmat(M_PI_2), Brot); return "L"; }

std::string	Cube3::rL() { rotateFace(0, -1, -1, getXrotmat(-M_PI_2), Frot); return "L\'"; }

std::string	Cube3::D() { rotateFace(-1, 0, -1, getYrotmat(M_PI_2), Lr); return "D"; }

std::string	Cube3::rD() { rotateFace(-1, 0, -1, getYrotmat(-M_PI_2), Rr); return "D\'"; }

std::string	Cube3::shuffle(size_t count) { return _shuffle(*this, _shuffleMethods, count); }

void	Cube3::exec(const std::string &command)
{
	try
	{
		(this->*(_methods.at(command)))();
	}
	catch(const std::exception& e)
	{
		throw UnknownCommand();
	}
}

void	Cube3::execline(const std::string &commandLine)
{
	for (size_t i = 0; i < commandLine.size(); ++i)
	{
		if (commandLine[i] != ' ' && (i == 0 || commandLine[i - 1] == ' '))
		{
			try
			{
				size_t	size = 1;
				if (i < commandLine.size() - 1 && commandLine[i + 1] != ' ')
					++size;
				(this->*(_methods.at(commandLine.substr(i, size))))();
				i += size;
			}
			catch(const std::exception& e)
			{
				throw UnknownCommand();
			}
		}
	}
}
