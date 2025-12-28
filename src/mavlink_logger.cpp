#include "mavlink_logger.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

MavlinkLogger::MavlinkLogger(const std::string &logFile)
    : logFile(logFile), logging(false) {}

void MavlinkLogger::startLogging() {
    if (logging) {
        std::cerr << "Warning: Logging is already started." << std::endl;
        return;
    }
    logStream.open(logFile, std::ios::out | std::ios::app);
    if (!logStream.is_open()) {
        std::cerr << "Error: Unable to open log file!" << std::endl;
        return;
    }
    logging = true;
    std::cout << "Logging started..." << std::endl;
}

void MavlinkLogger::stopLogging() {
    if (!logging) {
        std::cerr << "Warning: Logging was not started." << std::endl;
        return;
    }
    logging = false;
    if (logStream.is_open()) {
        logStream.close();
        std::cout << "Logging stopped." << std::endl;
    } else {
        std::cerr << "Error: Log file was not open!" << std::endl;
    }
}

void MavlinkLogger::logMessage(const mavlink_message_t &message) {
    if (!logging) {
        std::cerr << "Warning: Attempt to log message but logging is not active." << std::endl;
        return;
    }
    if (!logStream.is_open()) {
        std::cerr << "Error: Log stream is not open." << std::endl;
        return;
    }
    // Serialize MAVLink message to string
    char buffer[MAVLINK_MSG_BUFFER_LENGTH];
    int len = mavlink_msg_to_send_buffer(buffer, &message);
    logStream.write(buffer, len);
    if (!logStream) {
        std::cerr << "Error: Failed to write to log file." << std::endl;
    }
    logStream.flush(); // Ensure immediate writing
}

bool MavlinkLogger::isLogging() const {
    return logging;
}
