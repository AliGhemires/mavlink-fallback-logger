# Mavlink Fallback Logger

## Overview
The Mavlink Fallback Logger is designed to provide reliable logging of MAVLink messages in situations where the primary RSS (Real-time Streaming Source) is unavailable. By implementing a fallback logging system, this project enhances the resilience and robustness of unmanned vehicle operations, enabling continuous data capture and maintaining the integrity of mission-critical information.

## Background
As unmanned vehicle systems increasingly rely on MAVLink for communication and data exchange, ensuring data logging remains functional even in adverse scenarios is crucial. This project addresses the need for a fallback mechanism that activates during RSS outages, aiding swift recovery and ensuring data continuity.

## What it does
The Mavlink Fallback Logger captures MAVLink messages from alternative sources when the primary RSS is disconnected. It implements real-time diagnostics, configurable settings, and log summarization capabilities, making it a key tool for UAV operations.

## Repo layout
```plaintext
- CMakeLists.txt
- README.md
- include/
 - fallback_logger.hpp
 - mavlink_logger.hpp
- src/
 - fallback_logger.cpp
 - mavlink_logger.cpp
- tests/
 - test_mavlink_logger.cpp
```

## How it works
The core functionality revolves around a fallback logging mechanism that activates when the primary RSS feed fails. The main components include the logging modules defined in C++, structured using CMake for build management. Upon CLI command initiation, the logger captures MAVLink messages and saves them to log files. The system also offers real-time feedback on logging status and diagnostics to ensure data integrity.

## Install
1. Clone the repository:
 ```bash
 git clone https://your-repository-url
 cd your-repository-directory
 ```
2. Ensure you have CMake installed.
3. Build the project:
 ```bash
 mkdir build && cd build
 cmake ..
 make
 ```

## Quickstart
After building the project, use the command line interface to run the logger:

```bash
./mavlink_logger --start_logging
```

## Usage
- **Start Logging:**
 ```bash
 ./mavlink_logger --start_logging
 ```
- **Stop Logging:**
 ```bash
 ./mavlink_logger --stop_logging
 ```
- **Check Status:**
 ```bash
 ./mavlink_logger --status
 ```

## Outputs
The logger generates a log file containing all captured MAVLink messages, preserving their timestamps and types. The output format can be adjusted through the logger's configuration settings.

### Example output
```plaintext
2023-10-07 14:30:01 - MAVLink Message: HEARTBEAT, Type: 6
2023-10-07 14:30:02 - MAVLink Message: PARAM_VALUE, Param ID: SYSID_THISMAV, Value: 1
2023-10-07 14:30:03 - MAVLink Message: ATTITUDE, Roll: 0.5, Pitch: 0.1, Yaw: 3.14
```

## Limitations
- The logger relies on MAVLink protocol compliance; improper message formatting may lead to data capture issues.
- In RSS outages, the fallback mechanism may not capture every message if alternative signals are unavailable.

## Next steps
Future improvements may include:
- Enhancing filtering capabilities for logs based on user-configured thresholds.
- Incorporating advanced data recovery algorithms for integrity verification post-logging.

## Testing
The project includes a test suite to ensure functionality, encompassing:

- **Unit tests** for individual modules.
- **Integration tests** for the fallback system.
- **Performance tests** under varying conditions.

To run the tests, execute:
```bash
cd tests/
./run_tests.sh
```

## Inspired by: Fallback: RSS unavailable
This project draws inspiration from the research paper "Fallback: RSS unavailable," highlighting techniques to ensure data integrity and continued functionality in unmanned vehicle operations.
