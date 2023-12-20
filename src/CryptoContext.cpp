#include <CryptoContext.hpp>
#include <cryptopp/eccrypto.h>
#include <cryptopp/asn.h>
#include <cryptopp/oids.h>
#include <iostream>

namespace MShare
{
CryptoContext::CryptoContext(): d_(prng_, CryptoPP::ASN1::secp256r1()), e_(d_) { }

} // namespace MShare