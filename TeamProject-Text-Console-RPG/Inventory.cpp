#include "Inventory.h"
#include <algorithm>

using namespace std;

Inventory::~Inventory() {
	for (Item* item : items_) {
		delete item; 
	}
	items_.clear();
}

void Inventory::AddItem(Item* item) {
	if (item == nullptr) return;
	items_.push_back(item);
	std::cout << "[" << item->getName() << "]를 인벤토리에 추가했습니다." << std::endl;
}

void Inventory::RemoveItem(int index) {
	if (index >= 0 && index < static_cast<int>(items_.size())) {
		delete items_[index]; // 메모리 해제
		items_.erase(items_.begin() + index); // 배열 칸 당기기
	}
}

void Inventory::UseItem(int index, Character* character) {
	if (index >= 0 && index < static_cast<int>(items_.size())) {
		// ⭕ 종류를 묻지도 따지지도 않고 부모의 약속(use)만 실행
		// C++ 컴퓨터가 알아서 진짜 알맹이(HealthPotion 혹은 AttackBoost)를 찾아갑니다.
		items_[index]->use(character);

		// 소모품이므로 사용 후 가방에서 제거 및 메모리 해제
		delete items_[index];
		items_.erase(items_.begin() + index);
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
		std::cout << "[" << i + 1 << "] " << items_[i]->getName() << std::endl;
	}
	std::cout << "=============================" << std::endl;
}