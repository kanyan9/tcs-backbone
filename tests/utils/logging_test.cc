#include <iostream>
#include "../../src/utils/logging.h"

#include "gtest/gtest.h"

namespace tcs {

void PrintLog() {
  TCS_LOG(INFO) << "This is the"
                << " INFO message";
  TCS_LOG(WARNING) << "This is the"
                   << " WARNING message";
  TCS_LOG(ERROR) << "This is the"
                 << " ERROR message";
  TCS_CHECK(true) << "This is a TCS_CHECK"
                  << " message but it won't show up";
}

TEST(LogTest, PrintLogTest) {
  PrintLog();
}

} // namspace tcs

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}