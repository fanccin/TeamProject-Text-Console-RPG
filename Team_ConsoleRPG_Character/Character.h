//Character.h

#pragma once
#include<string>
#include "Inventory.h"

//Level up 부분은 통합됨.

class Character //과제 내용에서 방어와 MP 추가됨.
{

    
    
public:
    Character(std::string Name); // 22일 이야기했던 헤더파일 선언 내용. .cpp 정리.
    
    std::string getName() const { return name; };
    std::string getJob() const { return job; };    
    int getLevel() const { return level; };
    int getHealth(){ return health; };
    int getMaxHealth(){ return maxhealth; };
    int getMp(){ return mp; };
    int getMaxMp(){ return maxmp; };
    int getAttack(){ return attack; };
    int getDefense(){ return defense; };
    int getExp(){ return exp; };
    int getMaxExp(){ return maxexp; };
    int getGold(){ return gold; };
    int getInventory(){ return inventory; };
    
    void setLevel(int _level) { level = _level; }
    void setHealth(int _health) { health = _health; }
    void setMaxHealth(int _maxhealth) { maxhealth = _maxhealth; }
    void setMp(int _mp) { mp = _mp; }
    void setMaxMp(int _maxmp) { maxmp = _maxmp; }
    void setAttack(int _attack) { attack = _attack; }
    void setDefense(int _defense) { defense = _defense; }
    void setExp(int _exp) { exp = _exp; }
    void setMaxExp(int _maxExp) { maxexp = _maxExp; }
    void setGold(int _Gold) { gold = _Gold; }
    
    void GainExp(int amount);
    
    virtual ~Character() = default; //가상소멸자 - 전직 시 기본 
    
    void displayStatus();

    virtual void takeDamage(int damage)
    {
        int actualDamage = damage - defense;
        if (actualDamage < 0) actualDamage = 0;
    
        health -= actualDamage;
        if (health < 0) health = 0;
    
        std::cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! (남은 체력: " << health << ")" << std::endl;
    }
    
    virtual int SkillAttack() = 0;
    
    
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
    
    int SkillAttack();
};


class Magician : public Character
{
public:
    Magician(std::string name);
    
    int SkillAttack();
};


class Thief : public Character
{
public:
    Thief(std::string name);
    
    int SkillAttack();

};


class Archer : public Character
{
public:
    Archer(std::string name);
    
    int SkillAttack();
};


