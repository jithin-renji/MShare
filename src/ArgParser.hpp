#ifndef MSARG_PARSER_HPP
#define MSARG_PARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

namespace MShare {

struct UnknownOptionError : public std::exception {
  const char* what() const noexcept override;
};

struct Option {
  std::string name;

  enum Type {
    FLAG,   // eg. --verbose
    // ARG,    // eg. -n 10
    KWARG   // eg. --number 10
  } type;

  enum ExpectedValType {
    INT,
    FLOAT,
    STRING,
    NONE
  } expected_val_type = NONE;

  std::string help;
};

using OptionList = std::vector<Option>;
using ParsedOptions = std::unordered_map<std::string, std::string>;

class ArgParser {
public:
  ArgParser(int argc, char *argv[], const OptionList& options);

  const ParsedOptions get();
  void print_help(std::ostream& os = std::cout);

private:
  std::string progname_;
  OptionList options_;
  std::vector<std::string> original_args_;
  std::unordered_map<std::string, std::string> parsed_options_;

  void parse();
};

} // namespace MShare

#endif