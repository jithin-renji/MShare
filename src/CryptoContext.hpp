#ifndef MSCRYPTO_CONTEXT_HPP
#define MSCRYPTO_CONTEXT_HPP

#include <cryptopp/osrng.h>
#include <cryptopp/eccrypto.h>

#include <iostream>

namespace MShare
{

class CryptoContext
{
public:
  CryptoContext();

private:
  CryptoPP::AutoSeededRandomPool prng_;
  CryptoPP::ECIES<CryptoPP::ECP>::Decryptor d_;
  CryptoPP::ECIES<CryptoPP::ECP>::Encryptor e_;
};

std::ostream &operator<<(std::ostream &os, CryptoContext &cc);

} // namespace MShare



#endif  // MSCRYPTO_CONTEXT_HPP
