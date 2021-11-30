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
	return _commands.size();
}
