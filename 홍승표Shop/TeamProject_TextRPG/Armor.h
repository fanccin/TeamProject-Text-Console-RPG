#pragma once
#include "Item.h"

class Character;

class Armor :
    public Item
{
private:
    std::string name;
    int defense;
    int price;
public:
    Armor(std::string n, int def, int p);

    std::string getName() override;
    void use(Character* character) override;
    int getPrice() override { return price; }
};
