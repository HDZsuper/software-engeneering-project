#pragma once

#include <vector>
#include <ctime>
#include <iostream>

class Date {
public:
    // ��ȡʱ���
    time_t GetTime() const {
        return val;
    }

    // ��ȡ����ʱ�����ϸ��Ϣ
    std::vector<int> GetDetail() const {
        return detail;
    }

    // ��ʾ����ʱ��
    void Display() const {
        std::cout << detail[0] << "��" << detail[1] << "��" << detail[2] << "��"
            << detail[3] << "ʱ" << detail[4] << "��" << detail[5] << "��";
    }

    // ���캯����ͨ������ʱ����ϸ��Ϣ�����ʼ��
    explicit Date(const std::vector<int>& date_detail);

    // ���캯����ͨ��ʱ�����ʼ��
    explicit Date(time_t timestamp);

private:
    std::vector<int> detail;  // ����ʱ�����ϸ��Ϣ���ꡢ�¡��ա�ʱ���֡��룩
    time_t val;  // ʱ���
};