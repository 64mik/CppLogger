# CppLogger

C++ logging library using the Singleton pattern. Supports multiple output destinations.

## Features

- Factory Pattern: Easy creation of writers through LoggerFactory.
- Singleton Pattern: Ensures a single logger instance for flexibility.
- Multiple Outputs: It supports console and file output simultaneously. You can also use both simultaneously.
- Timestamps: Adds timestamps to file logs in [HH:MM:SS] format at file output.
- File Rotation: Automatically creates new log files based on date (YYYY-MM-DD.log format).
- Thread-Safe: Uses mutexes and condition variables for thread safety.
- Asynchronous Logging: Tried to make producer-consumer pattern with a queue and background thread for non-blocking log operations.

## How to use

### Basic Setup
```cpp
//main.cpp
#include "mlog.h"
#include "loggerFactory.h"

int main(){
	// Create writers console (and/or) file
	mik64::Logger::getInstance().setWriters(mik64::LoggerFactory::getWriters({"file","console"}));
	MLOG_INFO << "This is an info message " << 1;
}
```

```cpp
#include "mlog.h"

void example(){
	// Log messages
	MLOG_INFO << "This is an info message " << 1;
	MLOG_WARNING << "This is a" << " warning message";
	MLOG_ERROR << 0.1 << " This is an error message";
}
```

### Macros

- `MLOG_INFO`: Logs at INFO level
- `MLOG_WARNING`: Logs at WARNING level
- `MLOG_ERROR`: Logs at ERROR level
- `MLOG`: It's Alias for LOG_INFO, It will be None LogLevel later

### Log Output Format

- Console: `[LEVEL] line| function(): message`
- File: `[HH:MM:SS] [LEVEL] line| function(): message`

## Architecture

- Main thread enqueues log messages.
- Background thread dequeues and writes to all configured outputs.

## Building

This project uses C++17 and requires a C++ compiler

### Prerequisites

- C++17 compatible compiler
- Windows: MinGW-w64 or MSVC

## Example Output

### Console
```
[INFO] 15| main(): This is an info message 1
[WARN] 16| main(): This is a warning message
[ERR_] 17| main(): 0.1 This is an error message
```

### File
```logs/2026-04-14.log
[18:19:40] [INFO] 24| main(): This is an info message 1
[18:19:40] [WARN] 25| main(): This is a warning message
[18:19:40] [ERR_] 26| main(): 0.1 This is an error message
```

## Performance

- Tested with 100,000 logs in ~425ms (enqueue/dequeue) on Windows 11, Intel i5-10210U

## License

MIT License