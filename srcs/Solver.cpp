#include "Solver.hpp"

Solver::Solver() :
_s1(0),
_s2(0),
_s3(0),
_s4(0),
_s5(0),
_s6(0),
_s7(0),
_count(0)
{}

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
		_commands.push(cube->rU());
	else
		while (cube->getShapes()[pos]->_up == White)
			_commands.push(cube->U());
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
			_commands.push((cube->*m1)());
			--moves;
		}
		else
		{
			_commands.push((cube->*m2)());
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
	_commands.push((cube->*(m1[pos]))());
	_swap(cube, i, pos, &Cube3::rU, &Cube3::U);
	_commands.push((cube->*(m2[pos]))());
	_swap(cube, i, pos, &Cube3::U, &Cube3::rU);
	_commands.push((cube->*(m1[pos]))());
}

//	Ideas: insert immediately in the right place

void	Solver::_solve3s1(Cube3 *cube)
{
	int	possiblePos[] = {
		3, 5, 21, 23,
		7, 17, 25, 15,
		1, 9, 11, 19
	};
	for (int i = 0; i < 12; ++i)
	{
		Shape	*tmp = cube->getShapes()[possiblePos[i]];
		if (tmp->hasColor(White) && tmp->_up != White)
		{
			if (i < 4)
			{
				if (tmp->_front == White || tmp->_back == White )
				{
					if (tmp->_left != Black)
					{
						_spinForNonWhite(cube, 15);
						_commands.push((tmp->_front == White ? cube->rL() : cube->L()));
					}
					else
					{
						_spinForNonWhite(cube, 17);
						_commands.push((tmp->_front == White ? cube->R() : cube->rR()));
					}

				}
				else if (tmp->_left == White || tmp->_right == White)
				{
					if (tmp->_back != Black)
					{
						_spinForNonWhite(cube, 7);
						_commands.push((tmp->_left == White ? cube->rB() : cube->B()));
					}
					else
					{
						_spinForNonWhite(cube, 25);
						_commands.push((tmp->_left == White ? cube->F() : cube->rF()));
					}
				}
			}
			else if (i < 8)
			{
				if (tmp->_left == White)
					_commands.push(cube->L());
				else if (tmp->_back == White)
					_commands.push(cube->B());
				else if (tmp->_right == White)
					_commands.push(cube->R());
				else
					_commands.push(cube->F());
			}
			else
			{
				if (tmp->_left == White)
				{
					_spinForNonWhite(cube, 15);
					_commands.push(cube->L());
				}
				else if (tmp->_back == White)
				{
					_spinForNonWhite(cube, 7);
					_commands.push(cube->B());
				}
				else if (tmp->_right == White)
				{
					_spinForNonWhite(cube, 17);
					_commands.push(cube->R());
				}
				else if (tmp->_front == White)
				{
					_spinForNonWhite(cube, 25);
					_commands.push(cube->F());
				}
				else
				{
					if (tmp->_left != Black)
					{
						_spinForNonWhite(cube, 15);
						_commands.push(cube->L());
						_commands.push(cube->L());
					}
					else if (tmp->_right != Black)
					{
						_spinForNonWhite(cube, 17);
						_commands.push(cube->R());
						_commands.push(cube->R());
					}
					else if (tmp->_back != Black)
					{
						_spinForNonWhite(cube, 7);
						_commands.push(cube->B());
						_commands.push(cube->B());
					}
					else
					{
						_spinForNonWhite(cube, 25);
						_commands.push(cube->F());
						_commands.push(cube->F());
					}
				}
			}
			i = -1;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		int right = 0;
		Shape	**shapes = cube->getShapes();
		for (int j = 4; j < 8; ++j)
			if (shapes[possiblePos[j]]->horisontalEqual(*shapes[possiblePos[j] - 3]))
				++right;
		if (right > 1)
			break ;
		_commands.push(cube->U());
	}
	for (int i = 4; i < 8; ++i)
		if (!cube->getShapes()[possiblePos[i]]->horisontalEqual(*cube->getShapes()[possiblePos[i] - 3]))
			_swapUpForCross(cube, i - 4, cube->getShapes()[possiblePos[i] - 3]->getFirstNot(Black));
}

int		_s1getPos(Color mainColor, Color tempColor, int mainPos)
{
	int	dPos = mainColor - tempColor;
	mainPos += dPos;
	if (mainPos < 0)
		mainPos += 4;
	return mainPos % 4;
}

void	Solver::_solve3s1v2(Cube3 *cube)
{
	int	possiblePos[] = {
		3, 5, 23, 21,
		1, 11, 19, 9,
		7, 17, 25, 15
	};
	Method	m[] = {
		&Cube3::rB, &Cube3::L, &Cube3::rR, &Cube3::B,
		&Cube3::rF, &Cube3::R, &Cube3::rL, &Cube3::F
	};
	Color	mainCol = Black;
	int		mainPos = 0;
	while (mainCol == Black)
	{
		for (int i = 8; i < 12 && mainCol == Black; ++i)
			if (cube->getShapes()[possiblePos[i]]->_up == White)
			{
				mainCol = cube->getShapes()[possiblePos[i]]->getFirstNot(White);
				mainPos = i % 4;
			}
		for (int i = 0; i < 4 && mainCol == Black; ++i)
		{
			Shape	*shape = cube->getShapes()[possiblePos[i]];
			if (shape->hasColor(White))
			{
				Color	sides[] = {
					shape->_left, shape->_back, shape->_right, shape->_front
				};
				int	mpos = i * 2;
				mainCol = shape->getFirstNot(White);
				mainPos = i;
				if (sides[i] != White)
				{
					++mpos;
					mainPos = (i + 3) % 4;
				}
				_commands.push((cube->*m[mpos])());
			}
		}
		for (int i = 4; i < 8 && mainCol == Black; ++i)
		{
			Shape	*shape = cube->getShapes()[possiblePos[i]];
			if (shape->hasColor(White))
			{
				mainCol = shape->getFirstNot(White);
				mainPos = i - 4;
				_commands.push((cube->*m[(i - 4) * 2])());
			}
		}
		for (int i = 8; i < 12; ++i)
		{
			Shape	*shape = cube->getShapes()[possiblePos[i]];
			if (shape->hasColor(White))
			{
				_commands.push((cube->*m[(i - 8) * 2])());
				break ;
			}
		}
	}
	for (int i = 0; i < 12; ++i)
	{
		Shape	*shape = cube->getShapes()[possiblePos[i]];
		if (shape->hasColor(White))
		{
			if (i < 4)
			{
				Color	sides[] = {
					shape->_left, shape->_back, shape->_right, shape->_front
				};
				int	mpos = i * 2;
				int	tPos = i;
				if (sides[i] != White)
				{
					++mpos;
					tPos = (i + 3) % 4;
				}
				int rPos = _s1getPos(mainCol, shape->getFirstNot(White), mainPos);
				int rot = (tPos - rPos + 4) % 4;
				for (int j = 0; j < rot; ++j)
				{
					mainPos = (mainPos + 1) % 4;
					_commands.push(cube->U());
				}
				_commands.push((cube->*m[mpos])());
			}
			else if (i < 8)
			{
				while (cube->getShapes()[possiblePos[i + 4]]->_up == White)
				{
					mainPos = (mainPos + 1) % 4;
					_commands.push(cube->U());
				}
				_commands.push((cube->*m[(i - 4) * 2])());
			}
			else if (i % 4 == _s1getPos(mainCol, shape->getFirstNot(White), mainPos) && shape->_up == White)
				continue ;
			else
				_commands.push((cube->*m[(i - 8) * 2])());
			i = -1;
		}
	}
	while (cube->getShapes()[25]->_front != Green)
		_commands.push(cube->U());
}

void	Solver::_rpifpaf(Cube3 *cube, Method m1, Method m2, bool up, bool last)
{
	_commands.push((cube->*m1)());
	if (up)
		_commands.push(cube->U());
	else
		_commands.push(cube->D());
	_commands.push((cube->*m2)());
	if (!last)
		return ;
	if (up)
		_commands.push(cube->rU());
	else
		_commands.push(cube->rD());
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
	Method	lm[] = {
		&Cube3::L, &Cube3::B, &Cube3::R, &Cube3::F
	};
	Method	rlm[] = {
		&Cube3::rL, &Cube3::rB, &Cube3::rR, &Cube3::rF
	};
	ShapeMethod	sm[] = {
		&Shape::L, &Shape::F, &Shape::R, &Shape::B
	};
	for (int i = 0; i < 8; ++i)
	{
		Shape	*shape = cube->getShapes()[possiblePos[i]];
		if (shape->hasColor(White))
		{
			bool	left;
			int		pos;
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
				left = (pos == 0 && cube->getShapes()[0]->_left == White) || \
						(pos == 1 && cube->getShapes()[2]->_back == White) || \
						(pos == 2 && cube->getShapes()[20]->_right == White) || \
						(pos == 3 && cube->getShapes()[18]->_front == White);
				while (cube->getShapes()[rightPos[pos]] != shape || cube->getShapes()[rightPos[pos]]->_up != White)
					if (left)
						_lpifpaf(cube, rlm[pos], lm[pos]);
					else
						_rpifpaf(cube, m[pos], rm[pos]);
			}
			else if (possiblePos[i] == rightPos[pos] && shape->_up == White)
				continue ;
			else
			{

				Shape	tmp(*shape);
				(tmp.*sm[pos])();
				if (tmp._down != White)
					_rpifpaf(cube, m[pos], rm[pos]);
				else
					_lpifpaf(cube, rlm[pos], lm[pos]);
			}
			i = -1;
		}
	}
}

