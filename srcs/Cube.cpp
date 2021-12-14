#include "Cube.hpp"

Cube::Cube(int size) : _size(size)
{
	_solver = new Solver();
	if (_size < 2)
		throw SizeTooLow();
	if (_size > 10)
		throw SizeTooHigh();
	_shapes = new Shape *[_size * _size * _size];
	for (int z = 0; z < _size; ++z)
		for (int y = 0; y < _size; ++y)
			for (int x = 0; x < _size; ++x)
				_shapes[x + y * _size + z * _size * _size] = new Shape(x, y, z, _size);
}

Cube::Cube(const Cube& copy) : _size(copy._size)
{
	_solver = new Solver();
	_shapes = new Shape *[_size * _size * _size];
	for (int i = 0; i < _size * _size * _size; ++i)
		_shapes[i] = new Shape(*copy._shapes[i]);
	*_solver = *copy._solver;
}

Cube	&Cube::operator=(const Cube& other)
{
	if (this != &other)
	{
		for (int i = 0; i < _size * _size * _size; ++i)
			*_shapes[i] = *other._shapes[i];
		*_solver = *other._solver;
	}
	return *this;
}

Cube::~Cube()
{
	for (int i = 0; i < _size * _size * _size; ++i)
		delete _shapes[i];
	delete[] _shapes;
	delete _solver;
}

void	Cube::rotateFace(int x, int y, int z, mat3 rotmat, Rotation rot)
{
	Shape	*res[_size * _size * _size];
	float	fsize = _size;
	for (int tz = 0; tz < _size; ++tz)
		for (int ty = 0; ty < _size; ++ty)
			for (int tx = 0; tx < _size; ++tx)
				if (tx == x || ty == y || tz == z || (x == -1 && y == -1 && z == -1))
				{
					vec3	newPos = vec3((float)tx - fsize / 2 + 0.5f, (float)ty - fsize / 2 + 0.5f, (float)tz - fsize / 2 + 0.5f) * rotmat;
					res[tx + ty * _size + tz * _size * _size] = \
					_shapes[(int)roundf(newPos.x + fsize / 2 - 0.5f) + (int)roundf(newPos.y + fsize / 2 - 0.5f) * _size + (int)roundf(newPos.z + fsize / 2 - 0.5f) * _size * _size];
				}
	for (int tz = 0; tz < _size; ++tz)
		for (int ty = 0; ty < _size; ++ty)
			for (int tx = 0; tx < _size; ++tx)
				if (tx == x || ty == y || tz == z || (x == -1 && y == -1 && z == -1))
				{
					_shapes[tx + ty * _size + tz * _size * _size] = res[tx + ty * _size + tz * _size * _size];
					switch (rot)
					{
						case Rrot:
							_shapes[tx + ty * _size + tz * _size * _size]->R();
							break;
						case Lrot:
							_shapes[tx + ty * _size + tz * _size * _size]->L();
							break;
						case Frot:
							_shapes[tx + ty * _size + tz * _size * _size]->F();
							break;
						case Brot:
							_shapes[tx + ty * _size + tz * _size * _size]->B();
							break;
						case Rr:
							_shapes[tx + ty * _size + tz * _size * _size]->Rr();
							break;
						case Lr:
							_shapes[tx + ty * _size + tz * _size * _size]->Lr();
							break;
						default:
							break;
					}
				}
}

void	Cube::print()
{
	for (int z = 0; z < _size; ++z)
	{
		for (int i = 0; i < _size; ++i)
			std::cout << "   ";
		for (int x = 0; x < _size; ++x)
			std::cout << _shapes[x + _size * (_size - 1) + z * _size * _size]->_up << " ";
		std::cout << std::endl;
	}

	for (int y = _size - 1; y >= 0; --y)
	{
		int	z = 0;
		int	x = 0;
		for (; z < _size; ++z)
			std::cout << _shapes[x + y * _size + z * _size * _size]->_left << " ";
		--z;
		for (; x < _size; ++x)
			std::cout << _shapes[x + y * _size + z * _size * _size]->_front << " ";
		--x;
		for (; z >= 0; --z)
			std::cout << _shapes[x + y * _size + z * _size * _size]->_right << " ";
		++z;
		for (; x >= 0; --x)
			std::cout << _shapes[x + y * _size + z * _size * _size]->_back << " ";
		std::cout << std::endl;
	}
	
	for (int z = _size - 1; z >= 0; --z)
	{
		for (int i = 0; i < _size; ++i)
			std::cout << "   ";
		for (int x = 0; x < _size; ++x)
			std::cout << _shapes[x + z * _size * _size]->_down << " ";
		std::cout << std::endl;
	}
}

Cube::SizeTooHigh::SizeTooHigh() {}

const char* Cube::SizeTooHigh::what() const throw () { return "Size too high"; }

