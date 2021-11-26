#include "Cube3.hpp"
#include "Solver.hpp"

int	main()
{
	Cube3	c;
	Solver	s;
	std::string	tmp;

	c.print();
	c.shuffle(20);
	std::cout << std::endl;
	c.print();
	s.solve(&c);
	std::cout << std::endl;
	c.print();
	while (1)
	{
		std::cin >> tmp;
		try
		{
			c.exec(tmp);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		std::cout << std::endl;
		c.print();
	}
}
