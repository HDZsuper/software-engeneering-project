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
        Product* p1 = new Product("СС��С����", "�ܱ��˵��Ǻܺ���", 10);
        products_.push_back(p1);

        Product* p2 = new Product("����ͷ��", "�ܹ���������ͷ���ʹ��Ȩ��", 1000);
        products_.push_back(p2);

        Product* p3 = new Product("�ƽ�ͷ��", "�ܹ������ƽ�ͷ���ʹ��Ȩ��", 5000);
        products_.push_back(p3);

        Product* p4 = new Product("��ʯͷ��", "�ܹ�������ʯͷ���ʹ��Ȩ��", 10000);
        products_.push_back(p4);
    }


private:

    std::vector<Product*> products_;
};