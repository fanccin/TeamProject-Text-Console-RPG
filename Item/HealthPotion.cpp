#include "HealthPotion.h"
#include "Character.h"
#include <iostream>
#include <algorithm>

using namespace std;

class Character;

HealthPotion::HealthPotion(std::string n, int restore, int p)
    : name(n), healthRestore(restore), price(p) {
}

std::string HealthPotion::getName() {
    return name;
}

void HealthPotion::use(Character* character) {
    if (character == nullptr) return;

    int currentHp = character->getHealth();
    int maxHp = character->getMaxHealth();

    int nextHp = std::min(currentHp + healthRestore, maxHp);

    int actualRestore = nextHp - currentHp;
    character->setHealth(nextHp);
    cout << "" << name << "을 사용하여 체력을 " << healthRestore << " 회복했습니다!" << endl;
}