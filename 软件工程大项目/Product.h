#pragma once
#include<string>
#include<iostream>
class Product {
    Product(std::string product_name, std::string product_description, int product_cost)
        : name_(product_name), description_(product_description), cost_(product_cost) {}

    void DisplayInfo() const {
        std::cout << "��Ʒ���ƣ�" << name_ << "   ��Ʒ�۸�" << cost_ << '\n';
        std::cout << "��Ʒ������" << description_ << "\n\n";
    }

    int Purchase(int quantity) const {
        return quantity * cost_;
    }
    friend class Shop;
    std::string name_;
    std::string description_;
    int cost_;
};