#include "address.h"

namespace tcs {

TcsAddress::TcsAddress(int& value, 
                       std::vector<std::string>& ip_list,
                       int& port) {
  if (value < 1 || value > NUM_TYPE) {
    // TODO: output error log!
    return;
  }

  this->type_ = static_cast<AddressType>(value);

  for (auto ip : ip_list) {
    this->address_.push_back(ip + std::to_string(port));
  }
}

AddressType TcsAddress::get_type() {
  return this->type_;
}

std::vector<std::string> TcsAddress::get_address() {
  return this->address_;
}

} // namespace tcs