#pragma once
#include <chrono>
#include <core/os/os.h>
#include <core/string/ustring.h>
#include <iomanip>
#include <sstream>
#include <stdarg.h>

#ifdef _WIN32
#include <windows.h>
#endif

// 支持格式化字符串的日志宏
#define LOG_SET_LEVEL(level)                                                   \
  GodumLogger::get_singleton()->set_min_level(GodumLogger::level)
#define LOG_DEBUG(format, ...)                                                 \
  GodumLogger::get_singleton()->log(GodumLogger::LOG_LEVEL_DEBUG, format,      \
                                    __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_INFO(format, ...)                                                  \
  GodumLogger::get_singleton()->log(GodumLogger::LOG_LEVEL_INFO, format,       \
                                    __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_WARNING(format, ...)                                               \
  GodumLogger::get_singleton()->log(GodumLogger::LOG_LEVEL_WARNING, format,    \
                                    __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(format, ...)                                                 \
  GodumLogger::get_singleton()->log(GodumLogger::LOG_LEVEL_ERROR, format,      \
                                    __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_FATAL(format, ...)                                                 \
  GodumLogger::get_singleton()->log(GodumLogger::LOG_LEVEL_FATAL, format,      \
                                    __FILE__, __LINE__, ##__VA_ARGS__)

class GodumLogger {
public:
  enum LogLevel {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_ERROR = 3,
    LOG_LEVEL_FATAL = 4
  };

  void set_min_level(LogLevel level) { min_level = level; }

  static GodumLogger *get_singleton() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
    static GodumLogger instance;
    return &instance;
  }

  template <typename... Args>
  void log(LogLevel level, const char *format, const char *file, int line,
           Args... args) {
    if (level < min_level) {
      return;
    }

    String formatted_msg = vformat(format, args...);
    _log_internal(level, formatted_msg, file, line);
  }

  void log(LogLevel level, const String &msg, const char *file, int line) {
    if (level < min_level) {
      return;
    }
    _log_internal(level, msg, file, line);
  }

private:
  LogLevel min_level = LOG_LEVEL_DEBUG;

  void _log_internal(LogLevel level, const String &msg, const char *file,
                     int line) {
#ifdef _WIN32
    const char *short_file = strrchr(file, '\\');
#else
    const char *short_file = strrchr(file, '/');
#endif
    short_file = short_file ? short_file + 1 : file;

    String code_pos = vformat("[%s:%d]", short_file, line);
    String full_msg =
        vformat("%s%s%s%s%s\033[0m", get_color_code(level), get_timestamp(),
                code_pos, get_level_prefix(level), msg);
    print_line(full_msg);
  }

  const char *get_color_code(LogLevel level) {
    switch (level) {
    case LOG_LEVEL_DEBUG:
      return "\033[36m"; // Cyan
    case LOG_LEVEL_INFO:
      return "\033[32m"; // Green
    case LOG_LEVEL_WARNING:
      return "\033[33m"; // Yellow
    case LOG_LEVEL_ERROR:
      return "\033[31m"; // Red
    case LOG_LEVEL_FATAL:
      return "\033[35m"; // Magenta
    default:
      return "\033[0m";
    }
  }

  const char *get_level_prefix(LogLevel level) {
    switch (level) {
    case LOG_LEVEL_DEBUG:
      return "[DEBUG]";
    case LOG_LEVEL_INFO:
      return "[INFO]";
    case LOG_LEVEL_WARNING:
      return "[WARN]";
    case LOG_LEVEL_ERROR:
      return "[ERROR]";
    case LOG_LEVEL_FATAL:
      return "[FATAL]";
    default:
      return "[UNKNOWN]";
    }
  }

  String get_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) %
              1000;

    std::time_t t = std::chrono::system_clock::to_time_t(now);
#ifdef _WIN32
    std::tm tm;
    localtime_s(&tm, &t);
#else
    std::tm tm = *std::localtime(&t);
#endif

    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "." << std::setfill('0')
       << std::setw(3) << ms.count();

    return String(ss.str().c_str());
  }
};
