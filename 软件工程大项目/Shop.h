#pragma once
#include"Product.h"
#include<vector>
class Shop {
public:
    void ShopMenu();

    void Display() {
        for (auto product : products_) {
            product->DisplayInfo();
        }
    }

    Shop() : products_() {
        Product* p1 = new Product("小小的小玩意", "很便宜但是很好玩", 10);
        products_.push_back(p1);

        Product* p2 = new Product("白银头像", "能够解锁白银头像的使用权限", 1000);
        products_.push_back(p2);

        Product* p3 = new Product("黄金头像", "能够解锁黄金头像的使用权限", 5000);
        products_.push_back(p3);

        Product* p4 = new Product("钻石头像", "能够解锁钻石头像的使用权限", 10000);
        products_.push_back(p4);
    }


private:

    std::vector<Product*> products_;
};