#include "HealthPotion.h"
#include "Characters.h"
#include <iostream>
using namespace std;

class Character;

HealthPotion::HealthPotion(std::string n, int restore)
    : name(n), healthRestore(restore) {
}

std::string HealthPotion::getName() {
    return name;
}

void HealthPotion::use(Character* character) {
    if (character == nullptr) return;

    int currentHp = character->getHealth();
    character->setHealth(currentHp + healthRestore);
    cout << "" << name << "을 사용하여 체력을 " << healthRestore << " 회복했습니다!" << endl;
}

int HealthPotion::getPrice() {
    return 100; // 체력 포션 가격
}