#pragma once
#include "Item.h"
class HealthPotion :
    public Item
{
private:
    std::string name;
    int healthRestore; // 회복량 수치
    int price;
public:
    HealthPotion(std::string n, int restore, int p);

    std::string getName() override;
    void use(Character* character) override;
    int getPrice() override { return price; }
    bool isConsumable() override { return true; }
};