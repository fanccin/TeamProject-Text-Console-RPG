//Characters.cpp

#include<iostream>
#include<string>
#include "Character.h"

using namespace std;

Character::Character(std::string name, int level, int health, int maxhealth, int mp, int maxmp, int attack, int Exp, int maxExp, int gold)
{
    //초기 능력치 레벨 1, 초기 체력 200, 공격력 30, 경험치 0으로 시작.
    this->name = name;
    this->level = 1;
    this->health = 200; //현재체력
    this->maxhealth = 200; //최대체력
    this->mp =50;
    this->maxmp = 50;
    this->attack = 30;
//    this->gold = 0; // 나중에 만약 보유 gold를 연결하게될 경우
    this->Exp = 0; //초기 경험치 0
    //    void 경험치(int 경험치)
}

void displayStatus(string name, int level, int health, int mp, int attack, int gold)
{
    cout<< "속성 상세정보\n";
    cout<< " " << name << "\n";
    cout<< " " << level << " /10\n";
    cout<< "S2 HP       " << health <<"\n";
    cout<< "MP        " << mp <<"\n";
    cout<< "X  공격력    " << attack <<"\n";
//    cout<< "[] 방어력    " << defense <<"\n"; //명조 상세정보 따라서 넣은 방어력.
    cout<< "$  보유골드  " << gold <<"\n";
}




Character::~Character(){}