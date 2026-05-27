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
    std::string type;
public:
    Armor(std::string n, int def, int p);

    std::string getName() override;
    void use(Character* character) override;
    int getPrice() override { return price; }
    std::string getType() override { return type; }
};
