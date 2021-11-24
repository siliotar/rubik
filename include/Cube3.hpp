#pragma once

class Cube;

#include "Cube.hpp"
#include "utils.hpp"

class Cube3 : public Cube
{
	private:
		Cube3(const Cube3& copy);
		Cube3	&operator=(const Cube3& other);
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
};