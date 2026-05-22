#pragma once
#include "Item.h"
class AttackBoost :
    public Item
{
private:
    std::string name;
    int attackIncrease; // 공격력 증가 수치

public:
    AttackBoost(std::string n = "공격력 포션", int increase = 10);

    std::string getName() override;
    void use(Character* character) override;
    int getPrice() override;
};

