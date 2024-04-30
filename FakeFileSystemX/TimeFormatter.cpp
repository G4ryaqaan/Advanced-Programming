#include "TimeFormatter.h"

std::string TimeFormatter::formatTime(time_t timeStamp) {
    char buffer[80];
    struct tm timeinfo;

    localtime_s(&timeinfo, &timeStamp);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    return std::string(buffer);
}

const tm TimeFormatter::convertTime(const filesystem::file_time_type& timestamp) {
    using namespace chrono;
    system_clock::time_point delta = time_point_cast<system_clock::duration>(timestamp - filesystem::file_time_type::clock::now() + system_clock::now());
    time_t conversion = system_clock::to_time_t(delta);

    tm result;
    localtime_s(&result, &conversion);
    return result;
}

const time_t TimeFormatter::convertTimeToTimeT(const tm& timestamp) {
    return mktime(const_cast<tm*>(&timestamp));
}
