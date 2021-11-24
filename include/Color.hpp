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
			os << BLACK << "Black" << RESET;
			break ;
		case White:
			os << "White";
			break ;
		case Orange:
			os << ORANGE << "Orange" << RESET;
			break ;
		case Green:
			os << GREEN << "Green" << RESET;
			break ;
		case Red:
			os << RED << "Red" << RESET;
			break ;
		case Blue:
			os << BLUE << "Blue" << RESET;
			break ;
		case Yellow:
			os << YELLOW << "Yellow" << RESET;
			break ;
		default:
			os << "[Unknown Color]";
			break ;
	}
	return os;
}
