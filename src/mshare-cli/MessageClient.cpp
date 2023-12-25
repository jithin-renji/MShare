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

const char* ClientStartupError::what() const noexcept {
  return what_str_.c_str();
}

ClientSendError::ClientSendError(std::string what_str): what_str_(what_str) { }

const char* ClientSendError::what() const noexcept {
  return what_str_.c_str();
}

MessageClient::MessageClient(CryptoContext& cc): cc_{cc} {
  sfd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (sfd_ == -1) {
    throw ClientStartupError("Socket creation failed.");
  }
}

MessageClient::~MessageClient() {
  close(sfd_);
  status() << "Client bye.\n";
}

void MessageClient::send_msg(std::string& msg) {
  status() << "PK hash: " << to_hex(cc_.get_pubkey_hash()) << '\n';

  struct sockaddr_in saddr = {
    .sin_family = AF_INET,
    .sin_port = htons(3000)
  };

  if (inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr) != 1) {
    throw ClientSendError("Address parsing failed.");
  }

  ssize_t nbytes_sent = sendto(sfd_, msg.c_str(), msg.length(), 0, (struct sockaddr *) &saddr, sizeof(saddr));
  if (nbytes_sent == -1 || nbytes_sent != msg.length()) {
    throw ClientSendError("Full message send failed.");
  }
}

} // namespace MShare
