#pragma once
#include <string>
#include <iostream>

class Monster {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    virtual ~Monster() = default;

    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }

    virtual int takeDamage(int damage) {
        int actualDamage = damage - defense;
        if (actualDamage < 0) actualDamage = 0;

        health -= actualDamage;
        if (health < 0) health = 0;

        return actualDamage;
    }
};

class Goblin : public Monster {
public: Goblin(int level);
};

class Orc : public Monster {
public: Orc(int level);
};
class Troll : public Monster {
public: Troll(int level);
};
class Slime : public Monster {
public: Slime(int level);
};