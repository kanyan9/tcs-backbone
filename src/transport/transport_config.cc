#include "transport_config.h"

namespace tcs {

void TcsTransportConfig::set_priority(int value) {
  this->priority_ = static_cast<TcsPriority>(value);
}

void TcsTransportConfig::set_socket_type(int value) {
  this->socket_type_ = static_cast<TcsSocketType>(value);
}

void TcsTransportConfig::set_qos(int value) {
  this->qos_ = value;
}

void TcsTransportConfig::set_reTransCount(int value) {
  this->reTransCount_ = value;
}

void TcsTransportConfig::set_failCache(int value) {
  this->failCache_ = value;
}

TcsPriority TcsTransportConfig::get_priority() { return priority_; }

TcsSocketType TcsTransportConfig::get_socket_type() { return socket_type_; }

int TcsTransportConfig::get_qos() { return qos_; }
int TcsTransportConfig::get_reTransCount() { return reTransCount_; } 
int TcsTransportConfig::get_failCache() { return failCache_; }


} // namespace tcs