void	Solver::_lpifpaf(Cube3 *cube, Method m1, Method m2, bool up, bool last)
{
	_commands.push((cube->*m1)());
	if (up)
		_commands.push(cube->rU());
	else
		_commands.push(cube->rD());
	_commands.push((cube->*m2)());
	if (!last)
		return ;
	if (up)
		_commands.push(cube->U());
	else
		_commands.push(cube->D());
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
		&Cube3::L, &Cube3::B, &Cube3::R, &Cube3::F
	};
	Method	rm2[] = {
		&Cube3::rL, &Cube3::rB, &Cube3::rR, &Cube3::rF
	};
	int q = 0;
	for (int i = 0; i < 8; ++i, ++q)
	{
		Shape	*shape = cube->getShapes()[possiblePos[i]];
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
					_swap(cube, 0, i, &Cube3::rD, &Cube3::D);
				else if (shape->_down != Red && shape->hasColor(Red))
					_swap(cube, 1, i, &Cube3::rD, &Cube3::D);
				else if (shape->_down != Green && shape->hasColor(Green))
					_swap(cube, 2, i, &Cube3::rD, &Cube3::D);
				else
					_swap(cube, 3, i, &Cube3::rD, &Cube3::D);
				if (!(shape->_down == Blue && shape->getFirstNot(shape->_down) == Orange) && \
				(shape->_down > shape->getFirstNot(shape->_down) || (shape->_down == Orange && shape->getFirstNot(shape->_down) == Blue)))
				{
					//	Left
					_commands.push(cube->rD());
					_lpifpaf(cube, rm2[pos], m2[pos]);
					_rpifpaf(cube, m1[pos], rm1[pos], false, false);
				}
				else
				{
					//	Right
					_commands.push(cube->D());
					_rpifpaf(cube, m1[pos], rm1[pos]);
					_lpifpaf(cube, rm2[pos], m2[pos], false, false);
				}
			}
			else if (possiblePos[i] == rightPos[pos] && shape->horisontalEqual(*cube->getShapes()[rightPos[pos] + 3]))
				continue ;
			else
			{
				_rpifpaf(cube, m1[pos], rm1[pos]);
				_lpifpaf(cube, rm2[pos], m2[pos], false, false);
			}
			i = -1;
		}
	}
}

