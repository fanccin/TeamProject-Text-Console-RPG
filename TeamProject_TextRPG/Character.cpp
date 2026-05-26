#include <iostream>
#include <string>
#include "Character.h"
#include "Inventory.h"

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
    attack = 30;
    defense = 30;
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
void Character::setAttack(int _attack) { attack = _attack; }
void Character::setDefense(int _defense) { defense = _defense; }
void Character::setExp(int _exp) { exp = _exp; }
void Character::setMaxExp(int _maxExp) { maxexp = _maxExp; }
void Character::setGold(int _Gold) { gold = _Gold; }

void Character::displayStatus()
{
    cout << "\n========= [속성 상세정보] =========" << endl;
    cout << " 이름     : " << name << endl;
    cout << " 직업     : " << job << endl;
    cout << " 레벨     : " << level << " / 10" << endl;
    cout << " HP       : " << health << " / " << maxhealth << endl;
    cout << " MP       : " << mp << " / " << maxmp << endl;
    cout << " 경험치   : " << exp << " / " << maxexp << endl;
    cout << " 공격력   : " << attack << endl;
    cout << " 방어력   : " << defense << endl;
    cout << " 보유골드 : " << gold << " G" << endl;
    cout << "===================================\n" << endl;
}

void Character::takeDamage(int damage)
{
    int actualDamage = damage - defense;
    if (actualDamage < 0) actualDamage = 0;

    health -= actualDamage;
    if (health < 0) health = 0;

    std::cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! (남은 체력: " << health << ")" << std::endl;
}

void Character::GainExp(int amount)
{
    exp += amount;
    int oldlevel = level;
    int beforeHP = maxhealth;
    int beforeattack = attack;

    cout << "\n -> 경험치 +" << amount << " 획득! (현재 경험치: " << exp << "/" << maxexp << ")\n";

    while (exp >= maxexp && level < 10)
    {
        exp -= maxexp;
        level++;
        maxhealth += level * 20;
        attack += level * 5;
        health = maxhealth;
        maxexp += 10;
    }

    if (level >= 10)
    {
        level = 10;
    }

    if (level > oldlevel)
    {
        cout << "\n레벨업 조건 충족\n";
        cout << "★☆★★☆★★☆★★☆★☆★★\n";
        cout << "★☆★ LEVEL UP ★☆★\n";
        cout << "★☆★★☆★★☆★★☆★☆★★\n";
        cout << " -> Lv." << oldlevel << " -> Lv." << level << "\n";
        cout << " -> HP +" << (maxhealth - beforeHP) << " 공격력 +" << (attack - beforeattack) << " 증가!\n";
        cout << "\n스탯이 상승했습니다!\n";
        cout << "HP : " << beforeHP << " -> " << maxhealth << "\n";
        cout << "공격력 : " << beforeattack << " -> " << attack << "\n";
    }
}

Warrior::Warrior(std::string name) : Character(name)
{
    this->job = "전사";
    this->health += 50;
    this->maxhealth += 50;
    this->defense += 50;
    cout << "초보 탈락 전사 합격. (HP +50. 방어력 +50.)\n";
    cout << "공격 습득!\n";
    cout << "스킬 습득!\n";
}

Magician::Magician(std::string name) : Character(name)
{
    this->job = "마법사";
    this->mp += 50;
    this->maxmp += 50;
    this->attack += 50;
    cout << "초보 탈락 법사 합격. (MP +50. 공격력 +50.)\n";
    cout << "공격 습득!\n";
    cout << "스킬 습득!\n";
}

Thief::Thief(std::string name) : Character(name)
{
    this->job = "도적";
    this->health += 20;
    this->maxhealth += 20;
    this->attack += 20;
    cout << "초보 탈락 도적 합격. (HP +20. 공격력 +20.)\n";
    cout << "공격 습득!\n";
    cout << "스킬 습득!\n";
}

Archer::Archer(std::string name) : Character(name)
{
    this->job = "궁수";
    this->attack *= 2;
    cout << "초보 탈락 궁수 합격. (공격력 2배.)\n";
    cout << "공격 습득!\n";
    cout << "스킬 습득!\n";
}