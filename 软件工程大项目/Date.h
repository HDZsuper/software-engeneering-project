#pragma once

#include <vector>
#include <ctime>
#include <iostream>

class Date {
public:
    // 获取时间戳
    time_t GetTime() const {
        return val;
    }

    // 获取日期时间的详细信息
    std::vector<int> GetDetail() const {
        return detail;
    }

    // 显示日期时间
    void Display() const {
        std::cout << detail[0] << "年" << detail[1] << "月" << detail[2] << "日"
            << detail[3] << "时" << detail[4] << "分" << detail[5] << "秒";
    }

    // 构造函数，通过日期时间详细信息数组初始化
    explicit Date(const std::vector<int>& date_detail);

    // 构造函数，通过时间戳初始化
    explicit Date(time_t timestamp);

private:
    std::vector<int> detail;  // 日期时间的详细信息（年、月、日、时、分、秒）
    time_t val;  // 时间戳
};