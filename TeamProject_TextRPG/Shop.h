#pragma once
#include <string>
#include <vector>

class Character;
class Inventory;
class Item;
class Weapon;
class Armor;
class Healpotion;
class AttackBoost;

class Shop {

public :
	struct ShopItem {
		std::string type;
		std::string name;
		int value;
		int price;
	};

private :
	std::vector<ShopItem> shopItems;



public:
	Shop() {
		shopItems.push_back({ "Health", "소형 체력 포션", 30, 10 });
		shopItems.push_back({ "Health", "중형 체력 포션", 60, 25 });
		shopItems.push_back({ "Health", "엘릭서", 100, 60 });
		shopItems.push_back({ "Attack", "전투 자극제", 5, 20 });
		shopItems.push_back({ "Attack", "힘의 물약", 10, 40 });
		shopItems.push_back({ "Weapon", "패도군주의 가시대검", 18, 60 });
		shopItems.push_back({ "Weapon", "영혼수확자의 서리낫", 20, 70 });
		shopItems.push_back({ "Weapon", "차원 왜곡의 중력지팡이", 50, 200 });
		shopItems.push_back({ "Armor", "칠흑기사단 정예갑옷", 40, 160 });
		shopItems.push_back({ "Armor", "황혼의 방랑자 가죽코트", 60, 250 });
	}
	~Shop() { ; }

	void enterShop(Character* character); // 상점 루프
	void showShopItem() const; // 판매 물품 출력
	void buyItem(Character* character); // 구매
	void sellItem(Character* character); // 판매
};