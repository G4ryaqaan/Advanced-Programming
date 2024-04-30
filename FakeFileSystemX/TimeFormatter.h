#pragma once
#include <string>
#include <filesystem>


using namespace std;
using namespace filesystem;


/**
 * @class TimeFormatter
 * @brief This class is used to format time into several differnt time frames that are nessesary.
 */
class TimeFormatter {
public:
    static std::string formatTime(time_t timeStamp);
    static const tm convertTime(const filesystem::file_time_type& timestamp);
    static const time_t convertTimeToTimeT(const tm& timestamp);
};
