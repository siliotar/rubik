#pragma once

#include <ostream>

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define LIGHTGRAY "\033[37m"
#define RESET "\033[0m"
#define YELLOW "\033[0;93m"

enum Color
{
	Black,
	White,
	Orange,
	Green,
	Red,
	Blue,
	Yellow
};

inline std::ostream& operator<<(std::ostream &os, Color &color)
{
	switch (color)
	{
		case Black:
			os << BLACK << "██" << RESET;
			break ;
		case White:
			os << "██";
			break ;
		case Orange:
			os << ORANGE << "██" << RESET;
			break ;
		case Green:
			os << GREEN << "██" << RESET;
			break ;
		case Red:
			os << RED << "██" << RESET;
			break ;
		case Blue:
			os << BLUE << "██" << RESET;
			break ;
		case Yellow:
			os << YELLOW << "██" << RESET;
			break ;
		default:
			os << "[Unknown Color]";
			break ;
	}
	return os;
}
