#pragma once

#include <string>

namespace tcs {

enum class TcsDataType {
  // add data type to meet business transmission data requirement
  FOE = 1,
  MISSIONPACKAGE = 2
};

class TcsData {
 public:
  TcsData(int& value, int& length, std::string& content);

  TcsDataType get_type();

  std::string get_content();

  int get_len();

 private:
  TcsDataType data_type_;
  int length_;
  std::string content_;
};

} // namespace tcs