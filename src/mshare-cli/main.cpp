#include <ArgParser.hpp>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void version() {
  std::cout << "mshare-cli v0.1\n"
            << "Copyright (C) 2023 Jithin Renji.\n"
            << "Free software licensed under the GNU GPLv3.\n";
}

int main(int argc, char *argv[]) {
  MShare::OptionList options = {
    {"help", MShare::Option::FLAG, MShare::Option::NONE,
      "Show this help message and exit."},
    {"version", MShare::Option::FLAG, MShare::Option::NONE,
      "Show version information and exit."}
  };

  try {
    MShare::ArgParser parser(argc, argv, options);
    MShare::ParsedOptions parsed_options = parser.get();
    if (parsed_options.contains("help")) {
      parser.print_help();
    } else if (parsed_options.contains("version")) {
      version();
    }
  } catch (MShare::UnknownOptionError& e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}