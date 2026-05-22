#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

class Character; // 전방 선언

class Item {
public:
    virtual std::string getName() = 0;                     // 순수 가상 함수 (이름 반환 강제)
    virtual void use(Character* character) = 0;            // 순수 가상 함수 (사용 기능 강제)
    virtual int getPrice() = 0;
};

std::vector<Item*> GetShopItemList();

bool compareByPrice(Item* a, Item* b);