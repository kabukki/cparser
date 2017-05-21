#include "CParser.hpp"

static void usage(const char *bin)
{
  std::cerr << "NAME" << std::endl
	    << "	cparser - parse C files for Epitech norm" << std::endl
	    << std::endl
	    << "SYNOPSIS" << std::endl
	    << "	" << bin << " file [...] [-i]" << std::endl
	    << std::endl
	    << "DESCRIPTION" << std::endl
	    << "	Parses C files and reports errors according to " << std::endl
	    << "	the Epitech norm. Because it is very easy to " << std::endl
	    << "	overlook these and can fuck up your whole project/module." << std::endl
	    << std::endl
	    << "	-i, --ignore-comments		ignore comments" << std::endl
	    << "	-h, --help			display this help" << std::endl
	    << std::endl;
}

int main(int ac, char **av)
{
  CParser parser;
  std::vector<std::string> args;
  size_t i;

  if (ac >= 2) {
    for (i = 1; i < (size_t)ac; i++) {
      std::string arg = av[i];

      if (arg.compare("--ignore-comments") == 0 ||
	  arg.compare("-i") == 0) {
	parser.addOption(IGNORE_COMMENTS);
      } else if (arg.compare("--help") == 0 ||
		 arg.compare("-h") == 0) {
	usage(av[0]); return (1);
      } else if (arg.compare(0, 1, "-") == 0) {
	std::cerr << "Unknown option: " << arg << std::endl;
      } else
	args.push_back(arg);
    }
    for (i = 0; i < args.size(); i++) {
      parser.c_norm(args[i]);
    }
    std::cout << "C Parser is done, your mark is: " << parser.getMark() << std::endl;
  } else {
    std::cerr << "Usage: " << av[0] << " file [...]" << std::endl;
  }
  return 0;
}
