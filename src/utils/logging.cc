#include <execinfo.h>

#include "absl/debugging/stacktrace.h"
#include "absl/debugging/symbolize.h"
#include "logging.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace tcs {

TcsLogLevel TcsLog::severity_threshold_ = TcsLogLevel::INFO;
std::string TcsLog::log_dir_ = "";
std::string TcsLog::log_format_pattern_ = "[%Y-%m-%d %H:%M:%S,%e %L %P %t] %v";
std::string TcsLog::logger_name_ = "tcs_log_slink";
long TcsLog::log_rotation_max_size_ = 1 << 29;
long TcsLog::log_rotation_file_num_ = 10;

std::ostream& operator<<(std::ostream& os, const StackTrace& stack_trace) {
  static constexpr int MAX_NUM_FRAMES = 64;
  char buf[16 * 1024];
  void* frames[MAX_NUM_FRAMES];

  const int num_frames = backtrace(frames, MAX_NUM_FRAMES);
  char** frame_symbols = backtrace_symbols(frames, num_frames);
  for (int i = 0; i < num_frames; ++i) {
    os << frame_symbols[i];

    if (absl::Symbolize(frames[i], buf, sizeof(buf))) {
      os << " " << buf;
    }

    os << "\n";
  }
  free(frame_symbols);

  return os;
}

class DefaultStdErrLogger final {
 public:
  std::shared_ptr<spdlog::logger> GetDefaultLogger() {
    return default_stderr_logger_;
  }

  static DefaultStdErrLogger &Instance() {
    static DefaultStdErrLogger instance;
    return instance;
  }

 private:
  DefaultStdErrLogger() {
    default_stderr_logger_ = spdlog::stderr_color_mt("stderr");
    default_stderr_logger_->set_pattern(TcsLog::GetLogFormatPattern());
  }
  // default destructor
  ~DefaultStdErrLogger() = default;
  // disable copy construct
  DefaultStdErrLogger(DefaultStdErrLogger const &) = delete;
  // disable move construct
  DefaultStdErrLogger(DefaultStdErrLogger &&) = delete;

  std::shared_ptr<spdlog::logger> default_stderr_logger_;
};

class SpdLogMessage final {
 public:
  explicit SpdLogMessage(const char* file,
                        int line,
                        int loglevel,
                        std::shared_ptr<std::ostringstream> expose_osstream)
      : loglevel_(loglevel), expose_osstream_(expose_osstream) {
    stream() << file << ":" << line << ": ";
  }

  inline void Flush() {
    auto logger = spdlog::get(TcsLog::GetLoggerName());
    if (!logger) {
      logger = DefaultStdErrLogger::Instance().GetDefaultLogger();
    }

    if (loglevel_ == static_cast<int>(spdlog::level::critical)) {
      stream() << "\n*** StackTrace Information ***\n" << tcs::StackTrace();
    }

    if (expose_osstream_) {
      *expose_osstream_ << "\n*** StackTrace Information ***\n"
                        << tcs::StackTrace();
    }

    logger->log(
        static_cast<spdlog::level::level_enum>(loglevel_), "{}", str_.str());

    logger->flush();
  }

  ~SpdLogMessage() { Flush(); }
  
  inline std::ostream& stream() { return str_; }

 private:
  SpdLogMessage(const SpdLogMessage& ) = delete;
  SpdLogMessage& operator=(const SpdLogMessage&) = delete;

  std::ostringstream str_;
  int loglevel_;
  std::shared_ptr<std::ostringstream> expose_osstream_;
};

typedef tcs::SpdLogMessage LoggingProvider;

// Spdlog's severity map.
static int GetMappedSeverity(TcsLogLevel severity) {
  switch (severity) {
  case TcsLogLevel::INFO:
    return spdlog::level::info;
  case TcsLogLevel::WARNING:
    return spdlog::level::warn;
  case TcsLogLevel::ERROR:
    return spdlog::level::err;
  case TcsLogLevel::FATAL:
    return spdlog::level::critical;
  default:
    TCS_LOG(FATAL) << "Unsupported logging level: " << static_cast<int>(severity);
    // This return won't be hit but compiler needs it.
    return spdlog::level::off;
  }  
}

bool TcsLog::IsLevelEnabled(TcsLogLevel log_level) {
  return log_level >= severity_threshold_;
}

std::string TcsLog::GetLogFormatPattern() { return log_format_pattern_; }

std::string TcsLog::GetLoggerName() { return logger_name_; }

TcsLog::TcsLog(const char* file_name, int line_number, TcsLogLevel severity) 
    : logging_provider_(nullptr),
      is_enabled_(severity >= severity_threshold_),
      severity_(severity),
      is_fatal_(severity == TcsLogLevel::FATAL) {
  if (is_fatal_) {
    expose_osstream_ = std::make_shared<std::ostringstream>();
    *expose_osstream_ << file_name << ":" << line_number << ":";
  }
  if (is_enabled_) {
    logging_provider_ = new LoggingProvider(
        file_name, line_number, GetMappedSeverity(severity), expose_osstream_);
  }
}

std::ostream& TcsLog::Stream() {
  auto logging_provider = reinterpret_cast<LoggingProvider*>(logging_provider_);
  return logging_provider->stream();
}

bool TcsLog::IsEnabled() const { return is_enabled_; }

bool TcsLog::IsFatal() const { return is_fatal_; }

std::ostream& TcsLog::ExposeStream() { return *expose_osstream_; }

TcsLog::~TcsLog() {
  if (logging_provider_ != nullptr) {
    delete reinterpret_cast<LoggingProvider*>(logging_provider_);
    logging_provider_ = nullptr;
  }
  if (severity_ == TcsLogLevel::FATAL) {
    std::_Exit(EXIT_FAILURE);
  }
}

} // namespace tcs