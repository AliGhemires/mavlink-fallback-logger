#ifndef MAVLINK_LOGGER_HPP
#define MAVLINK_LOGGER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "fallback_logger.hpp"

class MavlinkLogger {
public:
    MavlinkLogger(const std::string& logFile);
    ~MavlinkLogger();

    void startLogging();
    void stopLogging();
    void logMessage(const std::string& message);
    void checkStatus();

private:
    std::ofstream logStream;
    bool isLogging{false};  // Initialize member variables
    std::string logFileName;
    FallbackLogger fallbackLogger;

    void initializeLogFile();
    void closeLogFile();
    void handleLogFileError(const std::string &errorMsg); // New method for error handling
};

// Updates in source files would correspondingly add error handling using handleLogFileError
// Example in source:
// void MavlinkLogger::startLogging() {
//    ...
//    if (!logStream.is_open()) {
//        handleLogFileError("Error: Unable to open log file!");
//        return;
//    }
//    ...
// }

#endif // MAVLINK_LOGGER_HPP
