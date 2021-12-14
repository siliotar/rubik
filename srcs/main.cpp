#include "Cube3.hpp"
#include "Solver.hpp"
#include "Visualizer.hpp"

void	multitest(Cube3 &c, size_t tCount, size_t sCount, bool beginner)
{
	Solver	s;
	size_t	size = 0;
	size_t	max = 0;
	size_t	min = 1000;
	size_t	big = 0;
	size_t	i;
	for (i = 0; i < tCount; ++i)
	{
		std::cout << c.shuffle(sCount) << std::endl;
		c.print();
		Commands	commands = s.solve(&c, true, beginner);
		size += commands.size();
		if (commands.size() > max)
			max = commands.size();
		if (commands.size() < min)
			min = commands.size();
		if (commands.size() > 150)
			++big;
		if (!c.assembled())
			break ;
		std::cout << std::endl;
	}
	if (!c.assembled())
		std::cout << "ERROR!!!" << std::endl;
	std::cout << "avg: " << (float)size / i << std::endl;
	std::cout << "min: " << min << std::endl;
	std::cout << "max: " << max << std::endl;
	std::cout << "> 150: " << big << std::endl;
}

int	displayUsage()
{
	std::cout << "Usage: rubik [OPTIONS] [ARGUMENTS]" << std::endl;
	std::cout << "Try 'rubik --help' for more information." << std::endl;
	return EXIT_FAILURE;
}

int	displayHelp()
{
	displayUsage();
	std::cout << std::endl;
	std::cout << "List of available commands:\tR, R', L, L', U, U', D, D', F, F', B, B'" << std::endl;
	std::cout << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "-c [command line]\t\tApply commands separated by a space to cube" << std::endl;
	std::cout << "\t\t\t\t  Doesn't work with -s and -t" << std::endl;
	std::cout << std::endl;
	std::cout << "-v\t\t\t\tLaunch the visualizer" << std::endl;
	std::cout << "\t\t\t\t  Doesn't work with -t" << std::endl;
	std::cout << std::endl;
	std::cout << "-s [COUNT]\t\t\tShuffle cube COUNT times" << std::endl;
	std::cout << "\t\t\t\t  Doesn't work with -c" << std::endl;
	std::cout << std::endl;
	std::cout << "-b\t\t\t\tUse a beginner's algorithm instead of an advanced" << std::endl;
	std::cout << std::endl;
	std::cout << "-t [COUNT]\t\t\tStarts the test with COUNT of different shuffles" << std::endl;
	std::cout << "\t\t\t\t  Doesn't work with -c and -v" << std::endl;
	std::cout << "\t\t\t\t  Shuffle 20 times by default" << std::endl;
	return EXIT_SUCCESS;
}

int	main(int argc, const char **argv)
{
	if (argc == 1)
		return displayUsage();
	std::string	option(argv[1]);
	if (option == "--help")
		return displayHelp();
	else if (option[0] == '-' && option.size() > 1)
	{
		char	flags = 0;
		Cube3	cube;
		int	arg = 3;
		int	sCount = 0;
		int	tCount = 0;
		std::string	cLine;
		for (size_t i = 1; i < option.size(); ++i)
		{
			if (option[i] == 'c')
			{
				if (flags & COMMANDLINE || flags & SHUFFLE || flags & TEST || argc < arg)
					return displayUsage();
				flags |= COMMANDLINE;
				cLine = argv[arg - 1];
				++arg;
			}
			else if (option[i] == 's')
			{
				if (flags & SHUFFLE || flags & COMMANDLINE || argc < arg)
					return displayUsage();
				flags |= SHUFFLE;
				sCount = atoi(argv[arg - 1]);
				if (sCount <= 0)
				{
					std::cerr << "COUNT must be greater than zero" << std::endl;
					return displayUsage();
				}
				++arg;
			}
			else if (option[i] == 'v')
			{
				if (flags & VISUALIZE || flags & TEST)
					return displayUsage();
				flags |= VISUALIZE;
			}
			else if (option[i] == 'b')
			{
				if (flags & BEGINNERALGO)
					return displayUsage();
				flags |= BEGINNERALGO;
			}
			else if (option[i] == 't')
			{
				if (flags & TEST || flags & COMMANDLINE || flags & VISUALIZE || argc < arg)
					return displayUsage();
				flags |= TEST;
				tCount = atoi(argv[arg - 1]);
				if (tCount <= 0)
				{
					std::cerr << "COUNT must be greater than zero" << std::endl;
					return displayUsage();
				}
				++arg;
			}
			else
			{
				std::cout << "Unknown option '" << option[i] << "'" << std::endl;
				std::cout << std::endl;
				return displayUsage();
			}
		}
		if (argc >= arg)
		{
			std::cout << "Too many arguments" << std::endl;
			std::cout << std::endl;
			return displayUsage();
		}
		std::string	shuff;
		if (flags & COMMANDLINE)
		{
			try
			{
				cube.execline(cLine);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				std::cout << std::endl;
				return displayUsage();
			}
			shuff += cLine;
			std::cout << "Shuffle: " << shuff << std::endl;
		}
		else if (flags & TEST)
		{
			srand(time(0));
			if (sCount == 0)
				sCount = 20;
			multitest(cube, tCount, sCount, flags & BEGINNERALGO);
			return EXIT_SUCCESS;
		}
		else if (flags & SHUFFLE)
		{
			srand(time(0));
			shuff += cube.shuffle(sCount);
			std::cout << "Shuffle: " << shuff << std::endl;
		}
		if (flags & VISUALIZE)
		{
			Commands	cmd;
			cmd.pushLine(shuff);
			Visualizer	v(3, true, flags & BEGINNERALGO);
			v.visualize(&cube, cmd);
		}
		else
		{
			cube.print();
			Commands	&cmd = cube.solve(true, flags & BEGINNERALGO);
			std::cout << cmd.str() << std::endl;
			std::cout << "Size = " << cmd.size() << std::endl;
		}
	}
	else
		return displayUsage();
	return EXIT_SUCCESS;
}
