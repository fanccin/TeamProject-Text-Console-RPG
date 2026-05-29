//Characters.h

#pragma once
#include<string>
#include"Inventory.h"

//Level up 부분은 통합됨.

class Character //과제 내용에서 방어와 MP 추가됨.
{
public:
    Character(std::string Name);

    std::string getName() const { return name; }
    std::string getJob() const { return job; }
    int getLevel() const { return level; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxhealth; }
    int getMp() const { return mp; }
    int getMaxMp() const { return maxmp; }
    int getAttack() const { return baseAttack + buffAttack; }
    int getDefense() const { return defense; }
    int getExp() const { return exp; }
    int getMaxExp() const { return maxexp; }
    int getGold() const { return gold; }
    Inventory* getInventory() { return inventory; }

    void setLevel(int _level);
    void setHealth(int _health);
    void setMaxHealth(int _maxhealth);
    void setMp(int _mp);
    void setMaxMp(int _maxmp);
    void setBaseAttack(int amount) { baseAttack = amount; }
    void addBuffAttack(int amount) { buffAttack += amount; }
    void setDefense(int _defense);
    void setExp(int _exp);
    void setMaxExp(int _maxExp);
    void setGold(int _Gold);
    
    void GainExp(int amount);

    virtual ~Character() = default; //가상소멸자 - 전직 시 기본 
    
    int takeDamage(int damage);

    // 순수 가상 함수
    virtual int skillAttack() = 0;

    // 도핑 끄는 함수
    void clearBuff() { buffAttack = 0; }
    

protected: //직업 선택 시 변수 변경.
    std::string name;
    std::string job;
    int level; //레벨업 파트 받아서 가져오기.
    int health;
    int maxhealth;
    int mp;
    int maxmp;
    int baseAttack; //기본 공격력 + 장비로 올라간 공격력
    int buffAttack; //일시적인 버프 공격력
    int defense;
    int exp;
    int maxexp;
    int gold;
    Inventory* inventory;
 };



//각 직업

class Warrior : public Character
{
public:
    Warrior(std::string name);
    int skillAttack() override {
        int skillDamage = baseAttack * 2;
        return skillDamage;
    }
};


class Magician : public Character
{
public:
    Magician(std::string name);
    int skillAttack() override {
        int skillDamage = baseAttack * 2;
        return skillDamage;
    }
};


class Thief : public Character
{
public:
    Thief(std::string name);
    int skillAttack() override {
        int skillDamage = baseAttack * 2;
        return skillDamage;
    }
};


class Archer : public Character
{
public:
    Archer(std::string name);
    int skillAttack() override {
        int skillDamage = baseAttack * 2;
        return skillDamage;
    }
};


//장비 장착
// class Equip : public Character
// {
// public:
//     Equip(int health, int maxhealth, int mp, int maxmp, int attack, int defense);
// };