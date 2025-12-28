#include "fallback_logger.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>
#include <chrono>
#include <thread>

class FallbackLogger {
private:
    std::ofstream log_file;
    std::mutex log_mutex;
    bool is_logging;
    std::string log_filename;
    std::vector<std::string> message_buffer;

    void logMessage(const std::string& message) {
        std::lock_guard<std::mutex> guard(log_mutex);
        if (!is_logging) {
            std::cerr << "Warning: Attempt to log message but logging is not active." << std::endl;
            return;
        }

        if (!log_file.is_open()) {
            std::cerr << "Error: Log file is closed unexpectedly." << std::endl;
            return;
        }

        log_file << message << std::endl;
        message_buffer.push_back(message);
    }

public:
    FallbackLogger(const std::string& filename) : is_logging(false), log_filename(filename) {}

    void startLogging() {
        if (is_logging) {
            std::cerr << "Warning: Logging is already started." << std::endl;
            return;
        }

        log_file.open(log_filename, std::ios::app);
        if (!log_file.is_open()) {
            std::cerr << "Error: Failed to open log file!" << std::endl;
            return;
        }
        
        is_logging = true;
        std::cout << "Logging started. Writing to " << log_filename << std::endl;
    }

    void stopLogging() {
        if (!is_logging) {
            std::cerr << "Warning: Logging was not started." << std::endl;
            return;
        }

        is_logging = false;
        if (log_file.is_open()) {
            log_file.close();
            std::cout << "Logging stopped. File closed." << std::endl;
        } else {
            std::cerr << "Error: Log file was not open during stop attempt." << std::endl;
        }
    }

    void logMAVLinkMessage(const std::string& message) {
        logMessage(message);
    }

    void summarizeLogs() {
        std::lock_guard<std::mutex> guard(log_mutex);
        std::cout << "Log Summary: Recorded " << message_buffer.size() << " messages." << std::endl;
    }
};

// Sample usage of the FallbackLogger
// Uncomment below for testing purposes
// int main() {
//     FallbackLogger logger("mavlink_fallback.log");
//     logger.startLogging();
//     logger.logMAVLinkMessage("Heartbeat: vehicle_id=1, type=1");
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     logger.logMAVLinkMessage("Status: ready");
//     logger.summarizeLogs();
//     logger.stopLogging();
//     return 0;
// }
