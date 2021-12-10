#pragma once

class Cube;
class Cube3;

#include "Cube.hpp"
#include "utils.hpp"

class Cube3 : public Cube
{
	private:
		typedef std::string (Cube3::*Method)();
		Cube3(const Cube3 &copy);
		Cube3	&operator=(const Cube3 &other);
		std::map<std::string, Method>	_methods;
	public:
		Cube3();
		virtual ~Cube3();
		std::string	F();
		std::string	rF();
		std::string	R();
		std::string	rR();
		std::string	U();
		std::string	rU();
		std::string	B();
		std::string	rB();
		std::string	L();
		std::string	rL();
		std::string	D();
		std::string	rD();
		std::string	shuffle(size_t count);
		void	exec(const std::string &command);
		void	execline(const std::string &commandLine);
};