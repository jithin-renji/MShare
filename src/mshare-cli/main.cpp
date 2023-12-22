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
    {"to", MShare::Option::KWARG, MShare::Option::STRING,
      "Send message to this contact."},
    {"message", MShare::Option::KWARG, MShare::Option::STRING,
      "Message to be sent."},
    {"new-contact", MShare::Option::KWARG, MShare::Option::STRING,
      "Add new contact."},
    {"help", MShare::Option::FLAG, MShare::Option::NONE,
      "Show this help message and exit."},
    {"version", MShare::Option::FLAG, MShare::Option::NONE,
      "Show version information and exit."}
  };

  MShare::ParsedOptions parsed_options;
  try {
    MShare::ArgParser parser(argc, argv, options);
    if (argc < 2) {
      parser.print_help();
      return 0;
    }

    parsed_options = parser.get();
    if (parsed_options.contains("help")) {
      parser.print_help();
    } else if (parsed_options.contains("version")) {
      version();
    }
  } catch (MShare::UnknownOptionError& e) {
    std::cout << e.what() << '\n';
    return -1;
  } catch (MShare::NoValueForOptionError& e) {
    std::cout << e.what() << '\n';
    return -1;
  }

  for (MShare::Option& option : options) {
    // std::cout << "Checking option: " << option.name << '\n';
    if (option.expected_val_type == MShare::Option::NONE)
      continue;

    if (parsed_options.contains(option.name)) {
      if (option.expected_val_type == MShare::Option::STRING)
        std::cout << std::setw(20) << std::left << option.name << std::any_cast<std::string>(parsed_options.at(option.name)) << '\n';
    }
  }

  return 0;
}