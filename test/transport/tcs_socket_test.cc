#include <iostream>
#include <string>

#include "../../src/transport/tcs_socket.h"
#include "../../src/utils/logging.h"

#include "gtest/gtest.h"

namespace tcs {

TEST(test_tcs_socket, connection) {
  TcsSocket* sock = new TcsSocket();

  sock->connect();
  std::string msg = "connection success";
  sock->send(msg);
  TCS_LOG(INFO) << "success to send message";
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  return 0;
}

} // namespace tcs