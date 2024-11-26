#include "Menu.h"

void Menu::MainMenu() {
	int input;
	while (true) {
		//system("cls");
		std::cout << "1����������\n";
		std::cout << "2���鿴����\n";
		std::cout << "3������̵�\n";
		std::cout << "4���˳�\n";
		std::cout << "�����룺";
		std::cin >> input;
		switch (input) {
		case 1:
			SetTaskMenu();
			break;
		case 2:
			LookTaskMenu();
			break;
		case 3:
			shop.ShopMenu();
			break;
		case 4:
			exit(0);
		default:
			std::cout << "�������\n";
		}
		if (std::cin.fail()) {
			std::string tmp;
			std::cin.clear();
			std::cin >> tmp;
		}
		std::cout << '\n';
	}
}

void Menu::SetTaskMenu() {
	//system("cls");
	std::cout << "��ʽ: id title desc detial[6] cate num_tags tags\n";
	std::cout << "������ָ�";
	int type;
	std::cin >> type;
	bool valid = true;
	if (type == 1) { // DDLʽ
		std::lock_guard<std::mutex> lock(tasks_mtx_);
		DDLTask* p = DDLTask::load(std::cin);
		if (p != nullptr) {
			tasks_.push_back(p);
		}
	}
	else if (type == 2) { // ��ʱʽ
		std::lock_guard<std::mutex> lock(tasks_mtx_);
		ScheduledTask* p = ScheduledTask::load(std::cin);
		if (p != nullptr) {
			money_ += p->start();
			delete p;
		}
	}
	else {
		valid = false;
	}
	if (std::cin.fail()) {
		valid = false;
	}
	if (!valid) {
		std::cout << "�Ƿ�ָ�\n";
		std::string tmp;
		std::cin >> tmp;
		std::cin.clear();
		return;
	}
	SaveAll();
}

void Menu::LookTaskMenu() {
	//system("cls");
	std::cout << "������ָ��(q�˳�)��\n";
	std::string ins;
	while (true) {
		std::cin >> ins;
		if (ins == "q") {
			return;
		}
		else if (ins == "ls") {
			ShowTask();
		}
		else if (ins == "del") { // ɾ������ del id
			std::lock_guard<std::mutex> lock(tasks_mtx_);
			int id;
			std::cin >> id;
			for (auto& task : tasks_) {
				if (task->id_ == id) {
					tasks_.erase(std::remove(tasks_.begin(), tasks_.end(), task), tasks_.end());
					break;
				}
			}
			SaveAll();
		}
		else if (ins == "change") { // �޸Ĳ��� change id op opnum
			std::lock_guard<std::mutex> lock(tasks_mtx_);
			int id;
			std::string op;
			std::cin >> id >> op;
			Task* p = nullptr;
			for (auto& task : tasks_) {
				if (task->id_ == id) {
					p = task;
					break;
				}
			}
			ChangeTask(p, op);
			SaveAll();
		}
		else if (ins == "look") { // ��ѯ���� look category tags_num tags
			std::string cate;
			int s;
			std::cin >> cate >> s;
			std::vector<std::string> tags(s);
			for (int i = 0; i < s; ++i) {
				std::cin >> tags[i];
			}
			ShowTask(cate, tags);
		}
		if (std::cin.fail()) {
			std::cout << "�Ƿ�ָ�\n";
			std::string tmp;
			std::cin >> tmp;
			std::cin.clear();
			return;
		}
	}
}

void Menu::CheckAllTasks() {
	std::lock_guard<std::mutex> lock(tasks_mtx_);  // ʹ���»��ߺ�׺����������
	time_t now = time(nullptr);  // ʹ��nullptr����0

	for (const auto& task : tasks_) {  // ʹ��const auto&���ⲻ��Ҫ�Ŀ���
		for (auto it = task->reminderTimes.begin(); it != task->reminderTimes.end(); ++it) {
			if (it->GetTime() <= now) {  // ����reminderTimes�洢����{time_t, ...}�Ķԣ�ʹ��first����time_t
				std::cout << "��ܰ��ʾ��������������" << task->title_ << "��������";

				// ʹ�ó�������ʱ��������ߴ���ɶ���
				const int one_day = 24 * 60 * 60;
				const int five_hours = 5 * 60 * 60;
				const int one_hour = 60 * 60;

				int time_difference = task->dueDate_.GetTime() - it->GetTime();
				switch (time_difference) {
				case one_day:
					std::cout << "1��\n";
					break;
				case five_hours:
					std::cout << "5Сʱ\n";
					break;
				case one_hour:
					std::cout << "1Сʱ\n";
					break;
				case 0:
					std::cout << "0��\n";
					break;
				}

				task->reminderTimes.erase(it);
				if (task->reminderTimes.empty()) {
					money_ += task->Finish();  // ʹ���»��ߺ�׺������Ա����
				}
				break;  // �����ڲ�ѭ��
			}
		}
	}
}

void Menu::SaveAll() {
	std::ofstream file("./data/save.txt", std::ios::out);
	file << money_ << '\n';
	file << tasks_.size() << '\n';
	for (const auto& task : tasks_) {
		task->Save(file);
		file << '\n';
	}
	file.close();
}

void Menu::LoadAll() {
	std::ifstream file("./data/save.txt", std::ios::in);
	file >> money_;
	int task_count;
	file >> task_count;
	tasks_.clear();
	for (int i = 0; i < task_count; ++i) {
		auto task = DDLTask::load(file);
		tasks_.push_back(task);
	}
	file.close();
}

void Menu::ShowTask(std::string cate, std::vector<std::string> tags) {
	std::lock_guard<std::mutex> lock(tasks_mtx_); // ����������Ҫ�������Ա�����tasks_�ķ���
	std::sort(tasks_.begin(), tasks_.end(), [](Task* x, Task* y) {
		return x->GetTime() > y->GetTime();
		});
	for (auto& task : tasks_) {
		bool show_task = (cate == task->category_ || cate == "*");
		for (const auto& tag : tags) {
			if (std::find(task->tags_.begin(), task->tags_.end(), tag) != task->tags_.end()) {
				show_task = true;
				break;
			}
		}
		if (show_task) {
			task->Display();
		}
	}
}

void Menu::ChangeTask(Task* task, std::string operation) {
	if (task == nullptr) {
		return;
	}

	std::string input;
	if (operation == "name") {
		std::cin >> input;
		task->ResetName(input);
	}
	else if (operation == "desc") {
		std::cin >> input;
		task->ResetDescribe(input);
	}
	else if (operation == "category") {
		std::cin >> input;
		task->SetCategory(input);
	}
	else if (operation == "ddl" || operation == "DDL") {
		std::vector<int> date_parts(6);
		for (int i = 0; i < 6; ++i) {
			std::cin >> date_parts[i];
		}
		task->ResetDDL(Date(date_parts));  // ����Date��һ���Ѷ�������ͻ��������ﲻ���Ķ�
	}
	else if (operation == "addtag") {
		std::cin >> input;
		task->AddTag(input);
	}
	else if (operation == "deltag") {
		std::cin >> input;
		task->RemoveTag(input);
	}
}