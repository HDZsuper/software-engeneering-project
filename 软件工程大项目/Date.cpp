#include "Date.h"
Date::Date(const std::vector<int>&arr)//������ʱ����
{
    detail = arr;
    tm time_info = {};
    time_info.tm_year = arr[0] - 1900;
    time_info.tm_mon = arr[1] - 1;
    time_info.tm_mday = arr[2];
    time_info.tm_hour = arr[3];
    time_info.tm_min = arr[4];
    time_info.tm_sec = arr[5];
    time_t raw_time = mktime(&time_info);
    val = raw_time;
}
Date::Date(time_t t)
{
    val = t;
    time_t raw_time = static_cast<time_t>(t);
    tm* time_info = localtime(&raw_time);

    detail = {
        time_info->tm_year + 1900, // ��ݴ� 1900 ��ʼ
        time_info->tm_mon + 1,    // �·ݴ� 0 ��ʼ
        time_info->tm_mday,
        time_info->tm_hour,
        time_info->tm_min,
        time_info->tm_sec
    };
}