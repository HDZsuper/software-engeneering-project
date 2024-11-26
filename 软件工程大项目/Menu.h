#pragma once

#include "Task.h"
#include "Shop.h"
#include <iostream>
#include <mutex>
#include <Windows.h> // 通常建议将系统级头文件放在后面，但这取决于您的具体需求和编译器行为
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

    // 移除注释掉的代码行，因为它不应该出现在最终的产品代码中
    // std::lock_guard<std::mutex> lock(tasks__mtx); // 注释掉的代码已被移除
};