#include <MessageClient.hpp>
#include <Crypto.hpp>
#include <Packet.hpp>
#include <Logger.hpp>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace MShare {

ClientStartupError::ClientStartupError(std::string what_str): what_str_(what_str) { }

MessageClient::MessageClient(CryptoContext& cc): cc_{cc} {
  sfd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (sfd_ == -1) {
    throw ClientStartupError("Socket creation failed.");
  }

  status() << "PK hash: " << to_hex(cc_.get_pubkey_hash()) << '\n';
}

MessageClient::~MessageClient() {
  close(sfd_);
  status() << "Client bye.\n";
}

} // namespace MShare
