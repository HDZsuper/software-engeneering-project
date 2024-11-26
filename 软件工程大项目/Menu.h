#pragma once

#include "Task.h"
#include "Shop.h"
#include <iostream>
#include <mutex>
#include <Windows.h> // ͨ�����齫ϵͳ��ͷ�ļ����ں��棬����ȡ�������ľ�������ͱ�������Ϊ
#include <fstream>
#include <vector>
#include <algorithm>

class Menu {
private:
    Shop shop;
    std::vector<Task*> tasks_;
    std::mutex tasks_mtx_;

public:
    int money_;

    void MainMenu();
    void SetTaskMenu();
    void LookTaskMenu();
    void CheckAllTasks();
    void SaveAll();
    void LoadAll();
    void ShowTask(std::string cate = "*", std::vector<std::string> tags = {});
    void ChangeTask(Task* p, std::string op);

    // �Ƴ�ע�͵��Ĵ����У���Ϊ����Ӧ�ó��������յĲ�Ʒ������
    // std::lock_guard<std::mutex> lock(tasks__mtx); // ע�͵��Ĵ����ѱ��Ƴ�
};