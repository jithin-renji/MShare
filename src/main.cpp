#include <CryptoContext.hpp>

#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

#include <ios>
#include <iostream>
#include <string>

int main() {
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

  std::cout << cc << '\n';
  std::cout << "E: " << ec << '\n';
  std::cout << "D: " << cc.decrypt(ciphertext) << '\n';

  return 0;
}
