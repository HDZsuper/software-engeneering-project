#pragma once
#include<string>
#include<ctime>
#include<vector>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include"FocusMode.h"
#include"Date.h"

#define MAX_SIZE 32
class Task {
protected:
    int id_;
    int type_;
    std::string title_;
    std::string description_;
    Date dueDate_;
    std::vector<std::string> tags_;
    std::string category_;

    friend class Menu;

public:
    Task(int id, const std::string& title, const std::string& description, Date dueDate)
        : id_(id), title_(title), description_(description), dueDate_(dueDate), type_(0) {}

    void ResetDDL(Date a) { dueDate_ = a; }
    void ResetName(const std::string& s) { title_ = s; }
    void ResetDescribe(const std::string& s) { description_ = s; }

    void SetCategory(const std::string& category) { category_ = category; }
    void AddTag(const std::string& tag) { tags_.push_back(tag); }
    void RemoveTag(const std::string& tag) {
        tags_.erase(std::remove(tags_.begin(), tags_.end(), tag), tags_.end());
    }
    time_t GetTime() const { return dueDate_.GetTime(); }

    virtual void Save(std::ofstream& file);
    virtual int Finish();
    void Display() const;

    std::vector<Date> reminderTimes;

    virtual ~Task() = default;
};

class DDLTask : public Task {
public:
    DDLTask(int id, const std::string& title, const std::string& description, Date dueDate)
        : Task(id, title, description, dueDate) {
        type_ = 1;
    }

    static DDLTask* load(std::istream& in);

    void setReminder(time_t now) {
        if (now < dueDate_.GetTime() - 60 * 60 * 24)
            reminderTimes.push_back(Date(dueDate_.GetTime() - 60 * 60 * 24));
        if (now < dueDate_.GetTime() - 60 * 60 * 5)
            reminderTimes.push_back(Date(dueDate_.GetTime() - 60 * 60 * 5));
        if (now < dueDate_.GetTime() - 60 * 60 * 1)
            reminderTimes.push_back(Date(dueDate_.GetTime() - 60 * 60 * 1));
        if (now < dueDate_.GetTime())
            reminderTimes.push_back(dueDate_);
    }
};

class ScheduledTask : public Task {
private:
    FocusMode focusmode_;

public:
    ScheduledTask(int id, const std::string& title, const std::string& description, Date dueDate)
        : Task(id, title, description, dueDate), focusmode_() {
        type_ = 2;
    }

    static ScheduledTask* load(std::istream& in);

    void enableFocusMode() { focusmode_.start(); }

    bool quit(time_t t);
    int start();
};