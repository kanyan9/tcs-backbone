#include "packet.h"

namespace tcs {

TcsPacketType TcsPacket::get_packet_type() {
  return packet_type_;
}
TcsAddress TcsPacket::get_address() {
  return address_;
}

std::string TcsPacket::get_packet_id() {
  return packet_number_;
}

TcsData TcsPacket::get_packet_data() {
  return data_;
}

TcsTransportConfig TcsPacket::get_packet_config() {
  return config_;
}

void serialize(::tcs::TcsPacket& tcs_packet,
               ::tcs::transport::Packet& packet) {
  // TcsAddress serialize
  // TODO: add app_id?
  tcs::transport::Address* address;
  address->set_addresstype(
      static_cast<int>(tcs_packet.get_address().get_type()));
  address->set_ip(tcs_packet.get_address().get_address());

  // TcsData serialize
  tcs::transport::Data* data;
  data->set_type(
      static_cast<int>(tcs_packet.get_packet_data().get_type()));
  data->set_content(tcs_packet.get_packet_data().get_content());

  // TcsTransportConfig serialize
  tcs::transport::TransportConfig* config;
  config->set_sockettype(
      static_cast<int>(tcs_packet.get_packet_config().get_socket_type()));
  
  config->set_qos(tcs_packet.get_packet_config().get_qos());
  config->set_retranscount(tcs_packet.get_packet_config().get_reTransCount());
  config->set_failcache(tcs_packet.get_packet_config().get_failCache());
  config->set_priority(
      static_cast<int>(tcs_packet.get_packet_config().get_priority()));

  // TcsPacket serialize
  packet.set_type(static_cast<int>(tcs_packet.get_packet_type()));
  packet.set_package_id(tcs_packet.get_packet_id());
  packet.set_allocated_address(address);
  packet.set_allocated_data(data);
  packet.set_allocated_config(config);
}

void deserialize(::tcs::TcsPacket& tcs_packet,
                 ::tcs::transport::Packet& packet) {
  return;
}

} // namespace tcs