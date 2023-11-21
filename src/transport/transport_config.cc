#include "transport_config.h"

namespace tcs {

Priority TransportConfig::get_priority() { return priority_; }

SocketType TransportConfig::get_socket_type() { return socket_type_; }

void TransportConfig::set_priority(int& value) {
  priority_ = static_cast<Priority>(value);
}

void TransportConfig::set_socket_type(int& value) {
  socket_type_ = static_cast<SocketType>(value);
}

void TransportConfig::set_qos(int& value) {
  qos_ = value;
}

void TransportConfig::set_reTransCount(int& value) {
  reTransCount_ = value;
}

void TransportConfig::set_failCache(int& value) {
  failCache_ = value;
}

} // namespace tcs