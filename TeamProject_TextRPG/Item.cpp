#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
using namespace std;

std::vector<Item*> GetShopItemList() {
    std::vector<Item*> shopItems;

    return shopItems;
}

bool compareByPrice(Item* a, Item* b) {
    if (a == nullptr || b == nullptr) return false;
    return a->getPrice() < b->getPrice(); // 오름차순 (싼 가격부터 정렬)
}