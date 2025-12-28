#include "mavlink_logger.hpp"
#include "fallback_logger.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

MavlinkLogger::MavlinkLogger() : logging(false), fallbackLogger(nullptr) {
    // Initialize logging components 
}

MavlinkLogger::~MavlinkLogger() {
    if (logging) {
        stopLogging();
    }
}

void MavlinkLogger::startLogging() {
    if (logging) {
        std::cerr << "Logging is already started." << std::endl;
        return;
    }
    logging = true;
    // Start the logging process in a separate thread
    loggingThread = std::thread(&MavlinkLogger::logMessages, this);
    if (loggingThread.joinable()) {
        loggingThread.detach();
    }
    std::cout << "Logging started..." << std::endl;
}

void MavlinkLogger::stopLogging() {
    if (!logging) {
        std::cerr << "Logging is not active." << std::endl;
        return;
    }
    logging = false;
    if (loggingThread.joinable()) {
        loggingThread.join();
    }
    std::cout << "Logging stopped." << std::endl;
}

void MavlinkLogger::logMessages() {
    std::ofstream logFile("mavlink_log.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Could not open log file!" << std::endl;
        // Attempt to use fallback if available
        if (fallbackLogger) {
            fallbackLogger->logMessage("Could not open log file!");
        }
        return;
    }

    while (logging) {
        // Simulate receiving MAVLink messages
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::string message = receiveMavlinkMessage();
        if (!message.empty()) {
            logFile << message << std::endl;
        } else if (fallbackLogger) {
            fallbackLogger->logMessage("No MAVLink message received.");
        }
    }

    logFile.close();
}

std::string MavlinkLogger::receiveMavlinkMessage() {
    // Placeholder function to simulate receiving MAVLink messages
    // Implement actual MAVLink message retrieval handling here.
    static int messageCount = 0;
    if (messageCount < 10) {
        return "MAVLink Message: " + std::to_string(messageCount++);
    } else {
        return {}; // Simulate no message
    }
}

void MavlinkLogger::setFallbackLogger(FallbackLogger *fallback) {
    fallbackLogger = fallback;
}

// Ensure that the FallbackLogger logs generic messages
void FallbackLogger::logMessage(const std::string &message) {
    std::ofstream fallbackLogFile("fallback_log.txt", std::ios::app);
    if (!fallbackLogFile.is_open()) {
        std::cerr << "Fallback could not open fallback log file!" << std::endl;
        return;
    }
    fallbackLogFile << message << std::endl;
    fallbackLogFile.close();
}
