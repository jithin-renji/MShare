#ifndef MSPACKET_HPP
#define MSPACKET_HPP

#include <stddef.h>
#include <string>

namespace MShare {

struct Packet {
  // Attempt to deserialize MShare packet received from the network.
  Packet(std::string& serialized);
  Packet();

  std::string serialize();

  uint32_t version;
  std::string pubkey_hash;
  std::string msg;
};

} // namespace MShare

#endif  // MSPACKET_HPP