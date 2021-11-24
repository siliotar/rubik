#include "Cube.hpp"

Cube::Cube(int size) : _size(size)
{
	if (size < 1)
		throw SizeTooLow();
	if (size > 100)
		throw SizeTooHigh();
	_shapes = new Shape *[_size * _size * _size];
	size_t	idx = 0;
	float	fsize = _size;
	for (float z = fsize / 2; z > -fsize / 2; --z)
		for (float y = -fsize / 2; y < fsize / 2; ++y)
			for (float x = -fsize / 2; x < fsize / 2; ++x)
				_shapes[idx++] = new Shape(x + 0.5f, y + 0.5f, z + 0.5f, _size);
}

Cube::~Cube() { delete[] _shapes; }

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
					_shapes[(int)(newPos.x + fsize / 2 - 0.5f) + (int)(newPos.y + fsize / 2 - 0.5f) * _size + (int)(newPos.z + fsize / 2 - 0.5f) * _size * _size];
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
			std::cout << "\t";
		for (int x = 0; x < _size; ++x)
			std::cout << _shapes[x + _size * (_size - 1) + z * _size * _size]->_up << "\t";
		std::cout << std::endl;
	}

	for (int y = _size - 1; y >= 0; --y)
	{
		int	z = 0;
		int	x = 0;
		for (; z < _size; ++z)
			std::cout << _shapes[x + y * _size + z * _size * _size]->_left << "\t";
		--z;
		for (; x < _size; ++x)
			std::cout << _shapes[x + y * _size + z * _size * _size]->_front << "\t";
		--x;
		for (; z >= 0; --z)
			std::cout << _shapes[x + y * _size + z * _size * _size]->_right << "\t";
		++z;
		for (; x >= 0; --x)
			std::cout << _shapes[x + y * _size + z * _size * _size]->_back << "\t";
		std::cout << std::endl;
	}
	
	for (int z = _size - 1; z >= 0; --z)
	{
		for (int i = 0; i < _size; ++i)
			std::cout << "\t";
		for (int x = 0; x < _size; ++x)
			std::cout << _shapes[x + z * _size * _size]->_down << "\t";
		std::cout << std::endl;
	}
}

Cube::SizeTooHigh::SizeTooHigh() {}

const char* Cube::SizeTooHigh::what() const throw () { return "Size too high"; }

Cube::SizeTooHigh::~SizeTooHigh() throw () {}

Cube::SizeTooLow::SizeTooLow() {}

const char* Cube::SizeTooLow::what() const throw () { return "Size too low"; }

Cube::SizeTooLow::~SizeTooLow() throw () {}
