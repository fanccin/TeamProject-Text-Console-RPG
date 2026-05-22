#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

class Character; // 전방 선언

class Item {
public:
    virtual ~Item() = default; // 가방에서 안전하게 삭제하기 위한 가상 소멸자

    virtual std::string getName() = 0;                     // 순수 가상 함수 (이름 반환 강제)
    virtual void use(Character* character) = 0;            // 순수 가상 함수 (사용 기능 강제)
};

// 자식 클래스 : 체력 포션
class HealthPotion : public Item {
private:
    std::string name;
    int healthRestore; // 회복량 수치

public:
    HealthPotion(std::string n = "체력 포션", int restore = 50);

    std::string getName() override;
    void use(Character* character) override;
};

// 자식 클래스 : 공격력 증가 아이템
class AttackBoost : public Item {
private:
    std::string name;
    int attackIncrease; // 공격력 증가 수치

public:
    AttackBoost(std::string n = "공격력 포션", int increase = 10);

    std::string getName() override;
    void use(Character* character) override; // 캐릭터 공격력을 올리는 알맹이
};

std::vector<Item*> GetShopItemList();