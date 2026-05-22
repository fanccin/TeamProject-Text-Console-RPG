#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
using namespace std;

std::vector<Item*> GetShopItemList() {
    std::vector<Item*> shopItems;

    // 동적 할당(new)으로 포션을 생성해서 포인터 배열에 담아줍니다.
    shopItems.push_back(new HealthPotion("체력 포션", 50));
    shopItems.push_back(new AttackBoost("공격력 포션", 10));

    return shopItems;
}

bool compareByPrice(Item* a, Item* b) {
    if (a == nullptr || b == nullptr) return false;
    return a->getPrice() < b->getPrice(); // 오름차순 (싼 가격부터 정렬)
}