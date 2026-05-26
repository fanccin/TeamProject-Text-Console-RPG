#include "Armor.h"
#include "Character.h"
#include <iostream>

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

    std::cout << name << "을(를) 장착하여 방어력이 " << defense << " 증가했습니다!" << std::endl;
}