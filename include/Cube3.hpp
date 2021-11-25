#pragma once

class Cube;
class Cube3;

#include "Cube.hpp"
#include "utils.hpp"

class Cube3 : public Cube
{
	private:
		typedef void (Cube3::*Method)();
		Cube3(const Cube3 &copy);
		Cube3	&operator=(const Cube3 &other);
		std::map<std::string, Method>	_methods;
	public:
		Cube3();
		virtual ~Cube3();
		void	F();
		void	rF();
		void	R();
		void	rR();
		void	U();
		void	rU();
		void	B();
		void	rB();
		void	L();
		void	rL();
		void	D();
		void	rD();
		virtual void	shuffle(size_t count);
};