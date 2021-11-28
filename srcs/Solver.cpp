#include "Solver.hpp"

Solver::Solver() {}

Solver::~Solver() {}

void	Solver::_spinForNonWhite(Cube3 *cube, int pos)
{
	int	possiblePos[] = {
		7, 17, 25, 15
	};
	int i;
	for (i = 0; i < 4; ++i)
		if (possiblePos[i] == pos)
			break ;
	++i;
	i %= 4;
	if (cube->getShapes()[possiblePos[i]]->_up != White)
		_commands << cube->rU() << " ";
	else
		while (cube->getShapes()[pos]->_up == White)
			_commands << cube->U() << " ";
}

void	Solver::_swap(Cube3 *cube, int first, int second, Method m1, Method m2)
{
	int moves = first - second;

	if (moves == 3)
		moves = -1;
	else if (moves == -3)
		moves = 1;
	while (moves != 0)
	{
		if (moves > 0)
		{
			_commands << (cube->*m1)() << " ";
			--moves;
		}
		else
		{
			_commands << (cube->*m2)() << " ";
			++moves;
		}
	}
}

void	Solver::_swapUpForCross(Cube3 *cube, int pos, Color color)
{
	int	possiblePos[] = {
		7, 17, 25, 15
	};
	Method	m1[] = {
		&Cube3::B, &Cube3::R, &Cube3::F, &Cube3::L
	};
	Method	m2[] = {
		&Cube3::rB, &Cube3::rR, &Cube3::rF, &Cube3::rL
	};
	int	i;
	for (i = 0; i < 4; ++i)
		if (cube->getShapes()[possiblePos[i]]->hasColor(color))
			break ;
	_commands << (cube->*(m1[pos]))() << " ";
	_swap(cube, i, pos, &Cube3::rU, &Cube3::U);
	_commands << (cube->*(m2[pos]))() << " ";
	_swap(cube, i, pos, &Cube3::U, &Cube3::rU);
	_commands << (cube->*(m1[pos]))() << " ";
}

//	Ideas: insert immediately in the right place

void	Solver::_solve3s1(Cube3 *cube)
{
	int	possiblePos[] = {
		7, 17, 25, 15,
		3, 5, 21, 23,
		1, 9, 11, 19
	};
	for (int i = 0; i < 12; ++i)
	{
		Shape	*tmp = cube->getShapes()[possiblePos[i]];
		if (tmp->hasColor(White) && tmp->_up != White)
		{
			if (i < 4)
			{
				if (tmp->_left == White)
					_commands << cube->L() << " ";
				else if (tmp->_back == White)
					_commands << cube->B() << " ";
				else if (tmp->_right == White)
					_commands << cube->R() << " ";
				else
					_commands << cube->F() << " ";
			}
			else if (i < 8)
			{
				if (tmp->_front == White || tmp->_back == White )
				{
					if (tmp->_left != Black)
					{
						_spinForNonWhite(cube, 15);
						_commands << (tmp->_front == White ? cube->rL() : cube->L()) << " ";
					}
					else
					{
						_spinForNonWhite(cube, 17);
						_commands << (tmp->_front == White ? cube->R() : cube->rR()) << " ";
					}

				}
				else if (tmp->_left == White || tmp->_right == White)
				{
					if (tmp->_back != Black)
					{
						_spinForNonWhite(cube, 7);
						_commands << (tmp->_left == White ? cube->rB() : cube->B()) << " ";
					}
					else
					{
						_spinForNonWhite(cube, 25);
						_commands << (tmp->_left == White ? cube->F() : cube->rF()) << " ";
					}
				}
			}
			else
			{
				if (tmp->_left == White)
				{
					_spinForNonWhite(cube, 15);
					_commands << cube->L() << " ";
				}
				else if (tmp->_back == White)
				{
					_spinForNonWhite(cube, 7);
					_commands << cube->B() << " ";
				}
				else if (tmp->_right == White)
				{
					_spinForNonWhite(cube, 17);
					_commands << cube->R() << " ";
				}
				else if (tmp->_front == White)
				{
					_spinForNonWhite(cube, 25);
					_commands << cube->F() << " ";
				}
				else
				{
					if (tmp->_left != Black)
					{
						_spinForNonWhite(cube, 15);
						_commands << cube->L() << " ";
						_commands << cube->L() << " ";
					}
					else if (tmp->_right != Black)
					{
						_spinForNonWhite(cube, 17);
						_commands << cube->R() << " ";
						_commands << cube->R() << " ";
					}
					else if (tmp->_back != Black)
					{
						_spinForNonWhite(cube, 7);
						_commands << cube->B() << " ";
						_commands << cube->B() << " ";
					}
					else
					{
						_spinForNonWhite(cube, 25);
						_commands << cube->F() << " ";
						_commands << cube->F() << " ";
					}
				}
			}
			i = -1;
		}
	}
	Color	colorOrder[] = {
		Blue, Red, Green, Orange
	};
	int	i;
	for (i = 0; i < 4; ++i)
		if (cube->getShapes()[possiblePos[i]]->hasColor(Blue))
			break ;
	for (int j = 1; j < 4; ++j)
		if (!cube->getShapes()[possiblePos[(i + j) % 4]]->hasColor(colorOrder[j]))
			_swapUpForCross(cube, (i + j) % 4, colorOrder[j]);
	_swap(cube, 0, i, &Cube3::U, &Cube3::rU);
}

void	Solver::_s2pifpaf(Cube3 *cube, Method m1, Method m2)
{
	_commands << (cube->*m1)() << " ";
	_commands << cube->D() << " ";
	_commands << (cube->*m2)() << " ";
	_commands << cube->rD() << " ";
}

