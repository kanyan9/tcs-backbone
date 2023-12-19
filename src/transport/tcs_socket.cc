#include "tcs_socket.h"
#include "../utils/logging.h"

#include <iostream>

#include <handy/handy.h>
#include <handy/conn.h>

namespace tcs {

std::string TcsSocket::server_ip_ = "127.0.0.1";
int TcsSocket::server_port_ = 37011;
int TcsSocket::max_frame_length_ = 1024 * 1024 * 32;
int TcsSocket::reconnect_interval_ = 2000;
std::string TcsSocket::app_id = "test";

class HandyConnect final {
 public:
  explicit HandyConnect(std::string& server_ip,
                        int& server_port,
                        int& reconnect_interval)
    : ip_(server_ip), port_(server_port),
      reconnect_interval_(reconnect_interval) {}

  void connect() {
    conn_ = handy::TcpConn::createConnection(&base_, ip_, port_);

    conn_->setReconnectInterval(reconnect_interval_);
  }

  void send(const char* message) {
    std::cout << "handy send message" << std::endl;

    conn_->send(message);

    std::cout << "send message success" << std::endl;

    base_.loop();
  }

  void send(TcsPacket* packet) {
    TCS_LOG(INFO) << "send message";
    std::string proto_message;
    serialize(packet, proto_message);
    TCS_LOG(INFO) << "protobuf message: " << proto_message;
    
    char flag[1] = { 0x25 };
    char* len = const_cast<char*>(std::to_string(proto_message.size()).c_str());
    char* content = const_cast<char*>(proto_message.c_str());

    auto proto_packet_length = 1 + strlen(len) + strlen(content);
    char proto_packet[proto_packet_length];

    strcat(proto_packet, flag);
    strcat(proto_packet, len);
    strcat(proto_packet, content);

    std::printf("packet protobuf content: %s\n", proto_packet);

    send(proto_packet);
  }

  void receive(TcsPacket& packet) {
    conn_->onRead([&](const handy::TcpConnPtr& con) {
      handy::Buffer& buf = con->getInput();
      char* recv_c = buf.data();
      int c_len = buf.size();
      TCS_LOG(INFO) << "receive message: " << recv_c;
      TCS_LOG(INFO) << "receive message length: " << c_len;
      char recv_message[c_len - 5];
      memcpy(recv_message, recv_c + 5, c_len - 5);
      std::string message(recv_message);

      TCS_LOG(INFO) << message;

      deserialize(packet, message);
    });
  }

  void close() {
    conn_->close();
  }

  ~HandyConnect() {
    close();
  }

private:
  std::string ip_;
  int port_;
  int reconnect_interval_;
  handy::EventBase base_;
  handy::TcpConnPtr conn_;
};

typedef HandyConnect ConnectProvider;

TcsSocket::TcsSocket() {
  connect_provider_ = nullptr;
  connect_provider_ = new ConnectProvider(server_ip_, server_port_,
                                          reconnect_interval_);
}

void TcsSocket::connect() {
  auto connect_provider = reinterpret_cast<ConnectProvider*>(connect_provider_);
  connect_provider->connect();
}

void TcsSocket::send(const char* message) {
  auto connect_provider = reinterpret_cast<ConnectProvider*>(connect_provider_);
  connect_provider->send(message);
}

// void TcsSocket::send(std::string message) {
//   auto connect_provider = reinterpret_cast<ConnectProvider*>(connect_provider_);
//   connect_provider->send(message);  
// }

void TcsSocket::send(TcsPacket* packet) {
  auto connect_provider = reinterpret_cast<ConnectProvider*>(connect_provider_);
  connect_provider->send(packet);
}

// void TcsSocket::receive(TcsPacket& packet) {
//   auto connect_provider = reinterpret_cast<ConnectProvider*>(connect_provider_);
//   connect_provider->receive(packet);
// }

TcsSocket::~TcsSocket() {
  if (connect_provider_ != nullptr) {
    delete reinterpret_cast<ConnectProvider*>(connect_provider_);
    connect_provider_ = nullptr;
  } 
}

} // namespace tcs
