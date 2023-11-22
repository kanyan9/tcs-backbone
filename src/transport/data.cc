#include "data.h"

namespace tcs {

TcsData::TcsData(int& value, int& length, std::string& content) {
  data_type_ = static_cast<tcs::TcsDataType>(value);
  length_ = length;
  content_ = content;
}

TcsDataType TcsData::get_type() {
  return data_type_;
}

int TcsData::get_len() {
  return length_;
}

std::string TcsData::get_content() {
  return content_;
}

} // namespace tcs