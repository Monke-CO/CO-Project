#pragma once

#include <mutex>
#include <source_location>
#include <iostream>

/**
 * Enum used for setting up the logging module.
 * The higher the value the more important the log is.
 */
enum LogPriority {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR,
    CRITICAL
};

enum LogType {
    EXPLICIT,
    IMPLICIT
};

/**
 * String constant used for converting the enum int value to a string. The strings inside this constant
 * should be in the same order as the LogPriority Enum.
 */
static const char *LogPriorityString[] = {
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR",
        "CRITICAL"
};

class Logger {
private:
    LogPriority priority = INFO;
    std::mutex log_mutex;

    Logger() = default;

    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }

    static const char* enumString(LogPriority priority) {
        return LogPriorityString[priority];
    }

    template <typename ...Args>
    void log(LogType start, std::source_location location, LogPriority logPriority, Args ...args) {
        if (logPriority >= this->priority) {
            std::cout << "[" << enumString(logPriority) << "] ";
            std::scoped_lock lock(log_mutex);
            if (start == EXPLICIT) {
                std::cout << "[File: " << location.file_name()
                          << ": line " << location.line() << " in function "
                          << location.function_name() << "] ";
            }
            ((std::cout << std::forward<Args>(args) << " "), ...);
            std::cout << std::endl;
        }
    }

public:
    Logger(const Logger&) = delete;
    Logger& operator= (const Logger&) = delete;

    /**
     * Sets the priority level for all logs. Only logs with a
     * <b>greater or equal</b> priority will be printed.
     * The default value is INFO
     */
    static void setPriorityLevel(LogPriority priority);

    template <typename LogType, typename...Args>
    struct Debug
    {
        explicit Debug(LogType logType,
                       Args... args,
                       const std::source_location& location = std::source_location::current())
        {
            getInstance().log(logType, location, DEBUG, args...);
        }
    };

    template <typename LogType, typename... Args>
    Debug(LogType logType, Args...args) -> Debug<LogType, Args...>;

    template <typename LogType, typename...Args>
    struct Info
    {
        explicit Info(LogType logType,
                      Args... args,
                      const std::source_location& location = std::source_location::current())
        {
            getInstance().log(logType, location, INFO, args...);
        }
    };

    template <typename LogType, typename... Args>
    Info(LogType logType, Args...args) -> Info<LogType, Args...>;

    template <typename LogType, typename...Args>
    struct Warn
    {
        explicit Warn(LogType logType,
                      Args... args,
                      const std::source_location& location = std::source_location::current())
        {
            getInstance().log(logType, location, WARN, args...);
        }
    };

    template <typename LogType, typename... Args>
    Warn(LogType logType, Args...args) -> Warn<LogType, Args...>;


    template <typename LogType, typename...Args>
    struct Error
    {
        explicit Error(LogType logType,
                      Args... args,
                      const std::source_location& location = std::source_location::current())
        {
            getInstance().log(logType, location, ERROR, args...);
        }
    };

    template <typename LogType, typename... Args>
    Error(LogType logType, Args...args) -> Error<LogType, Args...>;


    template <typename LogType, typename...Args>
    struct Critical
    {
        explicit Critical(LogType logType,
                       Args... args,
                       const std::source_location& location = std::source_location::current())
        {
            getInstance().log(logType, location, CRITICAL, args...);
        }
    };

    template <typename LogType, typename... Args>
    Critical(LogType logType, Args...args) -> Critical<LogType, Args...>;
};