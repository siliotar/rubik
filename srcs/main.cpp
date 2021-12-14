#include "Cube3.hpp"
#include "Solver.hpp"
#include "Visualizer.hpp"

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
		std::cout << c.shuffle(20) << std::endl;
		c.print();
		Commands	commands = s.solve(&c, true);
		size += commands.size();
		if (commands.size() > max)
			max = commands.size();
		if (commands.size() < min)
			min = commands.size();
		if (commands.size() > 150)
			++big;
		if (!c.assembled())
			break ;
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
	std::string	shuf = c.shuffle(20);
	std::cout << shuf << std::endl;
	Cube3	copy(c);
	Commands	&comm = copy.solve();
	std::cout << comm.str() << std::endl;
	Visualizer	v(3);
	v.visualize(&c, comm);
	return 0;
}
