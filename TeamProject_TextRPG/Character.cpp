#include <iostream>
#include <string>
#include "Character.h"
#include "Inventory.h"
#include "LogManager.h"

using namespace std;

Character::Character(std::string name)
{
    this->name = name;
    job = "무직";
    level = 1;
    health = 200;
    maxhealth = 200;
    mp = 50;
    maxmp = 50;
    baseAttack = 50;
    defense = 50;
    gold = 0;
    exp = 0;
    maxexp = 100;
    inventory = new Inventory();
}

void Character::setLevel(int _level) { level = _level; }
void Character::setHealth(int _health) { health = _health; }
void Character::setMaxHealth(int _maxhealth) { maxhealth = _maxhealth; }
void Character::setMp(int _mp) { mp = _mp; }
void Character::setMaxMp(int _maxmp) { maxmp = _maxmp; }
void Character::setDefense(int _defense) { defense = _defense; }
void Character::setExp(int _exp) { exp = _exp; }
void Character::setMaxExp(int _maxExp) { maxexp = _maxExp; }
void Character::setGold(int _Gold) { gold = _Gold; }

int Character::takeDamage(int damage)
{
    int actualDamage = damage - defense;
    if (actualDamage <= 0) actualDamage = 1;

    health -= actualDamage;
    if (health < 0) health = 0;

    return actualDamage;
}

void Character::GainExp(int amount)
{
    exp += amount;
    int oldlevel = level;
    int beforeHP = maxhealth;
    int beforeattack = baseAttack;

    LogManager::GetInstance().PrintExpReward(amount, exp, maxexp);

    while (exp >= maxexp && level < 10)
    {
        exp -= maxexp;
        level++;
        maxhealth += level * 20;
        baseAttack += level * 5;
        health = maxhealth;
        maxexp += 10;
    }

    if (oldlevel < 10 && level >= 10)
    {
        std::cout << "이제 일반 몬스터는 상대도 안 된다!\n";
        level = 10;
    }

    if (level > oldlevel)
    {
        LogManager::GetInstance().PrintLevelUp(
            oldlevel, level,
            (maxhealth - beforeHP), (baseAttack - beforeattack),
            beforeHP, maxhealth,
            beforeattack, baseAttack
        );
    }
}

Warrior::Warrior(std::string name) : Character(name)
{
    this->job = "전사";
    this->health += 50;
    this->maxhealth += 50;
    this->defense += 10;
    cout << "강인한 전사는 체력과 방어력이 증가합니다. (HP +50, 방어력 +10)\n";
    cout << "기본 공격 습득!\n";
    cout << "스킬 습득!\n";
}

Magician::Magician(std::string name) : Character(name)
{
    this->job = "마법사";
    this->mp += 50;
    this->maxmp += 50;
    this->baseAttack += 10;
    cout << "신비로운 마법사는 마력과 공격력이 증가합니다. (MP +50, 공격력 +10)\n";
    cout << "공격 습득!\n";
    cout << "스킬 습득!\n";
}

Thief::Thief(std::string name) : Character(name)
{
    this->job = "도적";
    this->health -= 50;
    this->maxhealth -= 50;
    this->baseAttack += 30;
    cout << "재빠른 도적은 체력이 낮지만 공격력이 높습니다. (HP -50, 공격력 +30)\n";
    cout << "기본 공격 습득!\n";
    cout << "스킬 습득!\n";
}

Archer::Archer(std::string name) : Character(name)
{
    this->job = "궁수";
    this->health -= 100;
    this->maxhealth -= 100;
    this->baseAttack += 40;
    cout << "멀리서 적을 공격하는 궁수의 화살은 매우 강력합니다. (HP -100, 공격력 +40 )\n";
    cout << "기본 공격 습득!\n";
    cout << "스킬 습득!\n";
}