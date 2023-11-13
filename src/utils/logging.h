#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

namespace tcs {
// This dumps the current stack trace information
class StackTrace {
  friend std::ostream& operator<<(std::ostream& os,
                                  const StackTrace& stack_trace);
};

enum class TcsLogLevel {
  INFO = 0,
  WARNING = 1,
  ERROR = 2,
  FATAL = 3
};

#define TCS_LOG_INTERNAL(level) \
  ::tcs::TcsLog(__FILE__, __LINE__, level)

#define TCS_LOG_ENABLED(level) \
  tcs::TcsLog::IsLevelEnabled(tcs::TcsLogLevel::level)

#define TCS_LOG(level)                                      \
  if (tcs::TcsLog::IsLevelEnabled(tcs::TcsLogLevel::level)) \
  TCS_LOG_INTERNAL(tcs::TcsLogLevel::level)

#define TCS_IGNORE_EXPR(expr) ((void)(expr))

#define TCS_CHECK(condition)                                                          \
  (condition)                                                                         \
      ? TCS_IGNORE_EXPR(0)                                                            \
      : ::tcs::Voidify() & ::tcs::TcsLog(__FILE__, __LINE__, tcs::TcsLogLevel::FATAL) \
                               << " Check failed: " #condition " "

#ifdef NDEBUG

#define TCS_DCHECK(condition)                                                         \
  (condition)                                                                         \
      ? TCS_IGNORE_EXPR(0)                                                            \
      : ::tcs::Voidify() & ::tcs::TcsLog(__FILE__, __LINE__, tcs::TcsLogLevel::ERROR) \
                               << " Debug check failed: " #condition " "
#else

#define TCS_DCHECK(condition) TCS_CHECK(condition)

#endif  // NDEBUG

#define TCS_CHECK_OP(left, op, right)        \
  if (const auto& _left_ = (left); true)     \
    if (const auto& _right_ = (right); true) \
  TCS_CHECK((_left_ op _right_)) << " " << _left_ << " vs " << _right_

#define TCS_CHECK_EQ(left, right) TCS_CHECK_OP(left, ==, right)
#define TCS_CHECK_NE(left, right) TCS_CHECK_OP(left, !=, right)
#define TCS_CHECK_LE(left, right) TCS_CHECK_OP(left, <=, right)
#define TCS_CHECK_LT(left, right) TCS_CHECK_OP(left, <, right)
#define TCS_CHECK_GE(left, right) TCS_CHECK_OP(left, >=, right)
#define TCS_CHECK_GT(left, right) TCS_CHECK_OP(left, >, right)


class TcsLogBase {
 public:
  virtual ~TcsLogBase() {}

  virtual bool IsEnabled() const { return false; }

  virtual bool IsFatal() const { return false; }

  template <typename T>
  TcsLogBase& operator<<(const T& t) {
    if (IsEnabled()) {
      Stream() << t;
    }
    if (IsFatal()) {
      ExposeStream() << t;
    }
    return *this;
  }
 protected:
  virtual std::ostream& Stream() { return std::cerr; }
  virtual std::ostream& ExposeStream() { return std::cerr; }
};

class TcsLog : public TcsLogBase {
 public:
  TcsLog(const char* file_name, int line_number, TcsLogLevel severity);
  
  virtual ~TcsLog();

  virtual bool IsEnabled() const;

  virtual bool IsFatal() const;

  static bool IsLevelEnabled(TcsLogLevel log_level_);

  static std::string GetLogFormatPattern();

  static std::string GetLoggerName();

 private:
  void* logging_provider_;

  bool is_enabled_;

  TcsLogLevel severity_;

  bool is_fatal_ = false;

  std::shared_ptr<std::ostringstream> expose_osstream_ = nullptr;

  // The directory where the log files are stored.
  // if this is empty, logs are printed to stdout.
  static std::string log_dir_;

  static TcsLogLevel severity_threshold_;

  static std::string log_format_pattern_;

  static long log_rotation_max_size_;

  static long log_rotation_file_num_;

  static std::string logger_name_;

 protected:
  virtual std::ostream& Stream();
  virtual std::ostream& ExposeStream();
};

// This class make TCS_CHECK compilation pass to change the << operator to void.
class Voidify {
 public:
  Voidify() {}
  // This has to be an operator with a precedence lower than << but
  // higher than ?:
  void operator&(TcsLogBase &) {}
};

} // tcs
