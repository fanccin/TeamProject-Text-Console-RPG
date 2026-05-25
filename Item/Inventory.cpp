#include "Inventory.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Weapon.h"
#include "Armor.h"
#include <algorithm>

using namespace std;

Inventory::~Inventory() {
	for (Item* item : items_) {
		delete item; 
	}
	items_.clear();
}

void Inventory::AddItem(std::string itemType, std::string name, int value, int price) {
	Item* CreatedItem = nullptr;

	if (itemType == "Health") {
		CreatedItem = new HealthPotion(name, value, price);
	}
	else if (itemType == "Attack") {
		CreatedItem = new AttackBoost(name, value, price);
	}
	else if (itemType == "Weapon") {
		CreatedItem = new Weapon(name, value, price);
	}
	else if (itemType == "Armor") {
		CreatedItem = new Armor(name, value, price);
	}
	if (CreatedItem == nullptr) {
		std::cout << "[에러] 알 수 없는 아이템 타입입니다: " << itemType << std::endl;
		return;
	}
	items_.push_back(CreatedItem);
}

void Inventory::RemoveItem(int index) {
	if (index >= 0 && index < static_cast<int>(items_.size())) {
		delete items_[index]; // 메모리 해제
		items_.erase(items_.begin() + index); // 배열 칸 당기기
	}
}

void Inventory::UseItem(int index, Character* character) {
	if (index >= 0 && index < static_cast<int>(items_.size())) {

		items_[index]->use(character);

		if (items_[index]->isConsumable()) {
			delete items_[index];
			items_.erase(items_.begin() + index);
		}
		else {
			items_.erase(items_.begin() + index);
		}
	}
	else {
		std::cout << "가방에 아이템이 없습니다." << std::endl;
	}
}

void Inventory::ShowInventory() const {
	cout << "\n========= [인벤토리] =========" << endl;
	if(items_.empty()) {
		cout << "인벤토리가 비어 있습니다." << endl;
		cout << "==================================" << endl;
		return;
	}
	for (size_t i = 0; i < items_.size(); ++i) {
		std::cout << "[" << i+1 << "] " << items_[i]->getName() << "(G" << items_[i]->getPrice() << ")" << std::endl;
	}
	std::cout << "=============================" << std::endl;
}