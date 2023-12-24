#include <ArgParser.hpp>
#include <Crypto.hpp>
#include <MessageServer.hpp>
#include <Logger.hpp>

#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

#include <ios>
#include <iostream>
#include <string>

void version() {
  std::cout << "mshared v0.1\n"
            << "Copyright (C) 2023 Jithin Renji.\n"
            << "Free software licensed under the GNU GPLv3.\n";
}

int main(int argc, char *argv[]) {
  using MShare::status;
  using MShare::warn;
  using MShare::error;

  MShare::OptionList options = {
    {"help", MShare::Option::FLAG, MShare::Option::NONE,
      "Show this help message and exit."},
    {"version", MShare::Option::FLAG, MShare::Option::NONE,
      "Show version information and exit."}
  };

  MShare::ParsedOptions parsed_options;

  try {
    MShare::ArgParser parser(argc, argv, options);
    parsed_options = parser.get();
    if (parsed_options.contains("help")) {
      parser.print_help();
      return 0;
    } else if (parsed_options.contains("version")) {
      version();
      return 0;
    }
  } catch (MShare::UnknownOptionError& e) {
    std::cerr << e.what() << '\n';
    return -1;
  }

  MShare::CryptoContext cc;
  status() << "PK hash: " << MShare::to_hex(cc.get_pubkey_hash()) << '\n';

  try {
    MShare::MessageServer server(cc);
  } catch (MShare::ServerStartupError& e) {
    MShare::error() << e.what() << '\n';
    return -1;
  }

  return 0;
}
