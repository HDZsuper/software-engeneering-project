#include "Shop.h"
#include "menu.h"
#include <Windows.h>
extern Menu m;
void Shop::ShopMenu() {
    system("cls");
    Display();

    std::string input;
    while (true) {
        std::cout << "当前拥有金币数量：" << m.money_ << '\n';
        std::cout << "(购买语法：buy name num)\n";
        std::cout << "请输入要购买的商品与数量(q退出)：";
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
                        std::cout << "金钱不足\n";
                    }
                    else {
                        m.money_ -= product->Purchase(quantity);
                        std::cout << "成功购买\n";
                        m.SaveAll();
                    }
                    break;  // 找到匹配的商品后，可以跳出循环
                }
            }

            if (!found) {
                std::cout << "未找到商品\n";
            }
        }

        // 处理输入错误
        if (std::cin.fail()){
            std::string tmp;
            std::cin.clear();
            std::cin >> tmp;
        }

        std::cout << '\n';
    }
}