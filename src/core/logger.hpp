#pragma once
#include <core/os/os.h>
#include <chrono>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

#define LOG_LEVEL(msg, level) GodumLogger::get_singleton()->log(GodumLogger::level, msg, __FILE__, __LINE__)

#define LOG_SET_LEVEL(level) GodumLogger::get_singleton()->set_min_level(GodumLogger::level)
#define LOG_DEBUG(msg) LOG_LEVEL(msg, LOG_LEVEL_DEBUG)
#define LOG_INFO(msg) LOG_LEVEL(msg, LOG_LEVEL_INFO)
#define LOG_WARNING(msg) LOG_LEVEL(msg, LOG_LEVEL_WARNING)
#define LOG_ERROR(msg) LOG_LEVEL(msg, LOG_LEVEL_ERROR)
#define LOG_FATAL(msg) LOG_LEVEL(msg, LOG_LEVEL_FATAL)

class GodumLogger {
public:
	enum LogLevel {
		LOG_LEVEL_DEBUG = 0,
		LOG_LEVEL_INFO = 1,
		LOG_LEVEL_WARNING = 2,
		LOG_LEVEL_ERROR = 3,
		LOG_LEVEL_FATAL = 4
	};

	void set_min_level(LogLevel level) {
		min_level = level;
	}

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

	void log(LogLevel level, const String &msg, const char *file, int line) {
		if (level < min_level) {
			return;
		}
#ifdef _WIN32
		const char *short_file = strrchr(file, '\\');
#else
		const char *short_file = strrchr(file, '/');
#endif
		short_file = short_file ? short_file + 1 : file;
		String code_pos = vformat("[%s:%d]",
				short_file, line);
		String full_msg = vformat("%s%s%s%s%s\033[0m",
				get_color_code(level),
				get_timestamp(),
				code_pos,
				get_level_prefix(level),
				msg);
		print_line(full_msg);
	}

private:
	LogLevel min_level = LOG_LEVEL_DEBUG;

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
		const char *prefix = "";
		switch (level) {
			case LOG_LEVEL_DEBUG:
				prefix = "[DEBUG]";
				break;
			case LOG_LEVEL_INFO:
				prefix = "[INFO]";
				break;
			case LOG_LEVEL_WARNING:
				prefix = "[WARN]";
				break;
			case LOG_LEVEL_ERROR:
				prefix = "[ERROR]";
				break;
			case LOG_LEVEL_FATAL:
				prefix = "[FATAL]";
				break;
		}
		return prefix;
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
		ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
		   << "." << std::setfill('0') << std::setw(3) << ms.count();

		return String(ss.str().c_str());
	}
};