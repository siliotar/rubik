#include "Cube.hpp"

Cube::Cube(int size) : _size(size)
{
	if (size < 2)
		throw SizeTooLow();
	if (size > 100)
		throw SizeTooHigh();
	_shapes = new Shape *[_size * _size * _size];
	for (int z = 0; z < _size; ++z)
		for (int y = 0; y < _size; ++y)
			for (int x = 0; x < _size; ++x)
				_shapes[x + y * _size + z * _size * _size] = new Shape(x, y, z, _size);
}

Cube::~Cube()
{
	for (int i = 0; i < _size * _size * _size; ++i)
		delete _shapes[i];
	delete[] _shapes;
}

void	Cube::rotateFace(int x, int y, int z, mat3 rotmat, Rotation rot)
{
	Shape	*res[_size * _size * _size];
	float	fsize = _size;
	for (int tz = 0; tz < _size; ++tz)
		for (int ty = 0; ty < _size; ++ty)
			for (int tx = 0; tx < _size; ++tx)
				if (tx == x || ty == y || tz == z)
				{
					vec3	newPos = vec3((float)tx - fsize / 2 + 0.5f, (float)ty - fsize / 2 + 0.5f, (float)tz - fsize / 2 + 0.5f) * rotmat;
					res[tx + ty * _size + tz * _size * _size] = \
					_shapes[(int)roundf(newPos.x + fsize / 2 - 0.5f) + (int)roundf(newPos.y + fsize / 2 - 0.5f) * _size + (int)roundf(newPos.z + fsize / 2 - 0.5f) * _size * _size];
				}
	for (int tz = 0; tz < _size; ++tz)
		for (int ty = 0; ty < _size; ++ty)
			for (int tx = 0; tx < _size; ++tx)
				if (tx == x || ty == y || tz == z)
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
const char* Cube::UnknownCommand::what() const throw () { return "Unknowsn command"; }
Cube::UnknownCommand::~UnknownCommand() throw () {}

void	Cube::shuffle(size_t count)
{
	srand(time(0));
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
}

void	Cube::exec(const std::string &command) { (void)command; throw UnknownCommand(); }

void	Cube::execline(const std::string &command) { (void)command; throw UnknownCommand(); }

Shape	**Cube::getShapes() const { return _shapes; }