Cube::SizeTooHigh::~SizeTooHigh() throw () {}

Cube::SizeTooLow::SizeTooLow() {}

const char* Cube::SizeTooLow::what() const throw () { return "Size too low"; }

Cube::SizeTooLow::~SizeTooLow() throw () {}

Cube::UnknownCommand::UnknownCommand() {}
const char* Cube::UnknownCommand::what() const throw () { return "Unknown command"; }
Cube::UnknownCommand::~UnknownCommand() throw () {}

std::string	Cube::shuffle(size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		int	axis = std::rand() % 3;
		int	pos = std::rand() % _size;
		switch (axis)
		{
		case 0:
			rotateFace(pos, -1, -1, getXrotmat(-M_PI_2), Frot);
			break;
		case 1:
			rotateFace(-1, pos, -1, getYrotmat(-M_PI_2), Rr);
			break;
		case 2:
			rotateFace(-1, -1, pos, getZrotmat(-M_PI_2), Rrot);
			break;
		default:
			break;
		}
	}
	return "";
}

void	Cube::exec(const std::string &command) { (void)command; throw UnknownCommand(); }

void	Cube::execline(const std::string &command) { (void)command; throw UnknownCommand(); }

Shape	**Cube::getShapes() const { return _shapes; }

std::string	Cube::x() { rotateFace(-1, -1, -1, getXrotmat(M_PI_2), Brot); return "x"; }

std::string	Cube::y() { rotateFace(-1, -1, -1, getYrotmat(M_PI_2), Lr); return "y"; }

std::string	Cube::z() { rotateFace(-1, -1, -1, getZrotmat(M_PI_2), Lrot); return "z"; }

std::string	Cube::rx() { rotateFace(-1, -1, -1, getXrotmat(-M_PI_2), Frot); return "x'"; }

std::string	Cube::ry() { rotateFace(-1, -1, -1, getYrotmat(-M_PI_2), Rr); return "y'"; }

std::string	Cube::rz() { rotateFace(-1, -1, -1, getZrotmat(-M_PI_2), Rrot); return "z'"; }

std::string	Cube::resetTransform()
{
	std::stringstream	ss;
	size_t	u = _size / 2  + (_size - 1) * _size + _size / 2 * _size * _size;
	size_t	l = _size / 2 * _size + _size / 2 * _size * _size;
	size_t	f = _size / 2 + _size / 2 * _size + (_size - 1) * _size * _size;
	size_t	r = (_size - 1) + _size / 2 * _size + _size / 2 * _size * _size;
	size_t	b = _size / 2 + _size / 2 * _size;
	size_t	d = _size / 2 + _size / 2 * _size * _size;
	if (_shapes[f]->_front == White && _shapes[u]->_up == Green)
		return "";
	if (_shapes[b]->_back == Green)
	{
		ss << x() << " ";
		ss << x();
	}
	else if (_shapes[d]->_down == Green)
		ss << rx();
	else if (_shapes[l]->_left == Green)
		ss << y();
	else if (_shapes[r]->_right == Green)
		ss << ry();
	else if (_shapes[u]->_up == Green)
		ss << x();
	if (_shapes[f]->_front == White)
		return ss.str();
	if (ss.str().size() > 0)
		ss << " ";
	if (_shapes[l]->_left == White)
		ss << rz();
	else if (_shapes[r]->_right == White)
		ss << z();
	else if (_shapes[d]->_down == White)
	{
		ss << z() << " ";
		ss << z();
	}
	return ss.str();
}

bool	Cube::assembled() const
{
	Color	l = _shapes[_size / 2 * _size + _size / 2 * _size * _size]->_left;
	Color	r = _shapes[(_size - 1) + _size / 2 * _size + _size / 2 * _size * _size]->_right;
	Color	d = _shapes[_size / 2 + _size / 2 * _size * _size]->_down;
	Color	u = _shapes[_size / 2 + (_size - 1) * _size + _size / 2 * _size * _size]->_up;
	Color	b = _shapes[_size / 2 + _size / 2 * _size]->_back;
	Color	f = _shapes[_size / 2 + _size / 2 * _size + (_size - 1) * _size * _size]->_front;
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			for (int k = 0; k < _size; ++k)
			{
				Shape	*shape = _shapes[i + j * _size + k * _size * _size];
				if (i == 0 && shape->_left != l)
					return false;
				if (i == _size - 1 && shape->_right != r)
					return false;
				if (j == 0 && shape->_down != d)
					return false;
				if (j == _size - 1 && shape->_up != u)
					return false;
				if (k == 0 && shape->_back != b)
					return false;
				if (k == _size - 1 && shape->_front != f)
					return false;
			}
		}
	}
	return true;
}

Commands	&Cube::solve(bool print, bool beginner)
{
	return _solver->solve(this, print, beginner);
}
