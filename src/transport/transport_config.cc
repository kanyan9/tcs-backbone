#include "transport_config.h"

namespace tcs {

TcsPriority TcsTransportConfig::get_priority() { return priority_; }

TcsSocketType TcsTransportConfig::get_socket_type() { return socket_type_; }

int TcsTransportConfig::get_qos() { return qos_; }
int TcsTransportConfig::get_reTransCount() { return reTransCount_; } 
int TcsTransportConfig::get_failCache() { return failCache_; }

void TcsTransportConfig::set_priority(int& value) {
  priority_ = static_cast<TcsPriority>(value);
}

void TcsTransportConfig::set_socket_type(int& value) {
  socket_type_ = static_cast<TcsSocketType>(value);
}

void TcsTransportConfig::set_qos(int& value) {
  qos_ = value;
}

void TcsTransportConfig::set_reTransCount(int& value) {
  reTransCount_ = value;
}

void TcsTransportConfig::set_failCache(int& value) {
  failCache_ = value;
}

} // namespace tcs