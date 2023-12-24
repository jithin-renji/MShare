#include <ArgParser.hpp>
#include <Logger.hpp>
#include <MessageClient.hpp>
#include <Crypto.hpp>

#include <any>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using MShare::status;

void version() {
  std::cout << "mshare-cli v0.1\n"
            << "Copyright (C) 2023 Jithin Renji.\n"
            << "Free software licensed under the GNU GPLv3.\n";
}

int mshare_cli_main(const MShare::ParsedOptions& options) {
  MShare::CryptoContext cc;
  if (options.contains("message")) {
    status() << "Trying to send: \"" << std::any_cast<std::string>(options.at("message")) << "\"\n";

    MShare::MessageClient client(cc);
    status() << "Client is alive.\n";
  }

  return 0;
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
    std::cerr << e.what() << '\n';
    return -1;
  } catch (MShare::NoValueForOptionError& e) {
    std::cerr << e.what() << '\n';
    return -1;
  } catch (MShare::UnexpectedArgumentError& e) {
    std::cerr << e.what() << '\n';
    return -1;
  }

  return mshare_cli_main(parsed_options);
}
