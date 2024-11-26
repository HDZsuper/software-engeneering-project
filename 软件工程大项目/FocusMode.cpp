#include "FocusMode.h"

void FocusMode::start() {
    isActive = true;
    // Todo: 实现禁用应用程序的逻辑
}

void FocusMode::stop() {
    isActive = false;
}

void FocusMode::addBlockedApp(const std::string& app) {
    blockedApps.push_back(app);
}

void FocusMode::removeBlockedApp(const std::string& app) {
    blockedApps.erase(std::remove(blockedApps.begin(), blockedApps.end(), app), blockedApps.end());
}

void FocusMode::cofig()
{
	//Todo
}