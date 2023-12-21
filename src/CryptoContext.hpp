#ifndef MSCRYPTO_CONTEXT_HPP
#define MSCRYPTO_CONTEXT_HPP

#include <cryptopp/osrng.h>
#include <cryptopp/eccrypto.h>

#include <iostream>
#include <streambuf>
#include <string_view>
#include <filesystem>
#include <memory>

namespace MShare
{

namespace fs = std::filesystem;

class CryptoContext
{
public:
  CryptoContext();

  std::string encrypt(std::string input);
  std::string decrypt(std::string input);

private:
  using Decyptor = CryptoPP::ECIES<CryptoPP::ECP>::Decryptor;
  using Encryptor = CryptoPP::ECIES<CryptoPP::ECP>::Encryptor;

  fs::path msdir_;

  CryptoPP::AutoSeededRandomPool prng_;
  std::unique_ptr<Decyptor> decryptor_;
  std::unique_ptr<Encryptor> encryptor_;

  void save_keys();
  void load_keys();
};

std::ostream &operator<<(std::ostream &os, CryptoContext &cc);

} // namespace MShare

#endif  // MSCRYPTO_CONTEXT_HPP
