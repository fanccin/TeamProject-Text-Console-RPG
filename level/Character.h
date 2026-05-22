//Characters.h

#pragma once
#include<string>

class Character //방어와 MP없음.
{
public:
    Character(std::string name, int level, int health, int maxhealth, int attack, int Exp, int maxExp, int gold);

    int getlevel();
    void setlevel(int _level);
    int gethealth();
    void sethealth(int _health);
    int getmaxhealth();
    void setmaxhealth(int _maxhealth);
    int getattack();
    void setattack(int _attack);
    int getExp();
    void setExp(int _Exp);
    int getmaxExp();
    void setmaxExp(int _maxExp);
    void GainExp(int amount);
    //    int getgold(); //골드를 아이템에 넣을지 캐릭터에 넣을지 확인 
    //    void setgold(int _gold); //상점 시스템까지 생각하면 아이템?

private:
    std::string name;
    int level; //레벨업 파트 받아서 가져오기.
    int health;
    int maxhealth;
    int attack;
    int Exp;
    int maxExp;
    int gold;
    //vector<Item* > inventory; //아이템 파트 받아서 가져오기.
};
