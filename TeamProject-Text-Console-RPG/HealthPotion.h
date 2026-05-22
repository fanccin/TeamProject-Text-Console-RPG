#pragma once
#include "Item.h"
class HealthPotion :
    public Item
{
private:
    std::string name;
    int healthRestore; // 회복량 수치

public:
    HealthPotion(std::string n = "체력 포션", int restore = 50);

    std::string getName() override;
    void use(Character* character) override;
    int getPrice() override;
};