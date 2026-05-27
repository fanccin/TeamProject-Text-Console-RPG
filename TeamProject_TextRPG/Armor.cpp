#include "Armor.h"
#include "Character.h"
#include <iostream>
#include "LogManager.h"

Armor::Armor(std::string n, int def, int p)
    : name(n), defense(def), price(p) {
}

std::string Armor::getName() {
    return name;
}

void Armor::use(Character* character) {
    if (character == nullptr) return;

    int currentDefense = character->getDefense();
    character->setDefense(currentDefense + defense);

    LogManager::GetInstance().PrintArmorEquip(this->name, this->defense);
}