void	Solver::_solve3s4(Cube3 *cube)
{
	int	possiblePos[] = {
		1, 9, 19, 11
	};
	Method	f[] = {
		&Cube3::R, &Cube3::B, &Cube3::L, &Cube3::F
	};
	Method	rf[] = {
		&Cube3::rR, &Cube3::rB, &Cube3::rL, &Cube3::rF
	};
	Method	m[] = {
		&Cube3::F, &Cube3::R, &Cube3::B, &Cube3::L
	};
	Method	rm[] = {
		&Cube3::rF, &Cube3::rR, &Cube3::rB, &Cube3::rL
	};
	while (cube->getShapes()[possiblePos[0]]->_down != Yellow || \
		cube->getShapes()[possiblePos[1]]->_down != Yellow || \
		cube->getShapes()[possiblePos[2]]->_down != Yellow || \
		cube->getShapes()[possiblePos[3]]->_down != Yellow)
	{
		int	t = 0;
		if ((cube->getShapes()[possiblePos[0]]->_down == Yellow && \
			cube->getShapes()[possiblePos[2]]->_down == Yellow) || \
			(cube->getShapes()[possiblePos[1]]->_down == Yellow && \
			cube->getShapes()[possiblePos[3]]->_down == Yellow && (t = 1) == 1))
		{
			if (t)
			{
				_commands.push(cube->F());
				_rpifpaf(cube, &Cube3::L, &Cube3::rL);
				_commands.push(cube->rF());
			}
			else
			{
				_commands.push(cube->L());
				_rpifpaf(cube, &Cube3::B, &Cube3::rB);
				_commands.push(cube->rL());
			}
			continue ;
		}
		int i;
		for (i = 0; i < 4; ++i)
		{
			if (cube->getShapes()[possiblePos[i]]->_down == Yellow \
				&& cube->getShapes()[possiblePos[(i + 1) % 4]]->_down == Yellow)
			{
				_commands.push((cube->*f[i])());
				_rpifpaf(cube, m[i], rm[i]);
				_rpifpaf(cube, m[i], rm[i]);
				_commands.push((cube->*rf[i])());
				return ;
			}
		}
		_commands.push((cube->*f[0])());
		_rpifpaf(cube, m[0], rm[0]);
		_commands.push((cube->*rf[0])());
	}
}

int		Solver::_s5findClose(Cube3 *cube)
{
	int	possiblePos[] = {
		1, 9, 19, 11
	};
	int	i;
	for (i = 0; i < 4; ++i)
		if (cube->getShapes()[possiblePos[i]]->getFirstNot(Yellow) == \
			cube->getShapes()[possiblePos[i] + 3]->getFirstNot(Yellow) && \
			cube->getShapes()[possiblePos[(i + 1) % 4]]->getFirstNot(Yellow) == \
			cube->getShapes()[possiblePos[(i + 1) % 4] + 3]->getFirstNot(Yellow))
			return i;
	return i;
}

int		Solver::_s5findOpos(Cube3 *cube)
{
	int	possiblePos[] = {
		1, 9, 19, 11
	};
	int	i;
	for (i = 0; i < 2; ++i)
		if (cube->getShapes()[possiblePos[i]]->getFirstNot(Yellow) == \
			cube->getShapes()[possiblePos[i] + 3]->getFirstNot(Yellow) && \
			cube->getShapes()[possiblePos[i + 2]]->getFirstNot(Yellow) == \
			cube->getShapes()[possiblePos[i + 2] + 3]->getFirstNot(Yellow))
			return i;
	return i;
}

void	Solver::_solve3s5(Cube3 *cube)
{
	int	possiblePos[] = {
		1, 9, 19, 11
	};
	int	i;
	for (i = 0; i < 3; ++i)
	{
		if (_s5findClose(cube) == 4)
			_commands.push(cube->D());
		else
			break ;
	}
	for (i = 0; i < 4; ++i)
		if (cube->getShapes()[possiblePos[i]]->getFirstNot(Yellow) != \
			cube->getShapes()[possiblePos[i] + 3]->getFirstNot(Yellow))
			break ;
	if (i == 4)
		return ;
	Method	m[] = {
		&Cube3::L, &Cube3::F, &Cube3::R, &Cube3::B
	};
	Method	rm[] = {
		&Cube3::rL, &Cube3::rF, &Cube3::rR, &Cube3::rB
	};
	if ((i = _s5findClose(cube)) == 4)
	{
		int	t;
		for (int i = 0; i < 3; ++i)
		{
			if ((t = _s5findOpos(cube)) == 2)
				_commands.push(cube->D());
			else
				break ;
		}
		_commands.push((cube->*m[t + 1])());
		_commands.push(cube->D());
		_commands.push((cube->*rm[t + 1])());
		_commands.push(cube->D());
		_commands.push((cube->*m[t + 1])());
		_commands.push(cube->D());
		_commands.push(cube->D());
		_commands.push((cube->*rm[t + 1])());
		for (i = 0; i < 3; ++i)
		{
			if (_s5findClose(cube) == 4)
				_commands.push(cube->D());
			else
				break ;
		}
	}
	i = _s5findClose(cube);
	_commands.push((cube->*m[i])());
	_commands.push(cube->D());
	_commands.push((cube->*rm[i])());
	_commands.push(cube->D());
	_commands.push((cube->*m[i])());
	_commands.push(cube->D());
	_commands.push(cube->D());
	_commands.push((cube->*rm[i])());
	_commands.push(cube->D());
}

bool	Solver::_s6correctAngle(Cube3 *cube, int pos)
{
	Color	f = cube->getShapes()[pos + 3]->getFirstNot(Black);
	Color	s = cube->getShapes()[pos + 3]->getFirstNot(f);
	if (!cube->getShapes()[pos]->hasColor(f) || \
		!cube->getShapes()[pos]->hasColor(s))
		return false;
	return true;
}

bool	Solver::_s6correctAngles(Cube3 *cube)
{
	int	possiblePos[] = {
		0, 18, 20, 2
	};
	for (int i = 0; i < 4; ++i)
		if (!_s6correctAngle(cube, possiblePos[i]))
			return false;
	return true;
}

void	Solver::_solve3s6(Cube3 *cube)
{
	int	possiblePos[] = {
		0, 18, 20, 2
	};
	Method	r[] = {
		&Cube3::R, &Cube3::B, &Cube3::L, &Cube3::F
	};
	Method	rr[] = {
		&Cube3::rR, &Cube3::rB, &Cube3::rL, &Cube3::rF
	};
	Method	l[] = {
		&Cube3::L, &Cube3::F, &Cube3::R, &Cube3::B
	};
	Method	rl[] = {
		&Cube3::rL, &Cube3::rF, &Cube3::rR, &Cube3::rB
	};
	while (!_s6correctAngles(cube))
	{
		int	i;
		for (i = 0; i < 4; ++i)
			if (_s6correctAngle(cube, possiblePos[i]))
				break ;
		i %= 4;
		_commands.push((cube->*r[i])());
		_commands.push(cube->rD());
		_commands.push((cube->*rl[i])());
		_commands.push(cube->D());
		_commands.push((cube->*rr[i])());
		_commands.push(cube->rD());
		_commands.push((cube->*l[i])());
		_commands.push(cube->D());
	}
}

