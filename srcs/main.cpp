#include "Cube3.hpp"

int	main()
{
	Cube3	c;
	std::string	tmp;

	c.print();
	while (1)
	{
		std::cin >> tmp;
		if (tmp == "F")
			c.F();
		else if (tmp == "R")
			c.R();
		else if (tmp == "U")
			c.U();
		else if (tmp == "B")
			c.B();
		else if (tmp == "L")
			c.L();
		else if (tmp == "D")
			c.D();
		else if (tmp == "F\'")
			c.rF();
		else if (tmp == "R\'")
			c.rR();
		else if (tmp == "U\'")
			c.rU();
		else if (tmp == "B\'")
			c.rB();
		else if (tmp == "L\'")
			c.rL();
		else if (tmp == "D\'")
			c.rD();
		std::cout << std::endl;
		c.print();
	}
}