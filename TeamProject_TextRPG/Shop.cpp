#include <string>
#include <vector>
#include "Shop.h"
#include <iostream>
#include "Character.h"
#include "Inventory.h"
#include "LogManager.h"




void Shop::showShopItem() const {
    for (size_t i = 0; i < shopItems.size(); ++i) {
        std::cout << i + 1 << ". " << shopItems[i].name
            << " | 효과: +" << shopItems[i].value
            << " | 가격: " << shopItems[i].price << " G\n";
    }
}

void Shop::enterShop(Character* character) {
    if (character == nullptr) return;

    while (true) {
        int choice;
        std::cout << "수상한 상인 : 용사여, 잠깐 물건 좀 보지 않겠나 ...?\n\n";
        std::cout << "=== 보유 골드 : " << character->getGold() << "G  ===\n";
        std::cout << "1. 아이템 구매   2. 아이템 판매   3. 나가기\n";
        std::cout << "0. 캐릭터 상태 확인\n";
        std::cout << "==============================\n";
        std::cout << "선택 : ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(99999, '\n');
            std::cout << "숫자만 입력하세요!\n";
            continue;
        }

        if (choice == 3) {
            std::cout << "또 봅세 ...\n";
            break;
        }
        else if (choice == 1) {
            buyItem(character);
        }
        else if (choice == 2) {
            sellItem(character);
        }
        else if (choice == 0) {
            LogManager::GetInstance().PrintCharacterInfo(character);
        }
        else {
            std::cout << "없는 메뉴입니다.\n";
        }
    }
}



void Shop::buyItem(Character* character) {
    while (true) {
        std::cout << "\n------------------------------\n";
        showShopItem();
        std::cout << "\n------------------------------\n";
        std::cout << "=== 현재 보유 골드 : " << character->getGold() << "G ===\n";
        int choice;
        std::cout << "구매할 아이템 번호 (뒤로가기 : 0) : ";
        std::cin >> choice;

        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(99999, '\n');
            std::cout << "숫자를 입력하세요.\n";
            continue;
        }
        if (choice == 0) {
            break;
        }
        if (choice < 0 || choice > static_cast<int>(shopItems.size())) {
            std::cout << "없는 메뉴입니다 ...\n";
            continue;
        }

        ShopItem targetItem = shopItems[choice - 1];
        int price = targetItem.price;

        // 골드 체크
        if (character->getGold() < price) {
            std::cout << "골드가 부족합니다 ...\n";
            continue;
        }

        character->setGold(character->getGold() - price);
        character->getInventory()->AddItem(targetItem.type, targetItem.name, targetItem.value, targetItem.price);
        std::cout << targetItem.name << "을(를) 구입하여 가방에 넣었습니다 ...\n";
    }
}

void Shop::sellItem(Character* character) {
    if (character == nullptr) return;

    // 판매 루프
    while (true) {
        std::cout << "\n------------------------------\n";
        // 인벤토리 민 골드 조회
        character->getInventory()->ShowInventory();
        std::cout << "=== 현재 보유 골드 : " << character->getGold() << "G ===\n";

        if (character->getInventory()->GetSize() == 0) {
            std::cout << "판매할 물건이 없습니다 ...\n";
            break;
        }

        int choice;
        std::cout << "판매할 아이템 번호 (뒤로 가기 : 0) : ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(99999, '\n');
            std::cout << "숫자를 입력하세요.\n";
            continue;
        }
        if (choice == 0) {
            break;
        }
        if (choice < 1 || choice > character->getInventory()->GetSize()) {
            std::cout << "잘못된 입력입니다 ...\n";
            continue;
        }

        Item* userItem = character->getInventory()->getItem(choice - 1);

        // getPrice() 는 Inventory의 부모인 Item에 존재하는 순수 가상 함수
        if (userItem != nullptr) {
            int originPrice = userItem->getPrice();
            int sellPrice = (originPrice * 6) / 10; // 60% 정수 연산

            // 골드 획득 및 가방에서 제거
            character->setGold(character->getGold() + sellPrice);
            character->getInventory()->RemoveItem(choice - 1);

            std::cout << "아이템을 판매하여 " << sellPrice << " G를 획득했습니다 ... (원가의 60%)\n";
        }
    }
}
