#pragma once

#include <string>
#include <cstring>
#include <exception>

namespace tcs {
class TcsException :public std::exception {
  public:
    TcsException(const std::string& msg) : msg_(msg) {}

    const char* what() const noexcept override { return msg_.c_str(); }

    std::string msg_;
};

} // namespace tcs
