#pragma once

#include <string>
#include "handy.h"
#include "conn.h"

namespace tcs {

class LocalSocket {
 public:
  LocalSocket() {}

  ~LocalSocket();

  void connect();
  void send(std::string message);
  void close();

 private:
  static unsigned char protocol_flag_;
  static std::string server_ip_;
  static int server_port_;
  static int max_frame_length_;
  static std::string app_id;

  handy::TcpConnPtr conn_;
};

typedef tcs::LocalSocket TcsSocket;

} // namespace tcs
