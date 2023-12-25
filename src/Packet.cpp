#include "Crypto.hpp"
#include "Logger.hpp"
#include <Packet.hpp>

namespace MShare {

PacketizationError::PacketizationError(std::string what_str): what_str_(what_str) { }

const char* PacketizationError::what() const noexcept {
  return what_str_.c_str();
}

Packet::Packet(std::string serialized) {
  using MShare::status;

  size_t delim_idx = serialized.find('_');
  if (delim_idx == std::string::npos) {
    throw PacketizationError("No delimiter in serialized packet.");
  }

  version = serialized.substr(0, delim_idx);
  serialized = serialized.substr(delim_idx + 1);

  status() << "Got version: " << "\"" << version << "\"" << '\n';

  delim_idx = serialized.find('_');
  if (delim_idx == std::string::npos) {
    throw PacketizationError("No delimiter in serialized packet.");
  }

  pubkey_hash = serialized.substr(0, delim_idx);
  serialized = serialized.substr(delim_idx + 1);

  status() << "Got pkh: " << "\"" << to_hex(pubkey_hash)<< "\"" << '\n';

  msg = serialized;
}

Packet::Packet(): version("0.1") { }

std::string Packet::serialize() {
  return version + "_" + pubkey_hash + "_" + msg;
}

} // namespace MShare
