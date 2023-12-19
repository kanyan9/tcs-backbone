#pragma once

#include <string>

#include "packet.h"

namespace tcs {

class TcsSocket {
 public:
  TcsSocket();

  ~TcsSocket();

  void connect();

  void send(const char* message);
  // void send(std::string message);
  void send(TcsPacket* packet);

  void receive(TcsPacket& packet);
  
  void close();

 private:
  static std::string server_ip_;
  static int server_port_;
  static int max_frame_length_;
  static int reconnect_interval_;
  static std::string app_id;

  void* connect_provider_;
};

} // namespace tcs
