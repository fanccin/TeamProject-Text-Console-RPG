#pragma once
#include "Item.h"
class AttackBoost :
    public Item
{
private:
    std::string name;
    int attackIncrease; // 공격력 증가 수치
    int price;
public:
    AttackBoost(std::string n, int buff, int p);

    std::string getName() override;
    void use(Character* character) override;
    int getPrice() override { return price; }
    bool isConsumable() override { return true; }
};

