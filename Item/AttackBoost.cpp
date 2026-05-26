#include "AttackBoost.h"
#include "Character.h"
#include <iostream>
class Character;

using namespace std;

AttackBoost::AttackBoost(std::string n, int buff, int p)
    : name(n), attackIncrease(buff), price(p) {
}

std::string AttackBoost::getName() {
    return name;
}

void AttackBoost::use(Character* character) {
    if (character == nullptr) return;

    int currentAttack = character->getAttack();
    character->setAttack(currentAttack + attackIncrease);
    cout << "" << name << "을 사용하여 공격력을 " << attackIncrease << " 증가시켰습니다!(이번 전투 동안만 유지됩니다)" << endl;
    cout << "현재 공격력: " << character->getAttack() << endl;
}