bool	Solver::_s7correctAngle(Cube3 *cube, int pos)
{
	if (cube->getShapes()[pos]->horisontalEqual(*cube->getShapes()[pos + 3]) && \
		cube->getShapes()[pos]->_down == Yellow)
		return true;
	return false;
}

bool	Solver::_s7correctAngles(Cube3 *cube)
{
	int	possiblePos[] = {
		0, 18, 20, 2
	};
	for (int i = 0; i < 4; ++i)
		if (!_s7correctAngle(cube, possiblePos[i]))
			return false;
	return true;
}

void	Solver::_solve3s7(Cube3 *cube)
{
	char	dir = 0;
	if (_s7correctAngles(cube))
		return ;
	for (int i = 0; i < 4; ++i)
	{
		while (cube->getShapes()[20]->_front != cube->getShapes()[19]->_front || \
				cube->getShapes()[20]->_right != cube->getShapes()[11]->_right || \
				cube->getShapes()[20]->_down != Yellow)
		{
			if (dir == 0)
				dir = cube->getShapes()[20]->_right == Yellow ? 1 : 2;
			if (dir == 1)
				_rpifpaf(cube, &Cube3::R, &Cube3::rR, true);
			else
				_lpifpaf(cube, &Cube3::rF, &Cube3::F, true);
		}
		_commands.push(cube->D());
	}
}

void	Solver::_solve3beginner(Cube3 *cube, bool print)
{
	size_t prev = 0;
	//	1-st stage (White cross)
	_solve3s1v2(cube);
	++_count;

	if (print)
	{
		std::cout << "--------------- Stage 1 ---------------" << std::endl;
		_s1 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s1 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}

	//	2-nd stage (First layer)
	_solve3s2(cube);
	
	if (print)
	{
		std::cout << "--------------- Stage 2 ---------------" << std::endl;
		_s2 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s2 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}

	//	3-rd stage (Middle layer)
	_solve3s3(cube);
	
	if (print)
	{
		std::cout << "--------------- Stage 3 ---------------" << std::endl;
		_s3 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s3 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}

	//	4-th stage (Yellow cross)
	_solve3s4(cube);
	
	if (print)
	{
		std::cout << "--------------- Stage 4 ---------------" << std::endl;
		_s4 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s4 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}

	//	5-th stage (Correct yellow cross)
	_solve3s5(cube);
	
	if (print)
	{
		std::cout << "--------------- Stage 5 ---------------" << std::endl;
		_s5 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s5 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}

	//	6-th stage (Correct angles in 3-rd layer)
	_solve3s6(cube);
	
	if (print)
	{
		std::cout << "--------------- Stage 6 ---------------" << std::endl;
		_s6 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s6 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}

	//	7-th stage (Final)
	_solve3s7(cube);
	
	if (print)
	{
		std::cout << "--------------- Stage 7 ---------------" << std::endl;
		_s7 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s7 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}
}

void	Solver::_useFormula(Cube3 *cube, const std::string &formula, int idx)
{
	Method	f[] = {
		&Cube3::B, &Cube3::R, &Cube3::F, &Cube3::L
	};
	Method	rf[] = {
		&Cube3::rB, &Cube3::rR, &Cube3::rF, &Cube3::rL
	};
	Method	b[] = {
		&Cube3::F, &Cube3::L, &Cube3::B, &Cube3::R
	};
	Method	rb[] = {
		&Cube3::rF, &Cube3::rL, &Cube3::rB, &Cube3::rR
	};
	Method	r[] = {
		&Cube3::L, &Cube3::B, &Cube3::R, &Cube3::F
	};
	Method	rr[] = {
		&Cube3::rL, &Cube3::rB, &Cube3::rR, &Cube3::rF
	};
	Method	l[] = {
		&Cube3::R, &Cube3::F, &Cube3::L, &Cube3::B
	};
	Method	rl[] = {
		&Cube3::rR, &Cube3::rF, &Cube3::rL, &Cube3::rB
	};
	for (size_t i = 0; i < formula.size(); ++i)
	{
		if (formula[i] != ' ' && (i == 0 || formula[i - 1] == ' '))
		{
			size_t	size = 1;
			if (i < formula.size() - 1 && formula[i + 1] != ' ')
				++size;
			std::string	cmd = formula.substr(i, size);
			if (cmd == "F")
				_commands.push((cube->*f[idx])());
			else if (cmd == "F'")
				_commands.push((cube->*rf[idx])());
			else if (cmd == "B")
				_commands.push((cube->*b[idx])());
			else if (cmd == "B'")
				_commands.push((cube->*rb[idx])());
			else if (cmd == "R")
				_commands.push((cube->*r[idx])());
			else if (cmd == "R'")
				_commands.push((cube->*rr[idx])());
			else if (cmd == "L")
				_commands.push((cube->*l[idx])());
			else if (cmd == "L'")
				_commands.push((cube->*rl[idx])());
			else if (cmd == "U")
				_commands.push(cube->U());
			else if (cmd == "U'")
				_commands.push(cube->rU());
			else if (cmd == "D")
				_commands.push(cube->D());
			else if (cmd == "D'")
				_commands.push(cube->rD());
			i += size;
		}
	}
}

