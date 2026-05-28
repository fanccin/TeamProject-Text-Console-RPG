#include "Weapon.h"
#include "Character.h"
#include <iostream>
#include "LogManager.h"

Weapon::Weapon(std::string n, int dmg, int p) : name(n), damage(dmg), price(p) {}

std::string Weapon::getName() {
    return name;
}

void Weapon::use(Character* character) {
    if (character == nullptr) return;

    int currentAttack = character->getAttack();
    character->setAttack(currentAttack + damage);

    LogManager::GetInstance().PrintWeaponEquip(this->name, this->damage);
}