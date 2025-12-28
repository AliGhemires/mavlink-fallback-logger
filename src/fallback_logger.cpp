#include "fallback_logger.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>

class FallbackLogger {
private:
    std::string log_file_path;
    std::ofstream log_file;
    bool is_logging;
    std::vector<std::string> log_buffer;
    size_t max_buffer_size;

public:
    FallbackLogger(const std::string& file_path, size_t buffer_size)
        : log_file_path(file_path), is_logging(false), max_buffer_size(buffer_size) {}

    ~FallbackLogger() {
        if (is_logging) {
            stop_logging(); // Ensure to stop logging on destruction
        }
    }

    bool start_logging() {
        if (is_logging) {
            std::cerr << "Logging is already started!" << std::endl;
            return false;
        }
        log_file.open(log_file_path, std::ios::out | std::ios::app);
        if (!log_file.is_open()) {
            std::cerr << "Failed to open log file: " << log_file_path << std::endl;
            return false;
        }
        is_logging = true;
        return true;
    }

    void log_message(const std::string& message) {
        if (!is_logging) {
            std::cerr << "Cannot log message, logging is not started." << std::endl;
            return;
        }
        log_buffer.push_back(message);
        if (log_buffer.size() >= max_buffer_size) {
            flush_log_buffer();
        }
    }

    void stop_logging() {
        if (!is_logging) {
            std::cerr << "Logging is already stopped!" << std::endl;
            return;
        }
        flush_log_buffer();
        if (log_file.is_open()) {
            log_file.close();
        }
        is_logging = false;
    }

    // Improved: Make flush_log_buffer check file open status
    void flush_log_buffer() {
        if (!log_file.is_open()) {
            std::cerr << "Log file is not open. Unable to flush buffer." << std::endl;
            return;
        }
        for (const auto& msg : log_buffer) {
            log_file << time_stamp() << " - " << msg << std::endl; // Timestamp each log entry
        }
        log_buffer.clear();
    }

private:
    std::string time_stamp() const {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        tm local_tm;
        localtime_s(&local_tm, &now_c);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_tm);
        return std::string(buffer);
    }
};

// Example function to simulate fallback logging behavior
void fallback_logging_example() {
    FallbackLogger logger("mavlink_fallback_log.txt", 10);
    if (logger.start_logging()) {
        for (int i = 0; i < 25; ++i) {
            logger.log_message("MAVLink message #: " + std::to_string(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        logger.stop_logging();
    }
}