void	Solver::_solve3advanceds2(Cube3 *cube)
{
	static const std::string	f2lformulas[] = {
		"U R U R' U' F' U' F",
		"U' F' U F U R U' R'",
		"U R U' R'",
		"F R' F' R",
		"R U R'",
		"F' U' F",
		"U' R U U R' U U R U' R'",
		"U F' U' F U U F' U F",
		"U' R U R' U U R U' R'",
		"U F' U U F U U F' U F",
		"U' R U' R' U F' U' F",
		"U' R U R' U R U R'",
		"U F' U F U' F' U' F",
		"U F' U U F U' R U R'",
		"U' R U U R' U F' U' F",
		"U' R U' R' U R U R'",
		"F' U F U U R U R'",
		"R U' R' U U F' U' F",
		"R U U R' U' R U R'",
		"F' U U F U F' U' F",
		"U R U U R' U R U' R'",
		"R U' R' U U R U R'",
		"U' F' U U F U' F' U F",
		"U U F' U' F U' F' U F",
		"R U R' U U R U R' U' R U R'",
		"F U R U' R' F' R U' R'",
		"F' U' F U F' U' F",
		"R U' R' U R U' R'",
		"R U R' U' F R' F' R",
		"R U R' U' R U R'",
		"R U' R' F' U U F",
		"U' R U R' U F' U' F",
		"R U R' U' R U R' U' R U R'",
		"U F' U' F U' R U R'",
		"U' R U' R' U U R U' R'",
		"U R U R' U U R U R'",
		"U R U R' U U R U R'",
		"R U F R U R' U' F' R'",
		"R F U R U' R' F' U' R'",
		"R U U R U R' U R U U R R",
		"R U R' U' R U U R' U' R U R'",
		"R U' R' U F' U U F U U F' U F"
	};
	int		upperEdges[] = {
		7, 17, 25, 15
	};
	int		middleEdges[] = {
		3, 5, 23, 21
	};
	int		upperCorners[] = {
		6, 8, 26, 24
	};
	int		downCorners[] = {
		0, 2, 23, 18
	};

	_commands.push(cube->z());
	_commands.push(cube->z());
	for (int i = 0; i < 4; ++i)
	{
		Shape	**shapes = cube->getShapes();
		Color	front = shapes[22]->_front;
		Color	right = shapes[14]->_right;
		if (shapes[20]->_down == White && shapes[20]->_right == right && \
		shapes[20]->_front == front && shapes[23]->horisontalEqual(*shapes[20]))
		{
			_commands.push(cube->y());
			continue ;
		}
		bool	edge = false, corner = false;
		if (shapes[20]->equals(White, front, right))
			corner = true;
		for (int j = 0; j < 4 && !corner; ++j)
			if (shapes[upperCorners[j]]->equals(White, front, right))
				corner = true;
		if (!corner)
			for (int j = 0; j < 4; ++j)
				if (shapes[downCorners[j]]->equals(White, front, right))
					_useFormula(cube, "R U R'", j);
		shapes = cube->getShapes();
		if (shapes[23]->equals(front, right))
			edge = true;
		for (int j = 0; j < 4 && !edge; ++j)
			if (shapes[upperEdges[j]]->equals(front, right))
				edge = true;
		if (!edge)
			for (int j = 0; j < 4; ++j)
				if (shapes[middleEdges[j]]->equals(front, right))
				{
					if (shapes[upperCorners[j]]->equals(White, front, right))
						_useFormula(cube, "R U' R'", j);
					else
						_useFormula(cube, "R U R'", j);
				}
		int	edgePos = 23, cornerPos = 26;
		if (cube->getShapes()[20]->equals(White, front, right))
			cornerPos = 20;
		else
			while (!cube->getShapes()[26]->equals(White, front, right))
				_commands.push(cube->U());
		if (!cube->getShapes()[23]->equals(front, right))
			for (int j = 0; j < 4 && edgePos == 23; ++j)
				if (cube->getShapes()[upperEdges[j]]->equals(front, right))
					edgePos = upperEdges[j];
		if (cornerPos == 20)
		{
			bool	r = edgePos != 23 && cube->getShapes()[edgePos]->_up == right;
			if (edgePos != 23)
			{
				if (cube->getShapes()[edgePos]->_up == right)
					while (!cube->getShapes()[25]->equals(front, right))
						_commands.push(cube->U());
				else
					while (!cube->getShapes()[17]->equals(front, right))
						_commands.push(cube->U());
			}
			if (cube->getShapes()[20]->_front == front)
			{
				if (edgePos == 23)
					_useFormula(cube, f2lformulas[41]);
				else
				{
					if (r)
						_useFormula(cube, f2lformulas[0]);
					else
						_useFormula(cube, f2lformulas[1]);
				}
			}
			else if (cube->getShapes()[20]->_front == White)
			{
				if (edgePos == 23)
				{
					if (cube->getShapes()[23]->_front == right)
						_useFormula(cube, f2lformulas[38]);
					else
						_useFormula(cube, f2lformulas[40]);
				}
				else
				{
					if (r)
						_useFormula(cube, f2lformulas[26]);
					else
						_useFormula(cube, f2lformulas[27]);
				}
			}
			else if (cube->getShapes()[20]->_right == White)
			{
				if (edgePos == 23)
				{
					if (cube->getShapes()[23]->_front == right)
						_useFormula(cube, f2lformulas[37]);
					else
						_useFormula(cube, f2lformulas[39]);
				}
				else
				{
					if (r)
						_useFormula(cube, f2lformulas[28]);
					else
						_useFormula(cube, f2lformulas[29]);
				}
			}
		}
		else
		{
			if (cube->getShapes()[26]->_front == White)
			{
				if (edgePos == 17)
				{
					if (cube->getShapes()[17]->_right == right)
						_useFormula(cube, f2lformulas[2]);
					else
						_useFormula(cube, f2lformulas[14]);
				}
				else if (edgePos == 25)
				{
					if (cube->getShapes()[25]->_front == front)
						_useFormula(cube, f2lformulas[12]);
					else
						_useFormula(cube, f2lformulas[16]);
				}
				else if (edgePos == 15)
				{
					if (cube->getShapes()[15]->_up == right)
						_useFormula(cube, f2lformulas[5]);
					else
						_useFormula(cube, f2lformulas[6]);
				}
				else if (edgePos == 7)
				{
					if (cube->getShapes()[7]->_up == front)
						_useFormula(cube, f2lformulas[8]);
					else
						_useFormula(cube, f2lformulas[10]);
				}
				else
				{
					if (cube->getShapes()[23]->_front == front)
						_useFormula(cube, f2lformulas[34]);
					else
						_useFormula(cube, f2lformulas[31]);
				}
			}
			else if (cube->getShapes()[26]->_right == White)
			{
				if (edgePos == 17)
				{
					if (cube->getShapes()[17]->_right == right)
						_useFormula(cube, f2lformulas[15]);
					else
						_useFormula(cube, f2lformulas[17]);
				}
				else if (edgePos == 25)
				{
					if (cube->getShapes()[25]->_front == front)
						_useFormula(cube, f2lformulas[3]);
					else
						_useFormula(cube, f2lformulas[13]);
				}
				else if (edgePos == 15)
				{
					if (cube->getShapes()[15]->_up == right)
						_useFormula(cube, f2lformulas[7]);
					else
						_useFormula(cube, f2lformulas[11]);
				}
				else if (edgePos == 7)
				{
					if (cube->getShapes()[7]->_up == front)
						_useFormula(cube, f2lformulas[4]);
					else
						_useFormula(cube, f2lformulas[9]);
				}
				else
				{
					if (cube->getShapes()[23]->_front == front)
						_useFormula(cube, f2lformulas[35]);
					else
						_useFormula(cube, f2lformulas[33]);
				}
			}
			else
			{
				if (edgePos == 17)
				{
					if (cube->getShapes()[17]->_right == right)
						_useFormula(cube, f2lformulas[18]);
					else
						_useFormula(cube, f2lformulas[25]);
				}
				else if (edgePos == 25)
				{
					if (cube->getShapes()[25]->_front == front)
						_useFormula(cube, f2lformulas[19]);
					else
						_useFormula(cube, f2lformulas[24]);
				}
				else if (edgePos == 15)
				{
					if (cube->getShapes()[15]->_up == right)
						_useFormula(cube, f2lformulas[22]);
					else
						_useFormula(cube, f2lformulas[21]);
				}
				else if (edgePos == 7)
				{
					if (cube->getShapes()[7]->_up == front)
						_useFormula(cube, f2lformulas[20]);
					else
						_useFormula(cube, f2lformulas[23]);
				}
				else
				{
					if (cube->getShapes()[23]->_front == front)
						_useFormula(cube, f2lformulas[32]);
					else
						_useFormula(cube, f2lformulas[30]);
				}
			}
		}
		_commands.push(cube->y());
	}
	_commands.push(cube->rz());
	_commands.push(cube->rz());
}

