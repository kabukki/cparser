//
// CParser.hpp for  in /home/le-rou_c/cpp/cparser
//
// Made by Lucien Le Roux
// Login   <le-rou_c@epitech.net>
//
// Started on  Sat Apr  8 11:19:49 2017 Lucien Le Roux
// Last update Sat Apr  8 21:47:59 2017 Lucien Le Roux
//

#ifndef CPARSER_HPP_
#define CPARSER_HPP_

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <algorithm>
#include <vector>

#define HEADER_SIZE	9
#define TAB_LENGTH	8

#define FG_BOLDRED	"\033[1;31m"
#define FG_RESET	"\033[0m"

#define IGNORE_COMMENTS	0x0001

/*
 * Known bugs:
 * -
 */

class CParser {
  /* Attr */
private:
  std::vector<std::string>	extensions;
  int				mark;
  int				options;
  /* Toggle to indicate a multi-line comment */
  bool				comment;

  /* Cons/Des */
public:
  CParser();
  ~CParser();

  /* Display an error */
private:
  void		c_printError(const std::string &line, const int res,
			     const size_t n, const size_t ndx,
			     const std::string &msg);

  /* Individual checks */
private:
  int		c_newline(const std::string line, const size_t n);
  int		c_80(const std::string line, const size_t n);
  int		c_brackets(const std::string line, const size_t n);
  int		c_comment(const std::string line, const size_t n);
  int		c_return(const std::string line, const size_t n);

public:
  void		c_norm(std::string file);

  /* Getters */
public:
  std::vector<std::string>	getExtensions(void) const;

  /* Setters */
public:
  void				addOption(const int option);

};

#endif /* CPARSER_HPP_ */
