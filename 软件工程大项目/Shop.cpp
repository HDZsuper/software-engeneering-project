#include "Shop.h"
#include "menu.h"
#include <Windows.h>
extern Menu m;
void Shop::ShopMenu() {
    system("cls");
    Display();

    std::string input;
    while (true) {
        std::cout << "��ǰӵ�н��������" << m.money_ << '\n';
        std::cout << "(�����﷨��buy name num)\n";
        std::cout << "������Ҫ�������Ʒ������(q�˳�)��";
        std::cin >> input;

        if (input == "q") {
            return;
        }

        if (input == "buy") {
            std::string product_name;
            int quantity;
            std::cin >> product_name >> quantity;

            bool found = false;
            for (auto product : products_) {
                if (product->name_ == product_name) {
                    found = true;
                    if (m.money_ < product->Purchase(quantity)) {
                        std::cout << "��Ǯ����\n";
                    }
                    else {
                        m.money_ -= product->Purchase(quantity);
                        std::cout << "�ɹ�����\n";
                        m.SaveAll();
                    }
                    break;  // �ҵ�ƥ�����Ʒ�󣬿�������ѭ��
                }
            }

            if (!found) {
                std::cout << "δ�ҵ���Ʒ\n";
            }
        }

        // �����������
        if (std::cin.fail()){
            std::string tmp;
            std::cin.clear();
            std::cin >> tmp;
        }

        std::cout << '\n';
    }
}