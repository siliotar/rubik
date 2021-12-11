#include "Commands.hpp"

Commands::Commands() {}

Commands::~Commands() {}

void	Commands::push(std::string command)
{
	if (_commands.size() > 2)
	{
		if (_commands[_commands.size() - 1] == command && \
			_commands[_commands.size() - 2] == command)
		{
			if (command.size() == 1)
				command += "\'";
			else
				command = command.substr(0, 1);
			_commands.erase(_commands.begin() + (_commands.size() - 2), _commands.end());
			_commands.push_back(command);
			return ;
		}
	}
	if (_commands.size() > 0)
	{
		if (command.size() != _commands[_commands.size() - 1].size() && \
			_commands[_commands.size() - 1][0] == command[0])
		{
			_commands.pop_back();
			return ;
		}
	}
	_commands.push_back(command);
}

void	Commands::pushLine(const std::string &commandLine)
{
	
	for (size_t i = 0; i < commandLine.size(); ++i)
	{
		if (commandLine[i] != ' ' && (i == 0 || commandLine[i - 1] == ' '))
		{
			size_t	size = 1;
			if (i < commandLine.size() - 1 && commandLine[i + 1] != ' ')
				++size;
			push(commandLine.substr(i, size));
		}
	}
}

std::string	Commands::str() const
{
	std::stringstream	result;
	std::vector<std::string>::const_iterator	it = _commands.begin();
	for (; it != _commands.end(); ++it)
	{
		if (it != _commands.begin())
			result << " ";
		result << *it;
	}
	return result.str();
}

void	Commands::clear()
{
	_commands.clear();
}

size_t	Commands::size() const
{
	size_t	size = 0;
	for (size_t i = 0; i < _commands.size(); ++i)
		if (_commands[i] != "x" && _commands[i] != "x'" && _commands[i] != "y" && \
			_commands[i] != "y'" && _commands[i] != "z" && _commands[i] != "z'")
			++size;
	return size;
}

size_t	Commands::fillSize() const
{
	return _commands.size();
}

const std::string	&Commands::operator[](size_t idx)
{
	return _commands[idx];
}
