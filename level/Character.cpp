//Characters.cpp

#include<iostream>
#include<string>
#include "Character.h"

using namespace std;

Character::Character(std::string name, int level, int health, int maxhealth, int attack, int Exp, int maxExp, int gold)
{
    //초기 능력치 레벨 1, 초기 체력 200, 공격력 30, 경험치 0으로 시작.
    this->name = name;
    this->level = 1;
    this->health = 200; //현재체력
    this->maxhealth = 200; //최대체력
    this->attack = 30;
    this->gold = 0;
    this->Exp = 0; //초기 경험치 0
    this->maxExp= 100;
    //    void 경험치(int 경험치)
}

void displayStatus(string name, int level, int health, int attack, int gold)
{
    cout << "속성 상세정보\n";
    cout << " " << name << "\n";
    cout << " " << level << " /10\n";
    cout << "S2 HP       " << health << "\n";
    //cout<< "MP        " << mp <<"\n";  //MP 안 넣는다면 삭제 
    cout << "X  공격력    " << attack << "\n";
    //    cout<< "[] 방어력    " << defense <<"\n"; //명조 상세정보 따라서 넣은 방어력.
    cout << "$  보유골드  " << gold << "\n";
}

void Character::GainExp(int amount)//경험치를 외부에서 받는다.
{
    Exp += amount;
    int oldlevel = level;//현재 레벨 복제
    int beforeHP = maxhealth;//현재 hp 복제
    
    int beforeattack = attack;//현재 공격력 복제
    

    std::cout << "\n -> 경험치 +" << amount << " 획득! " << "(현재 경험치: " << Exp << "/" << maxExp << ")\n";


    while (Exp >= maxExp && level < 10)//ui와 처리 분리
    {
        Exp -= maxExp;
        level++;

        // 성장값 
        maxhealth += level*20;
        attack += level*5;

        // 레벨업하면 체력 회복
        health = maxhealth;

        // 다음 레벨 요구 경험치 증가
        maxExp += 10;
    }

    if (level >= 10)//최대레벨 제한 버그 방지
    {
        level = 10;
      
    }


    if (level > oldlevel) //UI출현조건
    {
        std::cout << "\n레벨업 조건 충족\n";
        std::cout << "★☆★★☆★★☆★★☆★☆★★\n";
        std::cout << "★☆★ LEVEL UP★☆★\n";
        std::cout << "★☆★★☆★★☆★★☆★☆★★\n";
        std::cout << " -> Lv." << oldlevel << " -> Lv." << level << "\n";
        std::cout << " -> HP +" << (maxhealth - beforeHP) << " 공격력 +" << (attack - beforeattack) << " 증가!\n";
        std::cout << "\n스탯이 상승했습니다!\n";
        std::cout << "HP : " << beforeHP << " -> " << maxhealth << "\n";
        std::cout << "공격력 : " << beforeattack << " -> " << attack << "\n";
        
    }

    
}