void	Solver::_solve3s2(Cube3 *cube)
{
	int	possiblePos[] = {
		0, 2, 20, 18,
		6, 8, 26, 24
	};
	int	rightPos[] = {
		6, 8, 26, 24
	};
	Method	m[] = {
		&Cube3::B, &Cube3::R, &Cube3::F, &Cube3::L
	};
	Method	rm[] = {
		&Cube3::rB, &Cube3::rR, &Cube3::rF, &Cube3::rL
	};
	for (int i = 0; i < 8; ++i)
	{
		Shape	*shape = cube->getShapes()[possiblePos[i]];
		if (shape->hasColor(White))
		{
			int pos;
			if (shape->equals(White, Orange, Blue))
				pos = 0;
			else if (shape->equals(White, Blue, Red))
				pos = 1;
			else if (shape->equals(White, Red, Green))
				pos = 2;
			else
				pos = 3;
			if (i < 4)
			{
				_swap(cube, i, pos, &Cube3::D, &Cube3::rD);
				while (cube->getShapes()[rightPos[pos]] != shape || cube->getShapes()[rightPos[pos]]->_up != White)
					_s2pifpaf(cube, m[pos], rm[pos]);
			}
			else if (possiblePos[i] == rightPos[pos] && shape->_up == White)
				continue ;
			else
				_s2pifpaf(cube, m[pos], rm[pos]);
			i = -1;
		}
	}
}

void	Solver::_s3pifpaf(Cube3 *cube, Method m1, Method m2)
{
	_commands << (cube->*m1)() << " ";
	_commands << cube->rD() << " ";
	_commands << (cube->*m2)() << " ";
	_commands << cube->D() << " ";
}

void	Solver::_solve3s3(Cube3 *cube)
{
	int	possiblePos[] = {
		1, 11, 19, 9,
		3, 5, 23, 21
	};
	int	rightPos[] = {
		3, 5, 23, 21
	};
	Method	m1[] = {
		&Cube3::B, &Cube3::R, &Cube3::F, &Cube3::L
	};
	Method	rm1[] = {
		&Cube3::rB, &Cube3::rR, &Cube3::rF, &Cube3::rL
	};
	Method	m2[] = {
		&Cube3::L, &Cube3::R, &Cube3::F, &Cube3::L
	};
	Method	rm2[] = {
		&Cube3::rL, &Cube3::rR, &Cube3::rF, &Cube3::rL
	};
	Color	colorOrder[] = {
		Blue, Red, Green, Orange
	};
	for (int i = 0; i < 8; ++i)
	{
		Shape	*shape = cube->getShapes()[possiblePos[i]];
		Shape	*upper = cube->getShapes()[possiblePos[i] + 3];
		if (!shape->hasColor(Yellow))
		{
			int pos;
			if (shape->equals(Orange, Blue))
				pos = 0;
			else if (shape->equals(Blue, Red))
				pos = 1;
			else if (shape->equals(Red, Green))
				pos = 2;
			else
				pos = 3;
			if (i < 4)
			{
				if (shape->_down != Blue && shape->hasColor(Blue))
					_swap(cube, 0, i, &Cube3::D, &Cube3::rD);
				else if (shape->_down != Red && shape->hasColor(Red))
					_swap(cube, 1, i, &Cube3::D, &Cube3::rD);
				else if (shape->_down != Green && shape->hasColor(Green))
					_swap(cube, 2, i, &Cube3::D, &Cube3::rD);
				else
					_swap(cube, 3, i, &Cube3::D, &Cube3::rD);
				_s2pifpaf(cube, m1[pos], rm1[pos]);
				_s3pifpaf(cube, m2[pos], rm2[pos]);
			}
			else if (possiblePos[i] == rightPos[pos] && shape->horisontalEqual(*upper))
				continue ;
			else
			{
				_s2pifpaf(cube, m1[pos], rm1[pos]);
				_s3pifpaf(cube, m2[pos], rm2[pos]);
			}
			i = -1;
		}
		// if (shape->hasColor(White))
		// {
		// 	int pos;
		// 	if (shape->equals(Orange, Blue))
		// 		pos = 0;
		// 	else if (shape->equals(Blue, Red))
		// 		pos = 1;
		// 	else if (shape->equals(Red, Green))
		// 		pos = 2;
		// 	else
		// 		pos = 3;
		// 	if (i < 4)
		// 	{
		// 		_swap(cube, i, pos, &Cube3::D, &Cube3::rD);
		// 		while (cube->getShapes()[rightPos[pos]] != shape || cube->getShapes()[rightPos[pos]]->_up != White)
		// 			_s2pifpaf(cube, m[pos], rm[pos]);
		// 	}
		// 	else if (possiblePos[i] == rightPos[pos] && shape->_up == White)
		// 		continue ;
		// 	else
		// 		_s2pifpaf(cube, m[pos], rm[pos]);
		// 	i = -1;
		// }
	}
}

void	Solver::_solve3(Cube3 *cube)
{
	//	1-st stage (White cross)
	_solve3s1(cube);

	std::cout << "--------------- Stage 1 ---------------" << std::endl;
	cube->print();

	//	2-nd stage (First layer)
	_solve3s2(cube);
	
	std::cout << "--------------- Stage 2 ---------------" << std::endl;
	cube->print();

	//	3-rd stage (Middle layer)
	// _solve3s3(cube);
	
	// std::cout << "--------------- Stage 3 ---------------" << std::endl;
	// cube->print();

	std::cout << _commands.str() << std::endl;
}

void	Solver::solve(Cube *cube)
{
	if (dynamic_cast<Cube3*>(cube))
		_solve3(dynamic_cast<Cube3*>(cube));
}
