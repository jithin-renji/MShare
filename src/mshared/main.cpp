#include <ArgParser.hpp>
#include <CryptoContext.hpp>
#include <MessageServer.hpp>

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
  MShare::OptionList options = {
    {"help", MShare::Option::FLAG, MShare::Option::NONE,
      "Show this help message and exit."},
    {"version", MShare::Option::FLAG, MShare::Option::NONE,
      "Show version information and exit."}
  };

  try {
    MShare::ArgParser parser(argc, argv, options);
    const MShare::ParsedOptions parsed_options = parser.get();
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
  std::string ciphertext = cc.encrypt("Hello, world!");
  std::string ec;

  CryptoPP::StringSource ss(
    ciphertext,
    ciphertext.size(),
    new CryptoPP::HexEncoder(
      new CryptoPP::StringSink(ec),
      false
    )
  );

  std::cout << "E: " << ec << '\n';
  std::cout << "D: " << cc.decrypt(ciphertext) << '\n';

  MShare::MessageServer s(cc);
  std::thread t = s.spawn();
  t.join();

  return 0;
}
