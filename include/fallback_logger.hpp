#ifndef FALLBACK_LOGGER_HPP
#define FALLBACK_LOGGER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>  // added for file handling
#include "mavlink_logger.hpp"

class FallbackLogger {
public:
    // Constructor initializes the fallback logger.
    FallbackLogger(const std::string& filename);

    // Starts the logging process.
    void startLogging();

    // Stops the logging process.
    void stopLogging();

    // Logs a MAVLink message to the fallback storage.
    void logMessage(const mavlink_message_t& message);

    // Retrieve the logged messages.
    const std::vector<std::string>& getLoggedMessages() const;

private:
    bool isLogging;  // Indicates whether the logger is actively logging messages.
    std::string logFilename;  // Filename for logging. Added for file management
    std::ofstream logFileStream;  // File stream to write logs
    std::vector<std::string> messageLog;  // Container for logged messages.
    
    // Safely opens a log file, handling errors if it fails.
    bool openLogFile();

    // Handles the write operation when a message is logged.
    void writeLog(const std::string& message);

    // Safely closes the log file.
    void closeLogFile();
};

#endif // FALLBACK_LOGGER_HPP
