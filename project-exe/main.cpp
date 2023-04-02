#include "logger/Logger.h"

int main() {
    Logger::setPriorityLevel(INFO);

    Logger::Info(IMPLICIT, "This is the", 1, "st logger test");

    return 0;
}