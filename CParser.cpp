//
// CParser.cpp for  in /home/le-rou_c/cpp/cparser
// 
// Made by Lucien Le Roux
// Login   <le-rou_c@epitech.net>
// 
// Started on  Sat Apr  8 11:22:19 2017 Lucien Le Roux
// Last update Wed May 17 19:19:33 2017 Lucien Le Roux
//

#include "CParser.hpp"

CParser::CParser(void)
  : extensions()
  , mark(0)
  , comment(false) {
  std::string ext[] = {"hpp", "cpp", "c"};
  size_t i;

  for (i = 0; i < sizeof(ext) / sizeof(ext[0]); i++)
    extensions.push_back(ext[i]);
}
CParser::~CParser(void) {}

void CParser::c_printError(const std::string &line, const int res,
			   const size_t n, const size_t ndx,
			   const std::string &msg) {
  std::cerr << FG_BOLDRED "Line " << n << ": " << msg << " (" << res << ")" FG_RESET << std::endl;
  std::cerr << line << "$" << std::endl;
  std::cerr << std::string(ndx, ' ') << "^" << std::endl;
}

int CParser::c_newline(const std::string line, const size_t n) {
  size_t ndx = line.size() - 1;
  int res = (n > HEADER_SIZE && *line.rbegin() == ' ') ? -5 : 0;

  if (res)
    c_printError(line, res, n, ndx, "Whitespace at end of line");
  return res;
}

int CParser::c_80(const std::string line, const size_t n) {
  size_t ndx = 81;
  int res = (line.size() > 80) ? -5 : 0;

  if (res)
    c_printError(line, res, n, ndx, "Line exceeds 80 characters");
  return res;
}

int CParser::c_brackets(const std::string line, const size_t n) {
  size_t ndx = line.find(") {");
  int res;

  ndx = (ndx == std::string::npos ? line.find("else {") : ndx);
  ndx = (ndx == std::string::npos ? line.find("} else") : ndx);
  if ((res = (ndx != std::string::npos) ? -1 : 0))
    c_printError(line, res, n, ndx, "Curly brackets not isolated");
  return res;
}

int CParser::c_comment(const std::string line, const size_t n) {
  size_t ndx = line.find("//");
  int res = (n > HEADER_SIZE && ndx != std::string::npos) ? -1 : 0;

  if (res)
    c_printError(line, res, n, ndx, "Comment in code");
  return res;
}

int CParser::c_return(const std::string line, const size_t n) {
  size_t ndx = line.find("return ");
  int res;

  if (ndx == std::string::npos) res = 0;
  else if (line.substr(ndx + 6).find(";") == std::string::npos ||
	   line.substr(ndx + 6).find(" ;") == std::string::npos) {
    res = (line.substr(ndx + 6).find("(") == std::string::npos) ? -1 : 0;
  }
  if (res)
    c_printError(line, res, n, ndx, "Invalid return format");
  return res;
}

static void replaceTabs(std::string &s) {
  size_t ndx;

  while ((ndx = s.find("\t")) != std::string::npos) {
    s.replace(ndx, 1, "        ", 0, TAB_LENGTH - ndx % TAB_LENGTH);
  }
}

/*
 * Indicates if a line starts with a given string,
 * ignoring the first spaces
 */
static bool startsWith(const std::string & line,
		       const std::string & target) {
  std::string cpy(line);

  std::remove(cpy.begin(), cpy.end(), ' ');
  return (cpy.compare(0, target.size(), target) == 0);
}

void CParser::c_norm(std::string file) {
  std::ifstream input(file.c_str(), std::ios::in);
  std::string line;
  size_t n;

  if (input) {
    if (std::find(extensions.begin(), extensions.end(), file.substr(file.rfind(".") + 1))
	!= extensions.end()) {
      std::cout << "[+] C Parser starting for file " << file << ":" << std::endl;
      for (n = 1; getline(input, line); n++) {
	replaceTabs(line);
	comment = startsWith(line, "//");
	/*
	 * If line is a comment, notify the user
	 * (if --ignore-comments switch not enabled)
	 */
	if (options ^ IGNORE_COMMENTS)
	  mark += c_comment(line, n);
	// If line is not commented, parse it
	if (!comment) {
	  mark += c_newline(line, n);
	  mark += c_80(line, n);
	  mark += c_brackets(line, n);
	  mark += c_return(line, n);
	}
      }
      std::cout << "[-] C Parser finished for file " << file << "." << std::endl;
    } else {
      std::cerr << "[-] cparser: " + file + ": Does not have a valid extension, ignored" << std::endl;
    }
    input.close();
  } else {
    std::cerr << "[-] cparser: " + file + ": No such file or directory" << std::endl;
  }
}

std::vector<std::string>	CParser::getExtensions(void) const {
  return extensions;
}
int				CParser::getMark(void) const {
  return mark;
}
void				CParser::addOption(const int option) {
  options |= option;
}
