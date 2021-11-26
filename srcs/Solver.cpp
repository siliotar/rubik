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

void	Solver::_solve3(Cube3 *cube)
{
	//	1-st stage
	int	possiblePos[] = {
		7, 15, 17, 25,
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
				if (tmp->_front == White)
				{
					if (tmp->_left != Black)
					{
						_spinForNonWhite(cube, 15);
						_commands << cube->rL() << " ";
					}
					else
					{
						_spinForNonWhite(cube, 17);
						_commands << cube->R() << " ";
					}
				}
				else if (tmp->_left == White)
				{
					if (tmp->_back != Black)
					{
						_spinForNonWhite(cube, 7);
						_commands << cube->rB() << " ";
					}
					else
					{
						_spinForNonWhite(cube, 25);
						_commands << cube->F() << " ";
					}
				}
				else if (tmp->_right == White)
				{
					if (tmp->_back != Black)
					{
						_spinForNonWhite(cube, 7);
						_commands << cube->B() << " ";
					}
					else
					{
						_spinForNonWhite(cube, 25);
						_commands << cube->rF() << " ";
					}
				}
				else
				{
					if (tmp->_left != Black)
					{
						_spinForNonWhite(cube, 15);
						_commands << cube->L() << " ";
					}
					else
					{
						_spinForNonWhite(cube, 17);
						_commands << cube->rR() << " ";
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
	// if (cube->getShapes()[15]->_left == Green)
	// 	_commands << cube->rU() << " ";
	// else
	// 	while (cube->getShapes()[25]->_front != Green)
	// 		_commands << cube->U() << " ";
	int	i;
	for (i = 0; i < 3; ++i)
	{
		if (cube->getShapes)
	}
	
	std::cout << _commands.str() << std::endl;
}

void	Solver::solve(Cube *cube)
{
	if (dynamic_cast<Cube3*>(cube))
		_solve3(dynamic_cast<Cube3*>(cube));
}
