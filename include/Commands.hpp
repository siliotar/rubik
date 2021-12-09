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
		~Commands();
		void	push(std::string command);
		void	pushLine(const std::string &commandLine);
		std::string	str() const;
		void	clear();
		size_t	size() const;
};
