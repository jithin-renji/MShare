#ifndef MSMESSAGE_CLIENT_HPP
#define MSMESSAGE_CLIENT_HPP

#include <Crypto.hpp>

#include <string>
#include <stdexcept>

namespace MShare {

class ClientStartupError : public std::exception {
public:
  ClientStartupError(std::string what_str);

private:
  std::string what_str_;
};

class MessageClient {
public:
  MessageClient(CryptoContext& cc);
  ~MessageClient();

  void send_msg(std::string& msg);

private:
  CryptoContext& cc_;
  int sfd_;
};

} // namespace MShare

#endif  // MSMESSAGE_CLIENT_HPP
