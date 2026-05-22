//Characters.h

#pragma once
#include<string>
#include<Inventory.h>

//Level up 부분은 통합됨.

class Character //과제 내용에서 방어와 MP 추가됨.
{
public:
    Character(std::string Name);
    
    std::string getName();
    std::string getJob();    
    int getLevel();
    int getHealth();
    int getMaxHealth();
    int getMp();
    int getMaxMp();
    int getAttack();
    int getDefense();
    int getExp();
    int getMaxExp();
    int getGold();
    
    void setLevel(int _level);
    void setHealth(int _health);
    void setMaxHealth(int _maxhealth);
    void setMp(int _mp);
    void setMaxMp(int _maxmp);
    void setAttack(int _attack);
    void setDefense(int _defense);
    void setExp(int _exp);
    void setMaxExp(int _maxExp);
    void setGold(int _Gold);
    
    void GainExp(int amount);
    
    virtual ~Character() = default; //가상소멸자 - 전직 시 기본 
    
    void displayStatus();

    
protected: //직업 선택 시 변수 변경.
    std::string name;
    std::string job;
    int level; //레벨업 파트 받아서 가져오기.
    int health;
    int maxhealth;
    int mp;
    int maxmp;
    int attack;
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
    
//    void attack(Monster* monster) override;
};


class Magician : public Character
{
public:
    Magician(std::string name);
    
//    void attack(Monster* monster) override;
};


class Thief : public Character
{
public:
    Thief(std::string name);
    
//    void attack(Monster* monster) override;
};


class Archer : public Character
{
public:
    Archer(std::string name);
    
//    void attack(Monster* monster) override;
};


//장비 장착
// class Equip : public Character
// {
// public:
//     Equip(int health, int maxhealth, int mp, int maxmp, int attack, int defense);
// };
