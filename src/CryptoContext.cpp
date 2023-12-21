#include <CryptoContext.hpp>
#include <Logger.hpp>

#include <cryptopp/files.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/asn.h>
#include <cryptopp/oids.h>

#include <iostream>
#include <filesystem>
#include <memory>

namespace MShare
{

CryptoContext::CryptoContext(): msdir_(".mshare") {
  namespace fs = std::filesystem;

  if (!fs::exists(msdir_)) {
    fs::create_directory(msdir_);
    warn() << "Creating directory " << msdir_ << '\n';
  }

  bool use_new_keys = false;
  if (!fs::exists(msdir_ / "pubkey") || !fs::exists(msdir_ / "privkey")) {
    warn() << "No keys in " << msdir_ << ". Generating...\n";
    use_new_keys = true;
  }

  CryptoPP::ECIES<CryptoPP::ECP> d0;

  if (use_new_keys) {
    decryptor_ = std::make_unique<Decyptor>(prng_, CryptoPP::ASN1::secp256r1());
    encryptor_ = std::make_unique<Encryptor>(*decryptor_);
    save_keys();
    status() << "Done.\n";
  } else {
    load_keys();
  }
}

std::string CryptoContext::encrypt(std::string input) {
  std::string ciphertext;
  CryptoPP::StringSource ss(
    input,
    true,
    new CryptoPP::PK_EncryptorFilter(
      prng_,
      *encryptor_,
      new CryptoPP::StringSink(ciphertext)
    )
  );

  return ciphertext;
}

std::string CryptoContext::decrypt(std::string input) {
  std::string plaintext;
  CryptoPP::StringSource ss(
    input,
    true,
    new CryptoPP::PK_DecryptorFilter(
      prng_,
      *decryptor_,
      new CryptoPP::StringSink(plaintext)
    )
  );

  return plaintext;
}

void CryptoContext::save_keys() {
  CryptoPP::FileSink pubkey_sink((msdir_ / "pubkey").c_str());
  encryptor_->GetPublicKey().Save(pubkey_sink);

  CryptoPP::FileSink privkey_sink((msdir_ / "privkey").c_str());
  decryptor_->GetPrivateKey().Save(privkey_sink);
}

void CryptoContext::load_keys() {
  CryptoPP::FileSource pubkey_source((msdir_ / "pubkey").c_str(), true);
  encryptor_ = std::make_unique<Encryptor>();
  encryptor_->AccessPublicKey().Load(pubkey_source);

  CryptoPP::FileSource privkey_source((msdir_ / "privkey").c_str(), true);
  decryptor_ = std::make_unique<Decyptor>();
  decryptor_->AccessPrivateKey().Load(privkey_source);
}


} // namespace MShare