#pragma once

class Cube;
class Cube3;
class Commands;
class Solver;
class Shape;

#include <sstream>
#include "Commands.hpp"
#include "Shape.hpp"

class Solver
{
	private:
		typedef std::string (Cube3::*Method)();
		typedef void (Shape::*ShapeMethod)();

		Commands	_commands;
		size_t		_s1;
		size_t		_s2;
		size_t		_s3;
		size_t		_s4;
		size_t		_s5;
		size_t		_s6;
		size_t		_s7;
		size_t		_count;

		Solver(const Solver& copy);

		void	_solve3beginner(Cube3 *cube, bool print);
		void	_solve3s1(Cube3 *cube);
		void	_solve3s1v2(Cube3 *cube);
		void	_solve3s2(Cube3 *cube);
		void	_solve3s3(Cube3 *cube);
		void	_solve3s4(Cube3 *cube);
		void	_solve3s5(Cube3 *cube);
		void	_solve3s6(Cube3 *cube);
		void	_solve3s7(Cube3 *cube);
		void	_spinForNonWhite(Cube3 *cube, int pos);
		void	_swapUpForCross(Cube3 *cube, int pos, Color color);
		void	_swap(Cube3 *cube, int first, int second, Method m1, Method m2);
		void	_rpifpaf(Cube3 *cube, Method m1, Method m2, bool up = false, bool last = true);
		void	_lpifpaf(Cube3 *cube, Method m1, Method m2, bool up = false, bool last = true);
		int		_s5findClose(Cube3 *cube);
		int		_s5findOpos(Cube3 *cube);
		bool	_s6correctAngle(Cube3 *cube, int pos);
		bool	_s6correctAngles(Cube3 *cube);
		bool	_s7correctAngle(Cube3 *cube, int pos);
		bool	_s7correctAngles(Cube3 *cube);
		void	_solve3advanced(Cube3 *cube, bool print);
		void	_solve3advanceds2(Cube3 *cube);
		void	_solve3advanceds3(Cube3 *cube);
		void	_solve3advanceds4(Cube3 *cube);
		void	_useFormula(Cube3 *cube, const std::string &formula, int idx = 2);
	public:
		Solver	&operator=(const Solver& other);
		Solver();
		virtual ~Solver();
		Commands	&solve(Cube *cube, bool print = true, bool beginner = false);
};

#include "Cube.hpp"
#include "Cube3.hpp"
