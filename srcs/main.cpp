#include "Cube3.hpp"
#include "Solver.hpp"

void	test(Cube3 &c, const std::string &line)
{
	c.execline(line);

	std::cout << std::endl;
	c.print();
	Solver	s;
	Commands	commands = s.solve(&c);
	std::cout << "size = " << commands.size() << std::endl;
	std::cout << commands.str() << std::endl;
	c.print();

}

//	140
void	test1(Cube3 &c)
{
	test(c, "U R D R L' R R U' D U R' D U R' B' L R' B L R'");
}

//	146
void	test2(Cube3 &c)
{
	test(c, "D R' F R' D' L U' D' L' D U' L' L' R B' U' B' F' D' L");
}

//	112
void	test3(Cube3 &c)
{
	test(c, "D U' B U F R B' D F' B R' B' F' U' B F L' L' U' U'");
}

//	156
void	test4(Cube3 &c)
{
	test(c, "D F D' R L' L' F U R' B' U' L F U L R' D L B D'");
}

//	204
void	test5(Cube3 &c)
{
	test(c, "F D D F D U' U' F' L U R' B' B' F' U' F' R' D' B F");
}

//	208
void	test6(Cube3 &c)
{
	test(c, "R' B R' R' L U F R' U' R' U' U' L' U D R' L' L' B' L");
}

//	202
void	test7(Cube3 &c)
{
	test(c, "L B L R L D' F D' U F L B D L' F B' B' R L' L'");
}

void	test8(Cube3 &c)
{
	test(c, "F' B' L B D F' R' B R' U L F' D R' R' B F' R R R");
}

void	multitest(Cube3 &c, size_t count)
{
	Solver	s;
	size_t	size = 0;
	size_t	max = 0;
	size_t	min = 1000;
	size_t	big = 0;
	size_t	i;
	for (i = 0; i < count; ++i)
	{
		c.shuffle(100);
		c.print();
		Commands	commands = s.solve(&c, true);
		size += commands.size();
		if (commands.size() > max)
			max = commands.size();
		if (commands.size() < min)
			min = commands.size();
		if (commands.size() > 150)
			++big;
			// break ;
	}
	std::cout << "avg: " << (float)size / i << std::endl;
	std::cout << "min: " << min << std::endl;
	std::cout << "max: " << max << std::endl;
	std::cout << "> 150: " << big << std::endl;
}

int	main()
{
	srand(time(0));
	Cube3	c;
	test5(c);
	// multitest(c, 3000);
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
