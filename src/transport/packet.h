#pragma once

#include "address.h"
#include "data.h"
#include "transport_config.h"

namespace tcs {

enum class TcsPacketType {
  SERVICE_P = 1,
  STATE_P = 2,
  CONTROL_P = 3
};

class TcsPacket {
 public:
  TcsPacket() {}

  TcsPacket(int& packet_type, 
            TcsAddress& address,
            std::string& number,
            TcsData& data, 
            TcsTransportConfig& config)
    : packet_type_(static_cast<TcsPacketType>(packet_type)),
      address_(address),
      packet_number_(number),
      data_(data),
      config_(config) {}

  void set_packet_type(int value);
  void set_address(TcsAddress* address);
  void set_packet_id(std::string number);
  void set_packet_data(TcsData* data);
  void set_packet_config(TcsTransportConfig* config);

  TcsPacketType get_packet_type();
  TcsAddress get_address();
  std::string get_packet_id();
  TcsData get_packet_data();
  TcsTransportConfig get_packet_config();
  
 private:
  int version_ = 1;
  TcsPacketType packet_type_;
  TcsAddress address_;
  std::string packet_number_;
  TcsData data_;
  TcsTransportConfig config_;
};

void serialize(::tcs::TcsPacket* tcs_packet,
               std::string& proto_message);

void deserialize(::tcs::TcsPacket& tcs_packet,
                 std::string& msg);

} // tcs
