#pragma once

namespace tcs {

enum class TcsPriority {
  P1 = 1,
  P2 = 2,
  P3 = 3,
  P4 = 4,
  P5 = 5,
  P6 = 6
};

enum class TcsSocketType {
  UDP = 1,
  TCP = 2,
  UDT = 3,
  KCP = 4
};

class TcsTransportConfig {
 public:
  TcsTransportConfig() {}

  TcsTransportConfig(int& socket_type,
                  int& priority,
                  int& qos,
                  int& reTransCount,
                  int& failCache)
    : socket_type_(static_cast<TcsSocketType>(socket_type)),
      priority_(static_cast<TcsPriority>(priority)),
      qos_(qos),
      reTransCount_(reTransCount),
      failCache_(failCache) {}

  TcsSocketType get_socket_type();
  TcsPriority get_priority();
  int get_qos();
  int get_reTransCount();
  int get_failCache();

  void set_priority(int value);
  void set_socket_type(int value);
  void set_qos(int value);
  void set_reTransCount(int value);
  void set_failCache(int value);

 private:
  TcsSocketType socket_type_;
  TcsPriority priority_;
  int qos_;
  int reTransCount_;
  int failCache_;
};

} // namespace tcs