#pragma once

#include "address.h"
#include "data.h"
#include "transport_config.h"

namespace tcs {

enum class PacketType {
  SERVICE_P = 1,
  STATE_P = 2,
  CONTROL_P = 3
};

class Packet {
 public:
  Packet(int& packet_type, 
         Address& address,
         std::string& number,
         Data& data, 
         TransportConfig& config)
      : packet_type_(static_cast<PacketType>(packet_type)),
        address_(address),
        packet_number_(number),
        data_(data),
        config_(config) {}

 private:
  int version_ = 1;
  PacketType packet_type_;
  Address address_;
  std::string packet_number_;
  Data data_;
  TransportConfig config_;
};

} // tcs
