#pragma once

#include <vector>
#include <string>
#include <sstream>

class Commands
{
	private:
		std::vector<std::string>	_commands;
	public:
		Commands();
		Commands	&operator=(const Commands& other);
		~Commands();
		void	push(std::string command, bool optimize = true);
		void	pushLine(const std::string &commandLine, bool optimize = true);
		std::string	str() const;
		void	clear();
		size_t	size() const;
		size_t	fullSize() const;
		std::string	popFront();
		const std::string	&operator[](size_t idx);
};
