#include "Item.h"
// 플레이어 include "파일명.h"가 들어와야함
//#include "Character.h"
using namespace std;

// 체력 포션 구현
HealthPotion::HealthPotion(std::string n, int restore)
    : name(n), healthRestore(restore) {
}

std::string HealthPotion::getName() {
    return name;
}

void HealthPotion::use(Character* character) {
    if (character == nullptr) return;

    // 캐릭터 담당 팀원의 함수를 써서 체력 회복
    // 캐릭터 담당 팀원의 함수로 고칠 필요성이 있음
    int currentHp = character->gethealth();
    character->sethealth(currentHp + healthRestore);
	cout << "" << name << "을 사용하여 체력을 " << healthRestore << " 회복했습니다!" << endl;
}

// 공격력 증가 아이템 구현
AttackBoost::AttackBoost(std::string n, int increase)
    : name(n), attackIncrease(increase) {
}

std::string AttackBoost::getName() {
    return name;
}

void AttackBoost::use(Character* character) {
    if (character == nullptr) return;

    // 캐릭터 담당 팀원의 함수를 써서 공격력 버프 부여
    // 캐릭터 담당 팀원의 함수로 고칠 필요성이 있음
    int currentAttack = character->getattack();
    character->setattack(currentAttack + attackIncrease);
	cout << "" << name << "을 사용하여 공격력을 " << attackIncrease << " 증가시켰습니다!(이번 전투 동안만 유지됩니다)" << endl;
	cout << "현재 공격력: " << character->getattack() << endl;
}

std::vector<Item*> GetShopItemList() {
    std::vector<Item*> shopItems;

    // 동적 할당(new)으로 포션을 생성해서 포인터 배열에 담아줍니다.
    shopItems.push_back(new HealthPotion("체력 포션", 50));
    shopItems.push_back(new AttackBoost("공격력 포션", 10));

    return shopItems;
}
