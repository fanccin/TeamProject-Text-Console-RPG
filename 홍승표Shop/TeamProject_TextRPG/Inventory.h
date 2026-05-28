#pragma once
#include <vector>
#include "Item.h"

class Character;

class Inventory
{
private:
	std::vector<Item*> items_;
public:
    ~Inventory();
    
    void AddItem(std::string itemType, std::string name, int value, int price);              // 가방에 아이템 추가
    void RemoveItem(int index);           // 가방에서 아이템 영구 제거 (버리기/판매)
    void UseItem(int index, Character* character); // 가상 함수 버프 발동!

    int GetSize() const { return static_cast<int>(items_.size()); }
    void ShowInventory() const;           // 가방 목록 출력

                   // 가방에 아이템이 총 몇 개 있는지 확인
    int GetItemPrice(int index) const;
};

