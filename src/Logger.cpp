#include <Logger.hpp>

namespace MShare {

std::ostream &warn(std::ostream &os) {
  os << "[WARN] ";
  return os;
}

std::ostream &status(std::ostream &os) {
  os << "[STATUS] ";
  return os;
}

}