void	Solver::_solve3advanceds3(Cube3 *cube)
{
	Shape	**shapes = cube->getShapes();
	if (shapes[6]->_up == Yellow && shapes[7]->_up == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_up == Yellow && shapes[26]->_up == Yellow)
		return ;
	else if (shapes[6]->_back == Yellow && shapes[7]->_up == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_up == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R U R' U R U U R'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_up == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "R U U R' U' R U' R'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_up == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R U U R R U' R R U' R R U U R");
	else if (shapes[6]->_up == Yellow && shapes[7]->_up == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_up == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R R D R' U U R D' R' U U R'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_up == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R U U R' U' R U R' U' R U' R'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_up == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_up == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "L F R' F' L' F R F'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_up == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "F' L F R' F' L' F R");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "R U R' U' L R' F R F' L'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_up == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "L F R' F' L' R U R U' R'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "L' R B R B R' B' L R' R' L F R F' L'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "F R U R' U' F'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "R U R' U' R' F R F'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_back == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "R U U R R F R F' U U R' F R F'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_back == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "L' B' L U U R' U U R U U L' B L");
	else if (shapes[6]->_back == Yellow && shapes[7]->_back == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "L' R R B R' B L U U L' B R' L");
	else if (shapes[6]->_left == Yellow && shapes[7]->_back == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "L' R B' L U U L' B' R B' R R L");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "L' R B R B R' B' L R R F R F'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "L F R' F R F F L L B' R B' R' B B L");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "R U R' U R' F R F' U U R' F R F'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_back == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "F U R U' R' U R U' R' F'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_back == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R' F R U R U' R R F' R R U' R' U R U R'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_back == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "L' B' L U' R' U R U' R' U R L' B L");
	else if (shapes[6]->_back == Yellow && shapes[7]->_back == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "F' L' U' L U' F U F' U F");
	else if (shapes[6]->_left == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "L F L' R U R' U' L F' L'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R' F' R L' U' L U R' F R");
	else if (shapes[6]->_back == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R B' R' U' R B R' B' U B");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "L' B L U L' B' L B U' B'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_back == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "R U R R U' R' F R U R U' F'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_back == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "B' U' B' R B R' U B");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "R' F R U R' U' F' U R");
	else if (shapes[6]->_back == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "L F' L' U' L U F U' L'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "L F F R' F' R F' L'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_up == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R' F F L F L' F R");
	else if (shapes[6]->_up == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "L U U L L B L B' L U U L'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_up == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "F R' F' R U R U' R'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_up == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "R U R' U R U' R' U' R' F R F'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "L' U' L U' L' U L U L F' L' F");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "R U R' U' R' F R R U R' U' F'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_up == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "L U L' U L' B L B' L U U L'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_up == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "L F R' F R F F L'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "R' F' L F' L' F F R");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "B L U L' U' B' U B L U L' U' B'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_up == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "L R' F R F R' F R F F R' F L' R");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_up == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "B' U' R' U R B");
	else if (shapes[6]->_left == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_up == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "B U L U' L' B'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_up == Yellow && shapes[25]->_up == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "L' U' B U L U' L' B' L");
	else if (shapes[6]->_back == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_up == Yellow && shapes[26]->_up == Yellow)
		_useFormula(cube, "R U B' U' R' U R B R'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_up == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R U' R' U U R U B U' B' U' R'");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_up == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "L' U L U U L' U' B' U B U L");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_up == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "B L' B L L U' L' U' L U L' B B");
	else if (shapes[6]->_up == Yellow && shapes[7]->_back == Yellow && shapes[8]->_up == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_up == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "B U B' U' B U' B' R' U' R B U B'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_up == Yellow && shapes[17]->_right == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "F R U R' U' R U R' U' F'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_up == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "F' L' U' L U L' U' L U F");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_right == Yellow)
		_useFormula(cube, "L F R' F R F' R' F R F F L'");
	else if (shapes[6]->_back == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "L F U F' U' F U' F' U F U F' L'");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_back == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_left == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "L F' L L F U U F U U F' L");
	else if (shapes[6]->_left == Yellow && shapes[7]->_up == Yellow && shapes[8]->_right == Yellow && \
		shapes[15]->_left == Yellow && shapes[17]->_up == Yellow && \
		shapes[24]->_front == Yellow && shapes[25]->_front == Yellow && shapes[26]->_front == Yellow)
		_useFormula(cube, "R U U R' U' R U' R' F R U R' U' F'");
	else
	{
		_commands.push(cube->y());
		_solve3advanceds3(cube);
	}
}

