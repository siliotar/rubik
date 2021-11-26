#pragma once

class Cube;
class Cube3;

#include <sstream>
#include "Cube.hpp"
#include "Cube3.hpp"

class Solver
{
	private:
		std::stringstream	_commands;
		Solver(const Solver& copy);
		Solver	&operator=(const Solver& other);

		void	_solve3(Cube3 *cube);
		void	_spinForNonWhite(Cube3 *cube, int pos);
	public:
		Solver();
		virtual ~Solver();
		void	solve(Cube *cube);
};
