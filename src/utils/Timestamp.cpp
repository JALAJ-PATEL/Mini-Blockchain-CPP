#include "utils/Timestamp.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

std::string Timestamp::getCurrentUTCTime() {
    auto now = std::chrono::system_clock::now(); // Captures the current time of system clock

    // Convert to time_t for easier formatting
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // gmtime converts time_t to UTC time
    std::tm* gmt_time = std::gmtime(&now_time);

    std::ostringstream oss;
    oss << std::put_time(gmt_time, "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
}
