#pragma once
#include "Item.h"

class Character;

class Weapon :
    public Item
{
private:
    std::string name;
    std::string type;
    int damage;
    int price;
public:
    Weapon(std::string n, int dmg, int p);

    std::string getName() override;
    void use(Character* character) override;
    int getPrice() override { return price; }
    int getDamagaIncrease() { return damage; }
    std::string getType() override { return type; }
};