#pragma once
#include<string>
#include<iostream>
class Product {
    Product(std::string product_name, std::string product_description, int product_cost)
        : name_(product_name), description_(product_description), cost_(product_cost) {}

    void DisplayInfo() const {
        std::cout << "商品名称：" << name_ << "   商品价格：" << cost_ << '\n';
        std::cout << "商品描述：" << description_ << "\n\n";
    }

    int Purchase(int quantity) const {
        return quantity * cost_;
    }
    friend class Shop;
    std::string name_;
    std::string description_;
    int cost_;
};