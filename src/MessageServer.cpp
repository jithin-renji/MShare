#include <MessageServer.hpp>
#include <Logger.hpp>

namespace MShare {

MessageServer::MessageServer(CryptoContext& cctx): cctx_{cctx} { }

std::thread MessageServer::spawn() {
  return std::thread([this] { run(); });
}

void MessageServer::run() {
  status() << "Started message server thread.\n";
}

} // namespace MShare