#include "../utils/logging.h"
#include "address.h"

namespace tcs {

Address::Address(int& value, 
                       std::vector<std::string>& ip_list,
                       int& port) {
  if (value < 1 || value > NUM_TYPE) {
    TCS_LOG(ERROR) << "transport ip address error! value is 1 ~ 5"; 
    return;
  }

  this->type_ = static_cast<AddressType>(value);

  for (auto ip : ip_list) {
    this->address_.push_back(ip + std::to_string(port));
  }
}

AddressType Address::get_type() {
  return this->type_;
}

std::vector<std::string> Address::get_address() {
  return this->address_;
}

} // namespace tcs
