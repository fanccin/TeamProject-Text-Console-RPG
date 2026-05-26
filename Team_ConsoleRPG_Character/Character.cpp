//Character.cpp

#include<iostream>
#include<string>
#include "Character.h"

using namespace std;

//생성자 - 초기값은 여기서.
Character::Character(std::string name)
{
    //초기 능력치 레벨 1, 초기 체력 200, 공격력 30, 경험치 0으로 시작.
    this->name = name;
    this->level = 1;
    this->health = 200; //현재체력
    this->maxhealth = 200; //최대체력
    this->mp = 50;
    this->maxmp = 50;
    this->attack = 30;
    this->defense = 30;
    this->gold = 0;
    this->exp = 0; //초기 경험치 0
    this->maxexp = 100;
    //    void 경험치(int 경험치)
    this-> inventory = new Inventory();// new : 실체를 메모리 타입으로 만드는 것.
}



//스탯 출력
void Character::displayStatus()
{
    cout<< "속성 상세정보\n";
    cout<< " " << getName() << "\n";
    cout<< " " << getLevel() << " /10\n";
    cout<< "S2 HP       " << getHealth() <<"\n";
    cout<< "MP        " << getMp() <<"\n";
    cout<< "X  공격력    " << getAttack() <<"\n";
    cout<< "[] 방어력    " << getDefense() <<"\n";
    cout<< "$  보유골드  " << getGold() <<"\n";
}
//패치내역 : getter/setter 정리에 따라, get의 함수값으로 불러오기.

//레벨 업
void Character::GainExp(int amount)//경험치를 외부에서 받는다.
{
    exp += amount;
    int oldlevel = level;//현재 레벨 복제
    int beforeHP = maxhealth;//현재 hp 복제
    
    int beforeattack = attack;//현재 공격력 복제
    

    std::cout << "\n -> 경험치 +" << amount << " 획득! " << "(현재 경험치: " << exp << "/" << maxexp << ")\n";


    while (exp >= maxexp && level < 10)//ui와 처리 분리
    {
        exp -= maxexp;
        level++;

        // 성장값 
        maxhealth += level*20;
        attack += level*5;

        // 레벨업하면 체력 회복
        health = maxhealth;

        // 다음 레벨 요구 경험치 증가
        maxexp += 10;
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


//Character::~Character(){} // 소멸자


//직업선택
Warrior::Warrior(std::string name)
    :Character(name)
{
    this->job = "전사";
    this->health += 50;
    this->maxhealth += 50;
    this->defense += 50;
    cout << "초보 탈락 전사 합격. (HP +50. 방어력 +50.)\n";
    cout << "공격 습득!\n";
    cout << "스킬 습득!\n";
}

int Warrior::SkillAttack() //이미 멤버변수로 받아왔으니, attack을 매개변수로 받아올 필요 없음.
{
    int damage = attack*2;
    
    //std::cout << "\n[" << monster->getName() << "]에게 스킬 공격을 가합니다!\n";
}


Magician::Magician(std::string name)
    :Character(name)
{
    this->job = "마법사";
    this->mp *= 2;
    this->maxmp *= 2;
    this->attack += 50;
    cout << "초보 탈락 법사 합격. (MP 2배. 공격 +50.)\n";
    cout << "공격 습득!\n";
    cout << "스킬 습득!\n";
}

int Magician::SkillAttack() //이미 멤버변수로 받아왔으니, attack을 매개변수로 받아올 필요 없음.
{
    int damage = attack*2;
    
    //std::cout << "\n[" << monster->getName() << "]에게 스킬 공격을 가합니다!\n";
}

Thief::Thief(std::string name)
    :Character(name)
{
    this->job = "Thief";
    this->health += 20;
    this->maxhealth += 20;
    this->attack += 20;
    cout << "초보 탈락 도적 합격. (HP +20. 공격 +20.)\n";
    cout << "공격 습득!\n";
    cout << "스킬 습득!\n";
}

int Thief::SkillAttack() //이미 멤버변수로 받아왔으니, attack을 매개변수로 받아올 필요 없음.
{
    int damage = attack*2;
    
    //std::cout << "\n[" << monster->getName() << "]에게 스킬 공격을 가합니다!\n";
}


Archer::Archer(std::string name)
    :Character(name)
{
    this->job = "Archer";
    this->attack *= 2;
    cout << "초보 탈락 궁수 합격. (공격 2배.)\n";
    cout << "공격 습득!\n";
    cout << "스킬 습득!\n";
}

int Archer::SkillAttack() //이미 멤버변수로 받아왔으니, attack을 매개변수로 받아올 필요 없음.
{
    int damage = attack*2;
    
    return damage;
    
    //std::cout << "\n[" << monster->getName() << "]에게 스킬 공격을 가합니다!\n";
}