void	Solver::_solve3advanceds4(Cube3 *cube)
{
	if (cube->assembled())
		return ;
	Shape	**shapes = cube->getShapes();
	for (int i = 0; i < 4; ++i)
	{
		if (shapes[6]->_left == shapes[24]->_left && shapes[6]->_left == shapes[17]->_right && \
			shapes[6]->_back == shapes[7]->_back && shapes[6]->_back == shapes[26]->_right && \
			shapes[8]->_back == shapes[15]->_left && shapes[8]->_back == shapes[26]->_front && \
			shapes[24]->_front == shapes[25]->_front && shapes[24]->_front == shapes[8]->_right)
			_useFormula(cube, "R U R' U' R' F R R U' R' U' R U R' F'");
		else if (shapes[7]->_back == shapes[24]->_left && shapes[7]->_back == shapes[26]->_right && \
			shapes[8]->_back == shapes[15]->_left && shapes[8]->_back == shapes[26]->_front && \
			shapes[6]->_left == shapes[8]->_right && shapes[6]->_left == shapes[17]->_right && \
			shapes[6]->_back == shapes[24]->_front && shapes[6]->_back == shapes[25]->_front)
			_useFormula(cube, "F R U' R' U' R U R' F' R U R' U' R' F R F'");
		else if (shapes[8]->_right == shapes[25]->_front && shapes[8]->_right == shapes[26]->_right && \
			shapes[15]->_left == shapes[24]->_front && shapes[15]->_left == shapes[26]->_front && \
			shapes[6]->_left == shapes[17]->_right && shapes[6]->_left == shapes[24]->_left && \
			shapes[6]->_back == shapes[7]->_back && shapes[6]->_back == shapes[8]->_back)
			_useFormula(cube, "R U' R U R U R U' R' U' R R");
		else if (shapes[8]->_right == shapes[15]->_left && shapes[8]->_right == shapes[26]->_right && \
			shapes[17]->_right == shapes[24]->_front && shapes[17]->_right == shapes[26]->_front && \
			shapes[6]->_left == shapes[24]->_left && shapes[6]->_left == shapes[25]->_front && \
			shapes[6]->_back == shapes[7]->_back && shapes[6]->_back == shapes[8]->_back)
			_useFormula(cube, "R R U R U R' U' R' U' R' U R'");
		else if (shapes[6]->_left == shapes[17]->_right && shapes[6]->_left == shapes[24]->_left && \
			shapes[6]->_back == shapes[8]->_back && shapes[6]->_back == shapes[25]->_front && \
			shapes[8]->_right == shapes[15]->_left && shapes[8]->_right == shapes[26]->_right && \
			shapes[7]->_back == shapes[24]->_front && shapes[7]->_back == shapes[26]->_front)
			_useFormula(cube, "R R L L D' R R L L U U R R L L D' R R L L");
		else if (shapes[6]->_left == shapes[7]->_back && shapes[6]->_left == shapes[24]->_left && \
			shapes[6]->_back == shapes[8]->_back && shapes[6]->_back == shapes[15]->_left && \
			shapes[8]->_right == shapes[25]->_front && shapes[8]->_right == shapes[26]->_right && \
			shapes[17]->_right == shapes[24]->_front && shapes[17]->_right == shapes[26]->_front)
			_useFormula(cube, "U U R R L L D R R L L U L R' F F L L R R B B L R'");
		else if (shapes[15]->_left == shapes[24]->_left && shapes[15]->_left == shapes[26]->_right && \
			shapes[6]->_left == shapes[7]->_back && shapes[6]->_left == shapes[26]->_front && \
			shapes[6]->_back == shapes[8]->_back && shapes[6]->_back == shapes[17]->_right &&
			shapes[8]->_right == shapes[24]->_front && shapes[8]->_right == shapes[25]->_front)
			_useFormula(cube, "R' F R' B B R F' R' B B R R");
		else if (shapes[6]->_back == shapes[24]->_front && shapes[6]->_back == shapes[25]->_front && \
			shapes[8]->_back == shapes[15]->_left && shapes[8]->_back == shapes[24]->_left && \
			shapes[7]->_back == shapes[8]->_right && shapes[7]->_back == shapes[26]->_right && \
			shapes[6]->_left == shapes[17]->_right && shapes[6]->_left == shapes[26]->_front)
			_useFormula(cube, "R R B B R F R' B B R F' R");
		else if (shapes[6]->_left == shapes[15]->_left && shapes[6]->_left == shapes[24]->_left && \
			shapes[6]->_back == shapes[7]->_back && shapes[6]->_back == shapes[26]->_right && \
			shapes[8]->_back == shapes[25]->_front && shapes[8]->_back == shapes[26]->_front && \
			shapes[8]->_right == shapes[17]->_right && shapes[8]->_right == shapes[24]->_front)
			_useFormula(cube, "R U U R' U' R U U L' U R' U' L");
		else if (shapes[7]->_back == shapes[8]->_back && shapes[7]->_back == shapes[26]->_front && \
			shapes[8]->_right == shapes[24]->_front && shapes[8]->_right == shapes[25]->_front && \
			shapes[6]->_left == shapes[15]->_left && shapes[6]->_left == shapes[24]->_left && \
			shapes[6]->_back == shapes[17]->_right && shapes[6]->_back == shapes[26]->_right)
			_useFormula(cube, "U' R' U L' U U R U' R' U U R L");
		else if (shapes[6]->_back == shapes[25]->_front && shapes[6]->_back == shapes[26]->_right && \
			shapes[8]->_back == shapes[17]->_right && shapes[8]->_back == shapes[26]->_front && \
			shapes[7]->_back == shapes[8]->_right && shapes[7]->_back == shapes[24]->_front && \
			shapes[6]->_left == shapes[15]->_left && shapes[6]->_left == shapes[24]->_left)
			_useFormula(cube, "U' R' U R U' R R F' U' F U R F R' F' R R");
		else if (shapes[15]->_left == shapes[24]->_left && shapes[15]->_left == shapes[26]->_right && \
			shapes[8]->_back == shapes[17]->_right && shapes[8]->_back == shapes[26]->_front && \
			shapes[6]->_left == shapes[7]->_back && shapes[6]->_left == shapes[8]->_right && \
			shapes[6]->_back == shapes[24]->_front && shapes[6]->_back == shapes[25]->_front)
			_useFormula(cube, "R' U U R U U L U' R' U L' U L U' R U L'");
		else if (shapes[8]->_back == shapes[24]->_left && shapes[8]->_back == shapes[25]->_front && \
			shapes[6]->_left == shapes[7]->_back && shapes[6]->_left == shapes[8]->_right && \
			shapes[6]->_back == shapes[17]->_right && shapes[6]->_back == shapes[26]->_right && \
			shapes[15]->_left == shapes[24]->_front && shapes[15]->_left == shapes[26]->_front)
			_useFormula(cube, "L U U L' U U L F' L' U' L U L F L L");
		else if (shapes[6]->_back == shapes[25]->_front && shapes[6]->_back == shapes[26]->_right && \
			shapes[17]->_right == shapes[24]->_front && shapes[17]->_right == shapes[26]->_front && \
			shapes[8]->_back == shapes[15]->_left && shapes[8]->_back == shapes[24]->_left && \
			shapes[6]->_left == shapes[7]->_back && shapes[6]->_left == shapes[8]->_right)
			_useFormula(cube, "R' U U R' D' R U' R' D R U R U' R' U' R");
		else if (shapes[7]->_back == shapes[24]->_left && shapes[7]->_back == shapes[26]->_right && \
			shapes[8]->_back == shapes[17]->_right && shapes[8]->_back == shapes[26]->_front && \
			shapes[6]->_left == shapes[8]->_right && shapes[6]->_left == shapes[25]->_front && \
			shapes[6]->_back == shapes[15]->_left && shapes[6]->_back == shapes[24]->_front)
			_useFormula(cube, "R' U' R' D' R U' R' D R U R' D' R U R' D R R");
		else if (shapes[6]->_left == shapes[8]->_right && shapes[6]->_left == shapes[17]->_right && \
			shapes[6]->_back == shapes[7]->_back && shapes[6]->_back == shapes[24]->_front && \
			shapes[15]->_left == shapes[24]->_left && shapes[15]->_left == shapes[26]->_right && \
			shapes[8]->_back == shapes[25]->_front && shapes[8]->_back == shapes[26]->_front)
			_useFormula(cube, "R U R' U' L U U L' U' L U U R' U L' U' R U R U' R'");
		else if (shapes[17]->_right == shapes[24]->_left && shapes[17]->_right == shapes[26]->_right && \
			shapes[7]->_back == shapes[8]->_back && shapes[7]->_back == shapes[26]->_front && \
			shapes[6]->_left == shapes[8]->_right && shapes[6]->_left == shapes[15]->_left && \
			shapes[6]->_back == shapes[24]->_front && shapes[6]->_back == shapes[25]->_front)
			_useFormula(cube, "R' U R U' R' F' U' F R U R' F R' F' R U' R");
		else if (shapes[6]->_back == shapes[24]->_front && shapes[6]->_back == shapes[25]->_front && \
			shapes[8]->_back == shapes[17]->_right && shapes[8]->_back == shapes[24]->_left && \
			shapes[8]->_right == shapes[15]->_left && shapes[8]->_right == shapes[26]->_right && \
			shapes[6]->_left == shapes[7]->_back && shapes[6]->_left == shapes[26]->_front)
			_useFormula(cube, "R' R' F F R U U R U' U' R' F R U R' U' R' F R R");
		else if (shapes[8]->_right == shapes[24]->_front && shapes[8]->_right == shapes[25]->_front && \
			shapes[7]->_back == shapes[24]->_left && shapes[7]->_back == shapes[26]->_right && \
			shapes[6]->_left == shapes[17]->_right && shapes[6]->_left == shapes[26]->_front && \
			shapes[6]->_back == shapes[8]->_back && shapes[6]->_back == shapes[15]->_left)
			_useFormula(cube, "R' R' F' R U R U' R' F' R U' U' R' U' U' R' F F R R");
		else if (shapes[6]->_left == shapes[17]->_right && shapes[6]->_left == shapes[24]->_left && \
			shapes[6]->_back == shapes[15]->_left && shapes[6]->_back == shapes[26]->_right && \
			shapes[8]->_back == shapes[25]->_front && shapes[8]->_back == shapes[26]->_front && \
			shapes[7]->_back == shapes[8]->_right && shapes[7]->_back == shapes[24]->_front)
			_useFormula(cube, "L L F F L' U U L' U U L F' L' U' L U L F' L L");
		else if (shapes[8]->_right == shapes[15]->_left && shapes[8]->_right == shapes[24]->_front && \
			shapes[7]->_back == shapes[24]->_left && shapes[7]->_back == shapes[26]->_right && \
			shapes[6]->_left == shapes[25]->_front && shapes[6]->_left == shapes[26]->_front && \
			shapes[6]->_back == shapes[8]->_back && shapes[6]->_back == shapes[17]->_right)
			_useFormula(cube, "U' D R' U' R U D' R R U R' U R U' R U' R R");
		else
		{
			_commands.push(cube->U());
			continue ;
		}
		break ;
	}
	while (!cube->getShapes()[6]->horisontalEqual(*cube->getShapes()[3]))
		_commands.push(cube->U());
}

