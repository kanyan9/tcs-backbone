#pragma once

namespace tcs {

enum class Priority {
  P1 = 1,
  P2 = 2,
  P3 = 3,
  P4 = 4,
  P5 = 5,
  P6 = 6
};

enum class SocketType {
  UDP = 1,
  TCP = 2,
  UDT = 3,
  KCP = 4
};

class TransportConfig {
 public:
  TransportConfig() {}

  TransportConfig(int& socket_type,
                  int& priority,
                  int& qos,
                  int& reTransCount,
                  int& failCache)
    : socket_type_(static_cast<SocketType>(socket_type)),
      priority_(static_cast<Priority>(priority)),
      qos_(qos),
      reTransCount_(reTransCount),
      failCache_(failCache) {}

  Priority get_priority();
  SocketType get_socket_type();

  void set_priority(int& value);
  void set_socket_type(int& value);
  void set_qos(int& value);
  void set_reTransCount(int& value);
  void set_failCache(int& value);

 private:
  SocketType socket_type_;
  Priority priority_;
  int qos_;
  int reTransCount_;
  int failCache_;
};

} // namespace tcs