#pragma once

#include <vector>

namespace tcs {

enum class DataType {
  // add data type to meet business transmission data requirement
  FOE = 1,
  MISSIONPACKAGE = 2
};

class Data {
 public:
  Data(int& value, int& length, unsigned char* content);

  DataType get_type();

  std::vector<unsigned char> get_content();

 private:
  DataType data_type_;
  int length_;
  std::vector<unsigned char> content_;
};

} // namespace tcs