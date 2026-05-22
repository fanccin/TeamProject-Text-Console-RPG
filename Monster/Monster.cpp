#include "Monster.h"
#include <random>

using namespace std;

Goblin::Goblin(int level) {
    name = "고블린";
    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<int> hDist(level * 20, level * 30);
    uniform_int_distribution<int> aDist(level * 5, level * 10);
    uniform_int_distribution<int> dDist(level * 5, level * 10);
    health = hDist(gen); 
    attack = aDist(gen); 
    defence = dDist(gen);
}

Orc::Orc(int level) {
    name = "오크";
    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<int> hDist(level * 20, level * 30);
    uniform_int_distribution<int> aDist(level * 5, level * 10);
    uniform_int_distribution<int> dDist(level * 5, level * 10);
    health = hDist(gen); 
    attack = aDist(gen); 
    defence = dDist(gen);
}

Troll::Troll(int level) {
    name = "트롤";
    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<int> hDist(level * 20, level * 30);
    uniform_int_distribution<int> aDist(level * 5, level * 10);
    uniform_int_distribution<int> dDist(level * 5, level * 10);
    health = hDist(gen); 
    attack = aDist(gen); 
    defence = dDist(gen);
}

Slime::Slime(int level) {
    name = "슬라임";
    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<int> hDist(level * 20, level * 30);
    uniform_int_distribution<int> aDist(level * 5, level * 10);
    uniform_int_distribution<int> dDist(level * 5, level * 10);
    health = hDist(gen); 
    attack = aDist(gen); 
    defence = dDist(gen);
}