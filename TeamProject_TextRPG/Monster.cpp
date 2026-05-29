#include "Monster.h"
#include "Random.h"
#include <iostream>

using namespace std;

Goblin::Goblin(int level) {
    name = "고블린";
    health = RandomMt19937<int>(level * 20, level * 30);
    attack = RandomMt19937<int>(level * 5, level * 10);
    defense = RandomMt19937<int>(level * 3, level * 7);
}

Orc::Orc(int level) {
    name = "오크";
    health = RandomMt19937<int>(level * 25, level * 35);
    attack = RandomMt19937<int>(level * 8, level * 14);
    defense = RandomMt19937<int>(level * 4, level * 8);
}

Troll::Troll(int level) {
    name = "트롤";
    health = RandomMt19937<int>(level * 40, level * 60);
    attack = RandomMt19937<int>(level * 10, level * 18);
    defense = RandomMt19937<int>(level * 5, level * 10);
}

Slime::Slime(int level) {
    name = "슬라임";
    health = RandomMt19937<int>(level * 15, level * 20);
    attack = RandomMt19937<int>(level * 3, level * 6);
    defense = RandomMt19937<int>(level * 1, level * 3);
}

BossMonster::BossMonster(int level)
{
    name = "드래곤";
    health = RandomMt19937<int>(level * 100, level * 150);
    attack = RandomMt19937<int>(level * 25, level * 45);
    defense = RandomMt19937<int>(level * 12, level * 25);
}
