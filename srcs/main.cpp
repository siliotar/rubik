#include "Cube3.hpp"
#include "Solver.hpp"

int	main()
{
	srand(time(0));
	size_t	size = 0;
	Cube3	c;
	for (size_t i = 0; i < 500; ++i)
	{
		Solver	s;
		// std::string	tmp;

		// c.print();
		c.shuffle(20);
		std::cout << std::endl;
		// c.print();
		Commands	commands = s.solve(&c);
		size += commands.size();
		// std::cout << "size = " << commands.size() << std::endl;
		// std::cout << commands.str() << std::endl;
		c.print();
	}
	std::cout << (float)size / 500 << std::endl;
	return 0;
	// while (1)
	// {
	// 	std::cin >> tmp;
	// 	try
	// 	{
	// 		c.exec(tmp);
	// 	}
	// 	catch(const std::exception& e)
	// 	{
	// 		std::cerr << e.what() << '\n';
	// 	}
	// 	std::cout << std::endl;
	// 	c.print();
	// }
}
