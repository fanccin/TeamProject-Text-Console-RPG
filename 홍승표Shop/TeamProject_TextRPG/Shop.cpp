#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Weapon.h"
#include "Armor.h"
#include <iostream>
#include <algorithm>
using namespace std;



//  타입, 이름, 효과수치(value), 가격(price) 순서

static const ShopItem shopDB[] = {

    { "Health", "소형 체력 포션", 30, 10 },
    { "Health", "중형 체력 포션", 60, 25 },
    { "Health", "엘릭서", 100, 60 },
    { "Attack", "전투 자극제", 5, 20 },
    { "Attack", "힘의 물약", 10, 40 },
    { "Weapon", "패도군주의 가시대검", 18, 60 },
    { "Weapon", "영혼수확자의 서리낫", 20, 70 },
    { "Weapon", "차원 왜곡의 중력지팡이", 50, 200 },
    { "Armor",  "칠흑기사단 정예갑옷", 40, 160 },
    { "Armor",  "황혼의 방랑자 가죽코트", 15, 80 }
};

static const size_t SHOP_DB_SIZE = sizeof(shopDB) / sizeof(shopDB[0]);

// 생성자: 물품 등록 및 가격 오름차순 정렬

Shop::Shop()
{

    for (size_t i = 0; i < SHOP_DB_SIZE; ++i)

    {
        const auto& info = shopDB[i];

        // 인벤토리의 AddItem 생성 규칙과 동일하게 (이름, 효과수치, 가격) 순으로 동적 할당합니다.

        if (info.type == "Health")

        {

            goods.push_back(new HealthPotion(info.name, info.value, info.price));

        }

        else if (info.type == "Attack")

        {

            goods.push_back(new AttackBoost(info.name, info.value, info.price));

        }

        else if (info.type == "Weapon")

        {

            goods.push_back(new Weapon(info.name, info.value, info.price));

        }

        else if (info.type == "Armor")

        {

            goods.push_back(new Armor(info.name, info.value, info.price));

        }

    }



    // 가격 오름차순 정렬

    sort(goods.begin(), goods.end(), Item::compareByPrice);

}



// 소멸자(제미나이가 이렇게 해야한다고 알려줌)

// 제미나이 : 상점 소멸자 가동 -> "상점이 사라지니 물건들을 정리하자!"

// 반복문 -> goods에 담긴 첫 번째 주소를 따라가서 delete 처리 -> virtual 덕분에 자식 객체(HealthPotion 등)가 메모리에서 깔끔하게 증발!

//반복 완료 -> 모든 아이템 알맹이들이 메모리에서 해제됨.

// 마무리(clear) -> 주소 목록이 적혀있던 goods 장부까지 싹 지워서 청소 끝!

Shop::~Shop()

{

    for (Item* item : goods)

    {

        if (item != nullptr) delete item;

    }

    goods.clear();

}



// 상점 메인 루프 진입 (main.cpp에서 호출됨)

void Shop::EnterStore(Character* player, Inventory* inventory)

{

    while (true)

    {

        cout << "\n============================================\n";

        cout << " 수상한 상인이 물건을 펼칩니다.\n";

        cout << " 보유 골드: " << player->getGold() << " G\n";

        cout << "--------------------------------------------\n";

        cout << " 1. 아이템 구매\n";

        cout << " 2. 아이템 판매\n";

        cout << " 3. 상점 나가기\n";

        cout << "============================================\n";

        cout << " 선택 : ";



        int choice;

        cin >> choice;



        if (cin.fail())

        {

            cin.clear();

            cin.ignore(99999, '\n');

            cout << "숫자만 입력 가능합니다.\n";

            continue;

        }



        if (choice == 1) BuyMenu(player, inventory);

        else if (choice == 2) SellMenu(player, inventory);

        else if (choice == 3)

        {

            cout << "상인이 기괴하게 웃으며 물건을 챙겨 떠납니다. 다음 전투로 향합니다.\n";

            break;

        }

        else

        {

            cout << "올바른 메뉴 번호를 선택해주세요.\n";

        }

    }

}



// 아이템 구매 메뉴

void Shop::BuyMenu(Character* player, Inventory* inventory)

{

    cout << "\n--- [ 아이템 구매 ] ---\n";

    for (size_t i = 0; i < goods.size(); ++i)

    {

        cout << "[" << i + 1 << "] " << goods[i]->getName()

            << " | 가격: " << goods[i]->getPrice() << " G\n";

    }

    cout << "[" << goods.size() + 1 << "] 뒤로가기\n";

    cout << "--------------------------------------------\n";

    cout << "구매할 아이템 번호 선택 : ";



    int choice;

    cin >> choice;



    if (cin.fail())

    {

        cin.clear();

        cin.ignore(99999, '\n');

        cout << "숫자만 입력 가능합니다.\n";

        return;

    }



    if (choice == goods.size() + 1) return; // 뒤로가기





    if (choice >= 1 && choice <= static_cast<int>(goods.size()))

    {

        Item* selected = goods[choice - 1];



        if (player->getGold() >= selected->getPrice())

        {

            player->setGold(player->getGold() - selected->getPrice());



            // DB에서 해당 아이템의 원래 타입과 효과 수치(value)를 찾아냅니다.

            string type = "Health";

            int value = 0;

            for (size_t i = 0; i < SHOP_DB_SIZE; ++i)

            {

                if (shopDB[i].name == selected->getName())

                {

                    type = shopDB[i].type;

                    value = shopDB[i].value;

                    break;

                }

            }



            inventory->AddItem(type, selected->getName(), value, selected->getPrice());



            cout << "->" << selected->getName() << "을(를) 구입했습니다!\n";

            cout << "-> 남은 골드: " << player->getGold() << " G\n";

        }

        else

        {

            cout << "골드가 부족합니다! (보유 골드: " << player->getGold() << " G)\n";

        }

    }

    else cout << "잘못된 번호입니다.\n";

}



// 아이템 판매 메뉴

void Shop::SellMenu(Character* player, Inventory* inventory)

{

    cout << "\n--- [ 아이템 판매 ] ---\n";

    inventory->ShowInventory(); // 가방 상태 출력



    int inventorySize = inventory->GetSize();

    if (inventorySize == 0)

    {

        return; // 가방이 비어있으면 자동 탈출

    }



    cout << "판매할 아이템 번호를 선택하세요 (0번 취소) : ";

    int choice;

    cin >> choice;



    if (cin.fail())

    {

        cin.clear();

        cin.ignore(99999, '\n');

        cout << "숫자만 입력 가능합니다.\n";

        return;

    }



    if (choice == 0) return;



    // 플레이어가 입력한 번호(1 ~ N)가 유효한지 검사

    if (choice >= 1 && choice <= inventorySize)

    {

        int targetIndex = choice - 1; // 내부 벡터용 0-based 인덱스로 보정



        // 아이템 가격을 인벤토리로부터 가져옵니다.

        int originalPrice = inventory-> GetItemPrice(targetIndex);

        int sellPrice = static_cast<int>(originalPrice * 0.6);
      
        player->setGold(player->getGold() + sellPrice);

        inventory->RemoveItem(targetIndex);

        cout << "판매가 완료되었습니다!" << sellPrice << " G를 받았습니다.\n";

        cout << "현재 보유 골드: " << player->getGold() << " G\n";
    }
   else cout << "올바르지 않은 가방 슬롯 번호입니다.\n";
}