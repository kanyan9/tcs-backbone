#include <iostream>

#include "packet.h"
#include "../utils/logging.h"

#include "packet.pb.h"

namespace tcs {

void TcsPacket::set_packet_type(int value) {
  this->packet_type_ = static_cast<TcsPacketType>(value);
}

void TcsPacket::set_address(TcsAddress* address) {
  this->address_ = *address;
}

void TcsPacket::set_packet_id(std::string packet_id) {
  this->packet_number_ = packet_id;
}

void TcsPacket::set_packet_data(TcsData* data) {
  this->data_ = *data;
}

void TcsPacket::set_packet_config(TcsTransportConfig* config) {
  this->config_ = *config;
}

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

void serialize(::tcs::TcsPacket* tcs_packet, std::string& proto_message) {
  // TcsAddress protobuf 
  // TODO: add app_id?
  tcs::transport::Address* address = new tcs::transport::Address();
  TCS_LOG(INFO) << static_cast<int>(tcs_packet->get_address().get_type());
  TCS_LOG(INFO) << tcs_packet->get_address().get_address();
  address->set_addresstype(
      static_cast<int>(tcs_packet->get_address().get_type()));
  address->set_ip(tcs_packet->get_address().get_address());
  TCS_LOG(INFO) << "address serialize success";

  // TcsData protobuf
  tcs::transport::Data* data = new tcs::transport::Data();
  TCS_LOG(INFO) << tcs_packet->get_packet_data().get_content();  
  data->set_type(
      static_cast<int>(tcs_packet->get_packet_data().get_type()));
  data->set_content(tcs_packet->get_packet_data().get_content());
  TCS_LOG(INFO) << "data serialize success";

  // TcsTransportConfig protobuf 
  tcs::transport::TransportConfig* config = new tcs::transport::TransportConfig();
  config->set_sockettype(
      static_cast<int>(tcs_packet->get_packet_config().get_socket_type()));
  
  config->set_qos(tcs_packet->get_packet_config().get_qos());
  config->set_retranscount(tcs_packet->get_packet_config().get_reTransCount());
  config->set_failcache(tcs_packet->get_packet_config().get_failCache());
  config->set_priority(
        static_cast<int>(tcs_packet->get_packet_config().get_priority()));
  TCS_LOG(INFO) << "config serialize success";

  // TcsPacket protobuf 
  tcs::transport::Packet* packet = new tcs::transport::Packet();
  packet->set_type(static_cast<int>(tcs_packet->get_packet_type()));
  packet->set_package_id(tcs_packet->get_packet_id());
  packet->set_allocated_address(address);
  packet->set_allocated_data(data);
  packet->set_allocated_config(config);
  TCS_LOG(INFO) << "packet serial success";

  // Serialize
  packet->SerializeToString(&proto_message);
  TCS_LOG(INFO) << "protobuf message: " << proto_message;
  TCS_LOG(INFO) << "protobuf message size: " << proto_message.size();

  TCS_LOG(INFO) << "generate byte array success";
}

void deserialize(::tcs::TcsPacket& tcs_packet, std::string& msg) {
  tcs::transport::Packet* packet = new tcs::transport::Packet();
  packet->ParseFromString(msg);

  tcs_packet.set_packet_type(packet->type());
  tcs_packet.set_packet_id(packet->package_id());

  if (packet->has_address()) {
    TcsAddress* address = new TcsAddress();
    address->set_type(packet->address().addresstype());
    address->set_address(packet->address().ip());

    tcs_packet.set_address(address);
  }

  if (packet->has_data()) {
    TcsData* data = new TcsData();
    data->set_type(packet->data().type());
    data->set_contect(packet->data().content());

    tcs_packet.set_packet_data(data);
  }

  if (packet->has_config()) {
    TcsTransportConfig* config = new TcsTransportConfig();
    config->set_socket_type(packet->config().sockettype());
    config->set_priority(packet->config().priority());
    config->set_qos(packet->config().qos());
    config->set_failCache(packet->config().failcache());
    config->set_failCache(packet->config().retranscount());

    tcs_packet.set_packet_config(config);
  }
}

} // namespace tcs
