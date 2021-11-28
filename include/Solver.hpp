#pragma once

class Cube;
class Cube3;

#include <sstream>
#include "Cube.hpp"
#include "Cube3.hpp"

class Solver
{
	private:
		typedef std::string (Cube3::*Method)();
		std::stringstream	_commands;
		Solver(const Solver& copy);
		Solver	&operator=(const Solver& other);

		void	_solve3(Cube3 *cube);
		void	_solve3s1(Cube3 *cube);
		void	_solve3s2(Cube3 *cube);
		void	_solve3s3(Cube3 *cube);
		void	_spinForNonWhite(Cube3 *cube, int pos);
		void	_swapUpForCross(Cube3 *cube, int pos, Color color);
		void	_swap(Cube3 *cube, int first, int second, Method m1, Method m2);
		void	_s2pifpaf(Cube3 *cube, Method m1, Method m2);
		void	_s3pifpaf(Cube3 *cube, Method m1, Method m2);
	public:
		Solver();
		virtual ~Solver();
		void	solve(Cube *cube);
};
