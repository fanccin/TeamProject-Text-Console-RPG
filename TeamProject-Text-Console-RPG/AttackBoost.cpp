#include "AttackBoost.h"
#include "Characters.h"
#include <iostream>
class Character;

using namespace std;

AttackBoost::AttackBoost(std::string n, int increase)
    : name(n), attackIncrease(increase) {
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

int AttackBoost::getPrice() {
    return 150; // 공격력 포션 가격 (원하는 숫자로 적으셔도 됩니다)
}