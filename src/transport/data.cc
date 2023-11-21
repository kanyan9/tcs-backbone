#include "data.h"

namespace tcs {

Data::Data(int& value, int& length, unsigned char* content) {
  data_type_ = static_cast<tcs::DataType>(value);
  length_ = length;
  for(int i = 0; i < length; i++) {
    content_.push_back(content[i]);
  }
}

DataType Data::get_type() {
  return data_type_;
}

std::vector<unsigned char> Data::get_content() {
  return content_;
}

} // namespace tcs