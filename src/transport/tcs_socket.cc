#include "tcs_socket.h"
#include "../utils/logging.h"

namespace tcs {

unsigned char TcsSocket::protocol_flag_ = 0x25;
std::string TcsSocket::server_ip_ = "127.0.0.1";
int TcsSocket::server_port_ = 37011;
int TcsSocket::max_frame_length_ = 1024 * 1024 * 32;
std::string TcsSocket::app_id = "test";

void TcsSocket::connect() {
  handy::EventBase base;
  conn_ = handy::TcpConn::createConnection(&base, server_ip_, server_port_);
  
  if (conn_->getState() == handy::TcpConn::State::Handshaking) {
    TCS_LOG(INFO) << "local tcp connect success!";
  } else {
    conn_->setReconnectInterval(200);
  }

  base.loop();
}

void TcsSocket::send(std::string message) {
  std::string pf = std::to_string(protocol_flag_);
  std::string msg = pf + message;
  // TODO(kan):: add send state
  conn_->send(msg);

  return;
}

void TcsSocket::close() {
  conn_->close();
}

TcsSocket::~LocalSocket() {
  if (conn_->getState() != handy::TcpConn::State::Closed) {
    this->close();
  }
}

} // namespace tcs
