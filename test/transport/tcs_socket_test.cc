#include <iostream>
#include <string>

#include "../../src/transport/tcs_socket.h"
#include "../../src/utils/logging.h"

#include "gtest/gtest.h"

namespace tcs {

TEST(test_tcs_socket, send) {

  // unsigned char message[11] = "helloworld";
  // unsigned char message[6] = {0x25, 0x00, 0x00, 0x00, 0x01, 'a'};
  // message[0] = 0x25;
  // message[1] = 0x0;
  // message[2] = 0x0;
  // message[3] = 0x0;
  // message[4] = 0x01;

  // message[5] = 'a';
  // std::string message("hello world");
  // unsigned char flag = 0x25;
  // std::string len = std::to_string(message.length());

  // message = std::to_string(flag) + len + message;

  // const char* msg = reinterpret_cast<const char*>(message);
  // std::string msg = "";
  // for (int i = 0; i < 6; i++) {
  //   msg += message[i];
  // }
  // std::cout << msg << "\n";
  // sock->send(msg);

  TcsSocket* sock = new TcsSocket();
  std::string ip("127.0.0.1");
  int addr_type = 1;
  int port = 8282;
  TcsAddress* addr = new TcsAddress(addr_type, ip, port);

  int data_type = 1;
  std::string content("Hi! It's first message. God bless you!");
  int data_len = content.length();
  TcsData* data = new TcsData(data_type, data_len, content);

  int sock_t =1;
  int prior = 1;
  int qos = 1;
  int rc = 1;
  int fc = 1;
  TcsTransportConfig* config = new TcsTransportConfig(sock_t, prior, qos, rc, fc);

  int pack_t = 1;
  std::string num("1");
  TcsPacket* packet = new TcsPacket(pack_t, *addr, num, *data, *config);

  sock->connect();
  // sock->send(*packet);
  TCS_LOG(INFO) << "done";

  sock->send(packet);
}

} // namespace tcs

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  return 0;
}
