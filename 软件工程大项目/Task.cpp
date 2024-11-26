#include "Task.h"
std::vector<int>occupied_id(MAX_SIZE);

void Task::Save(std::ofstream& file) {
    file << title_ << " " << description_ << " ";
    std::vector<int> tmp = dueDate_.GetDetail();
    for (int i : tmp) {
        file << i << " ";
    }
    file << category_ << " " << tags_.size() << " ";
    for (const auto& tag : tags_) {
        file << tag << " ";
    }
}

int Task::Finish() {
    if (type_ == 2) {
        occupied_id[id_] = 0;
    }
    std::cout << "�������ĥ�³���÷�����Կຮ������ϲ���������\n";
    srand(dueDate_.GetTime());

    int money = rand() % 100 + 50;
    std::cout << "�������" << money << "�������Ϊ����\n";
    return money;
}

void Task::Display() const {
    std::cout << "id: " << id_ << "  name: " << title_ << "  category: " << category_ << '\n';
    std::cout << "tags: ";
    for (const auto& tag : tags_) {
        std::cout << tag << " ";
    }
    std::cout << '\n';
    std::cout << "describe:" << description_ << '\n';
    std::cout << "DDL:";
    dueDate_.Display();
    std::cout << "\n\n";
}

bool ScheduledTask::quit(time_t t) {
    std::cout << "��ȷ�����Ҫ�˳�������\n";
    while (time(0) < t + 3) {
        if (_kbhit()) {
            char c = getchar();
            if (c == 'q') {
                return true;
            }
        }
        Sleep(1);
    }
    return false;
}

int ScheduledTask::start() {
    std::cout << "������" << title_ << "��";
    dueDate_.Display();
    std::cout << "���֮ǰ���������뿪����ȥ�ɱ��Ŷ\n";
    while (time(0) < dueDate_.GetTime()) {
        if (_kbhit()) {
            char c = getchar();
            if (c == 'q') {
                if (quit(time(0))) {
                    return 0;
                }
            }
        }
        Sleep(1);
    }
    return Finish();
}

DDLTask* DDLTask::load(std::istream& in) {
    int id = 0;
    std::string title, describe;
    std::vector<int> detail(6);
    std::string category;
    int num_tags;
    std::string tmp;
    for (; id < MAX_SIZE; ++id) {
        if (!occupied_id[id]) {
            break;
        }
    }
    occupied_id[id] = 1;
    in >> title >> describe;
    for (int i = 0; i < 6; ++i) {
        in >> detail[i];
    }
    DDLTask* p = new DDLTask(id, title, describe, static_cast<Date>(detail));
    in >> category >> num_tags;
    p->SetCategory(category);
    for (int i = 0; i < num_tags; ++i) {
        in >> tmp;
        p->AddTag(tmp);
    }
    p->setReminder(time(0));
    if (!in.fail()) {
        return p;
    }
    return nullptr;
}

ScheduledTask* ScheduledTask::load(std::istream& in) {
    int id = 0;
    std::string title, describe;
    std::vector<int> detail(6);
    std::string category;
    int num_tags;
    std::string tmp;
    for (; id < MAX_SIZE; ++id) {
        if (!occupied_id[id]) {
            break;
        }
    }
    occupied_id[id] = 1;
    in >> title >> describe;
    for (int i = 0; i < 6; ++i) {
        in >> detail[i];
    }
    ScheduledTask* p = new ScheduledTask(id, title, describe, static_cast<Date>(detail));
    in >> category >> num_tags;
    p->SetCategory(category);
    for (int i = 0; i < num_tags; ++i) {
        in >> tmp;
        p->AddTag(tmp);
    }
    if (!in.fail()) {
        return p;
    }
    return nullptr;
}