void	Solver::_solve3advanced(Cube3 *cube, bool print)
{
	size_t prev = 0;
	//	1-st stage (White cross)
	_solve3s1v2(cube);
	++_count;

	if (print)
	{
		std::cout << "--------------- Stage 1 ---------------" << std::endl;
		_s1 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s1 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}

	//	2-nd stage (First two layers - F2L)
	_solve3advanceds2(cube);
	
	if (print)
	{
		std::cout << "--------------- Stage 2 ---------------" << std::endl;
		_s2 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s2 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}

	//	3-rd stage (Orientation of the Last Layer - OLL)
	_commands.push(cube->x());
	_commands.push(cube->x());
	_solve3advanceds3(cube);
	_commands.push(cube->resetTransform());
	
	if (print)
	{
		std::cout << "--------------- Stage 3 ---------------" << std::endl;
		_s3 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s3 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}

	//	4-th stage (Permutation of the Last Layer - PLL)
	_commands.push(cube->x());
	_commands.push(cube->x());
	_solve3advanceds4(cube);
	_commands.push(cube->resetTransform());
	
	if (print)
	{
		std::cout << "--------------- Stage 4 ---------------" << std::endl;
		_s4 += _commands.size() - prev;
		std::cout << "avg = " << (float)_s4 / _count << std::endl;
		std::cout << _commands.size() - prev << std::endl;
		prev = _commands.size();
		cube->print();
	}
}

Commands	&Solver::solve(Cube *cube, bool print)
{
	_commands.clear();
	if (dynamic_cast<Cube3*>(cube))
		_solve3advanced(dynamic_cast<Cube3*>(cube), print);
	return _commands;
}
