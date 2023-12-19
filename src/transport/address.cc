#include "../utils/logging.h"
#include "address.h"

namespace tcs {

TcsAddress::TcsAddress(int& value, 
                       std::string& ip,
                       int& port) {
  if (value < 1 || value > NUM_TYPE) {
    TCS_LOG(ERROR) << "transport ip type error! value is 1 ~ 5"; 
    return;
  }

  this->type_ = static_cast<TcsAddressType>(value);
  this->address_ = ip + ":" + std::to_string(port);
}

void TcsAddress::set_type(int value) {
  this->type_ = static_cast<TcsAddressType>(value);
}

void TcsAddress::set_address(std::string address) {
  this->address_ = address;
}

TcsAddressType TcsAddress::get_type() {
  return this->type_;
}

std::string TcsAddress::get_address() {
  return this->address_;
}

} // namespace tcs
