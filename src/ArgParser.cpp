#include <ArgParser.hpp>

#include <iomanip>
#include <algorithm>

namespace MShare {

const char* UnknownOptionError::what() const noexcept {
  return "Unknown option encountered during command-line parsing.";
}

ArgParser::ArgParser(int argc, char *argv[], const OptionList& options): progname_(argv[0]), options_(options) {
  // For convenience.
  for (int i = 0; i < argc; i++) {
    original_args_.push_back(argv[i]);
  }

  parse();
}

const ParsedOptions ArgParser::get() {
  return parsed_options_;
}

void ArgParser::print_help(std::ostream& os) {
  os << "Usage: " << progname_ << " [options]\n";
  os  << "Options:\n";
  for (Option& option : options_) {
    os << "  --" << std::setw(20) << std::left << option.name << std::setw(20) << option.help << '\n';
  }
}

void ArgParser::parse() {
  // TODO: handle non-flag args.
  bool expecting_arg = false;
  for (std::string& arg : original_args_) {
    if (arg.length() > 2 && arg.substr(0, 2) == "--") {
      std::string option_name = arg.substr(2);
      auto found_option = std::find_if(options_.begin(), options_.end(), [&option_name](const Option& option) {
        return option.name == option_name;
      });
      if (found_option == options_.end()) {
        throw UnknownOptionError{};
      }

      if (found_option->type == Option::FLAG) {
        parsed_options_[option_name] = "true";
      }
    }
  }
}

} // namespace MShare