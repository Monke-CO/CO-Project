#include "logger/Logger.h"

void Logger::setPriorityLevel(LogPriority priority) {
    getInstance().priority = priority;
}