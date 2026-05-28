#include "AttackBoost.h"
#include "Character.h"
#include <iostream>
#include "LogManager.h"
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
    int actualAttack = currentAttack + attackIncrease;
    character->setAttack(actualAttack);
    LogManager::GetInstance().PrintBattleBuffEffect(this->name, attackIncrease, character->getAttack());
}