#pragma once
#include <vector>
#include <string>

class FocusMode {
private:
    bool isActive = false;
    std::vector<std::string> blockedApps;

public:
    void start();
    void stop();
    void addBlockedApp(const std::string& app);
    void removeBlockedApp(const std::string& app);
    void cofig(); // ±£ÁôÉùÃ÷
};