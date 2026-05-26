#include "Weapon.h"
#include "Character.h"
#include <iostream>

Weapon::Weapon(std::string n, int dmg, int p) : name(n), damage(dmg), price(p) {}

std::string Weapon::getName() {
    return name;
}

void Weapon::use(Character* character) {
    if (character == nullptr) return;

    int currentAttack = character->getAttack();
    character->setAttack(currentAttack + damage);

    std::cout << name << "을(를) 장착하여 공격력이 " << damage << " 증가했습니다!" << std::endl;
}