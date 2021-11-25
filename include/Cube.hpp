#pragma once

class Shape;
class mat3;
class Cube;

#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include "Color.hpp"
#include "Shape.hpp"
#include "mat3.hpp"
#include "utils.hpp"

enum Rotation
{
	Rrot,
	Lrot,
	Frot,
	Brot,
	Rr,
	Lr
};

class Cube
{
	private:
		Cube();
		Cube(const Cube& copy);
		Cube	&operator=(const Cube& other);
	protected:
		int		_size;
		Shape	**_shapes;
		template <typename Child>
		void	_shuffle(Child &c, std::map<std::string, void (Child::*)()> methods, size_t count)
		{
			typedef typename std::map<std::string, void (Child::*)()>::iterator	iterator;
			srand(time(0));
			for (size_t i = 0; i < count; ++i)
			{
				int	move = std::rand() % methods.size();
				iterator	it = methods.begin();
				for (int j = 0; j < move; ++j)
					++it;
				(c.*(it->second))();
			}
		}
	public:
		Cube(int size);
		virtual ~Cube();
		void	print();
		void	rotateFace(int x, int y, int z, mat3 rotmat, Rotation rot);
		class	SizeTooHigh : public std::exception
		{
			public:
				SizeTooHigh();
				virtual const char* what() const throw ();
				virtual ~SizeTooHigh() throw ();
		};
		class	SizeTooLow : public std::exception
		{
			public:
				SizeTooLow();
				virtual const char* what() const throw ();
				virtual ~SizeTooLow() throw ();
		};
		virtual void	shuffle(size_t count);
};