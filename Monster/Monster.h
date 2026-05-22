#pragma once
#include <string>

using namespace std;

// [인터페이스] Monster

class Monster {
public:
    virtual ~Monster() = default; // 가상 소멸자

    virtual string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getAttack() const = 0;
    virtual int getDefence() const = 0;
    virtual void takeDamage(int damage) = 0;
};


// [구현 클래스 선언] Goblin, Orc, Troll, Slime

class Goblin : public Monster {
private:
    string name;
    int health;
    int attack;
    int defence;

public:
    Goblin(int level);
    string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    int getDefence() const override;
    void takeDamage(int damage) override;
};

class Orc : public Monster {
private:
    string name;
    int health;
    int attack;
    int defence;

public:
    Orc(int level);
    string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    int getDefence() const override;
    void takeDamage(int damage) override;
};

class Troll : public Monster {
private:
    string name;
    int health;
    int attack;
    int defence;

public:
    Troll(int level);
    string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    int getDefence() const override;
    void takeDamage(int damage) override;
};

class Slime : public Monster {
private:
    string name;
    int health;
    int attack;
    int defence;

public:
    Slime(int level);
    string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    int getDefence() const override;
    void takeDamage(int damage) override;
};