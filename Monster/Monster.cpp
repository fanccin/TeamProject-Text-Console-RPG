#include "Monster.h"
#include <iostream>
#include <random>

using namespace std;


// Goblin 구현

Goblin::Goblin(int level) {
    name = "고블린";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> healthDist(level * 20, level * 30);
    uniform_int_distribution<int> attackDist(level * 5, level * 10);
    uniform_int_distribution<int> defenceDist(level * 5, level * 10);
    health = healthDist(gen);
    attack = attackDist(gen);
    defence = defenceDist(gen);
}

string Goblin::getName() const { return name; }
int Goblin::getHealth() const { return health; }
int Goblin::getAttack() const { return attack; }
int Goblin::getDefence() const { return defence; }

void Goblin::takeDamage(int damage) {
    int actualDamage = damage - defence;

    if (actualDamage < 0) {
        actualDamage = 0;
    }

    health -= actualDamage;

    if (health < 0) {
        health = 0;
    }
    cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! (남은 체력: " << health << ")" << endl;
}


// Orc 구현

Orc::Orc(int level) {
    name = "오크";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> healthDist(level * 20, level * 30);
    uniform_int_distribution<int> attackDist(level * 5, level * 10);
    uniform_int_distribution<int> defenceDist(level * 5, level * 10);
    health = healthDist(gen);
    attack = attackDist(gen);
    defence = defenceDist(gen);
}

string Orc::getName() const { return name; }
int Orc::getHealth() const { return health; }
int Orc::getAttack() const { return attack; }
int Goblin::getDefence() const { return defence; }

void Orc::takeDamage(int damage) {
    int actualDamage = damage - defence;

    if (actualDamage < 0) {
        actualDamage = 0;
    }

    health -= actualDamage;

    if (health < 0) {
        health = 0;
    }
    cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! (남은 체력: " << health << ")" << endl;
}


// Troll 구현

Troll::Troll(int level) {
    name = "트롤";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> healthDist(level * 20, level * 30);
    uniform_int_distribution<int> attackDist(level * 5, level * 10);
    uniform_int_distribution<int> defenceDist(level * 5, level * 10);
    health = healthDist(gen);
    attack = attackDist(gen);
    defence = defenceDist(gen);
}

string Troll::getName() const { return name; }
int Troll::getHealth() const { return health; }
int Troll::getAttack() const { return attack; }
int Goblin::getDefence() const { return defence; }

void Troll::takeDamage(int damage) {
    int actualDamage = damage - defence;

    if (actualDamage < 0) {
        actualDamage = 0;
    }

    health -= actualDamage;

    if (health < 0) {
        health = 0;
    }
    cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! (남은 체력: " << health << ")" << endl;
}


// Slime 구현

Slime::Slime(int level) {
    name = "슬라임";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> healthDist(level * 20, level * 30);
    uniform_int_distribution<int> attackDist(level * 5, level * 10);
    uniform_int_distribution<int> defenceDist(level * 5, level * 10);
    health = healthDist(gen);
    attack = attackDist(gen);
    defence = defenceDist(gen);
}

string Slime::getName() const { return name; }
int Slime::getHealth() const { return health; }
int Slime::getAttack() const { return attack; }
int Goblin::getDefence() const { return defence; }

void Slime::takeDamage(int damage) {
    int actualDamage = damage - defence;

    if (actualDamage < 0) {
        actualDamage = 0;
    }

    health -= actualDamage;

    if (health < 0) {
        health = 0;
    }
    cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! (남은 체력: " << health << ")" << endl;
}