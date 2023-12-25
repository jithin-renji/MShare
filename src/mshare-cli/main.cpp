#include <ArgParser.hpp>
#include <Logger.hpp>
#include <MessageClient.hpp>
#include <Crypto.hpp>

#include <any>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#ifdef __APPLE__
  #include <cstring>
  #include <libproc.h>
#endif

using MShare::status;
using MShare::warn;
using MShare::error;

void version() {
  std::cout << "mshare-cli v0.1\n"
            << "Copyright (C) 2023 Jithin Renji.\n"
            << "Free software licensed under the GNU GPLv3.\n";
}

bool is_mshared_alive() {
#if defined(__APPLE__)
  pid_t pids[2048];
  int bytes = proc_listpids(PROC_ALL_PIDS, 0, pids, 2048);
  int n_proc = bytes / sizeof(pid_t);
  for (int i = 0; i < n_proc; i++) {
    struct proc_bsdinfo proc;
    int ret = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0, &proc, PROC_PIDTBSDINFO_SIZE);
    if (ret == PROC_PIDTBSDINFO_SIZE && std::strcmp("mshared", proc.pbi_name) == 0) {
      return true;
    }
  }

  return false;
#elif defined(linux)
  warn() << "Make sure mshared is running.\n";
  return true;
#endif
}

int mshare_cli_main(const MShare::ParsedOptions& options) {
  if (!is_mshared_alive()) {
    error() << "mshared is not running.\n";
    return -1;
  }

  MShare::CryptoContext cc;
  if (options.contains("message")) {
    std::string msg = std::any_cast<std::string>(options.at("message"));
    status() << "Trying to send: \"" << msg << "\"\n";

    try {
      MShare::MessageClient client(cc);
      client.send_msg(msg);
    } catch (MShare::ClientStartupError& e) {
      error() << e.what() << '\n';
      return -1;
    } catch (MShare::ClientSendError& e) {
      error() << e.what() << '\n';
    }
  }

  return 0;
}

int main(int argc, char *argv[]) {
  MShare::OptionList options = {
    {"to", MShare::Option::KWARG, MShare::Option::STRING,
      "Send message to this contact."},
    {"message", MShare::Option::KWARG, MShare::Option::STRING,
      "Message to be sent."},
    {"new-contact", MShare::Option::KWARG, MShare::Option::STRING,
      "Add new contact."},
    {"help", MShare::Option::FLAG, MShare::Option::NONE,
      "Show this help message and exit."},
    {"version", MShare::Option::FLAG, MShare::Option::NONE,
      "Show version information and exit."}
  };

  MShare::ParsedOptions parsed_options;
  try {
    MShare::ArgParser parser(argc, argv, options);
    if (argc < 2) {
      parser.print_help();
      return 0;
    }

    parsed_options = parser.get();
    if (parsed_options.contains("help")) {
      parser.print_help();
    } else if (parsed_options.contains("version")) {
      version();
    }
  } catch (MShare::UnknownOptionError& e) {
    std::cerr << e.what() << '\n';
    return -1;
  } catch (MShare::NoValueForOptionError& e) {
    std::cerr << e.what() << '\n';
    return -1;
  } catch (MShare::UnexpectedArgumentError& e) {
    std::cerr << e.what() << '\n';
    return -1;
  }

  return mshare_cli_main(parsed_options);
}
