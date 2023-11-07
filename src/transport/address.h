#pragma once

#include <string>
#include <vector>

namespace tcs {

enum AddressType {
  UNICAST_IP = 1,
  MULTICAST_IPS = 2,
  MULTICAST_GROUP_IP = 3,
  BROADCAST_SUB = 4,
  BROADCAST_ALL = 5
};

const int NUM_TYPE = 5;

class TcsAddress {
 public:
  TcsAddress(int& value, std::vector<std::string>& ip_list, int& port);
  
  // void set_type(int value);
  // void set_ip(std::vector<std::string>& iplist);
  // void set_port(int port);
  AddressType get_type();
  std::vector<std::string> get_address();

 private:
  AddressType type_;
  std::vector<std::string> address_;
  
};

} // tcs

