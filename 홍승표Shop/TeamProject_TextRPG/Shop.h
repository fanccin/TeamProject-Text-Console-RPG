#pragma once



#include <vector>

#include <string>

#include "Item.h"

#include "Character.h"

#include "Inventory.h"



struct ShopItem

{

    std::string type; // "Health", "Attack", "Weapon", "Armor" 등

    std::string name; // 아이템 이름

    int value;   // 효과 수치 (체력 회복량, 공격력 증가량 등) 

    int price;   // 아이템 가격(고정)

};



class Shop

{

private:

    std::vector<Item*>goods;



    void BuyMenu(Character* player, Inventory* inventory);  // 아이템 구매 메뉴

    void SellMenu(Character* player, Inventory* inventory); // 아이템 판매 메뉴



public:

    Shop();

    ~Shop();



    // 상점 메인 진입 함수 (main.cpp에서 호출)

    void EnterStore(Character* player, Inventory* inventory);
};