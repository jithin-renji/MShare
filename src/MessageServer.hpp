#ifndef MSMESSAGE_SERVER_HPP
#define MSMESSAGE_SERVER_HPP

#include <CryptoContext.hpp>

#include <cstdint>
#include <thread>

namespace MShare {

class MessageServer {
public:
  MessageServer(CryptoContext& cctx);

  std::thread spawn();

private:
  uint16_t port_;
  int sfd_;
  CryptoContext& cctx_;

  void run();
};

} // namespace MShare

#endif  // MSMESSAGE_SERVER_HPP