#include "HealthPotion.h"
#include "Character.h"
#include <iostream>
#include <algorithm>
#include "LogManager.h"

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
    LogManager::GetInstance().PrintPotionEffect(this->name, actualRestore);
}