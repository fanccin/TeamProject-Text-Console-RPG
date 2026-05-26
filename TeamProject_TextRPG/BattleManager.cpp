#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "Inventory.h"

#include <iostream>
#include <string>
#include "Random.h"
#include "Item.h"
#include "ItemDrop.h"




Monster* BattleManager::generateMonster(int level) 
{
	int monsterProbability = RandomMt19937<int>(0,99);

	if (monsterProbability <= 40) return new Slime(level);
	else if (monsterProbability <= 75) return new Goblin(level);
	else if (monsterProbability <= 95) return new Orc(level);
	else return new Troll(level);

}
void BattleManager::startBattle()
{
	//몬스터 생성
	//캐릭터 레벨에 따른 몬스터 레벨 스케일링
	Monster* monster = generateMonster(character->getLevel());

	std::cout << "몬스터 [" << monster->getName() << "] 등장...\n";
	//몬스터 정보 출력
	displayMonsterStatus(monster);
	//노도핑 공격력 백업
	int originalAttack = character->getAttack();

	//전투 루프
	while (character->getHealth() > 0 && monster->getHealth() > 0)
	{
		//===============플레이어 턴====================
		std::cout << "\n[" << character->getName() << "의 턴]\n";
		std::cout << "\n 주사위를 굴렸습니다 ...\n";
		int playerRoll = RandomMt19937<int>(1, 100);

		//아이템 사용 선택지
		if (playerRoll <= 20) {
			{
				bool isItemUsed = false;
				while (!isItemUsed) {
					int choice;
					std::cout << "\n 아이템을 사용합니다 ...\n";

					if (character->getInventory()->GetSize() == 0) {
						std::cout << "가방을 뒤졌으나 아무것도 없었습니다 ...\n";
						break;
					}

					//인벤토리 보여주기
					character->getInventory()->ShowInventory();
					std::cout << "\n 사용할 아이템 : \n";
					std::cout << "( 0. 캐릭터 상태 확인 )\n";
					
					//예외처리
					std::cin >> choice;
					if (std::cin.fail()) {
						std::cout << "숫자를 입력하세요.\n";
						std::cin.clear();
						std::cin.ignore(99999, '\n');
						continue;
					}
					if (choice == 0) {
						character->displayStatus();
						continue;
					}

					if (choice < 1 || choice > character->getInventory()->GetSize()) {
						std::cout << "잘못된 입력입니다. 다시 입력하세요.\n";
						continue;
					}
					character->getInventory()->UseItem(choice, character);
					isItemUsed = true;

					//아이템 사용 후
					character->displayStatus();
				}
			}
		}
		//기본 공격
		else if (playerRoll <= 60) {
			std::cout << "\n[" << monster->getName() << "]에게 기본 공격을 가합니다!\n";
			monster->takeDamage(character->getAttack());
		}
		//스킬 사용
		else if (playerRoll <= 90) {
			std::cout << "\n[" << monster->getName() << "]에게 스킬 공격을 가합니다!\n";
			monster->takeDamage(character->skillAttack());
		}
		//치명타 공격(스킬 데미지 2배)
		else {
			std::cout << "치명타!!!\n";
			std::cout << "\n[" << monster->getName() << "]에게 치명적인 공격을 가합니다!\n";
			monster->takeDamage(character->skillAttack() * 2);
		}

		//몬스터 사망 시 전투 종료
		if (monster->getHealth() <= 0) {
			//logger.RecordKill(monster->getName());
			break;
		}

		//================몬스터 턴====================
		std::cout << "\n[" << monster->getName() << "의 턴]\n";
		int monsterRoll = RandomMt19937<int>(1, 100);

		//기본 공격
		if (monsterRoll <= 90) {
			{
				int damage = (monster->getAttack() - character->getDefense());
				if (damage <= 0) damage = 1;
				character->setHealth(character->getHealth() - damage);
				std::cout << "\n[" << monster->getName() << "]에게 공격을 받았습니다 ...(데미지 : " << damage << ")\n";
				std::cout << "남은 체력 : " << character->getHealth() << ")\n";

			}
		}
		//치명타 공격(데미지 2배)
		else {
			int damage = (monster->getAttack() * 2 - character->getDefense());
			character->setHealth(character->getHealth() - damage);
			std::cout << monster->getName() << "이 공격을 준비합니다 ...\n";
			std::cout << "치명타!!!\n";
			std::cout << "\n[" << monster->getName() << "]에게 치명적인 공격을 받았습니다 ...(데미지 : " << damage << ")\n";
			std::cout << "남은 체력 : " << character->getHealth() << ")\n";
		}

	}

	//전투 결과 정산
	//전투 종료 후 공격력 버프 꺼짐
	character->setAttack(originalAttack);

	//승리 시
	if (character->getHealth() >= 0) {
		{
			std::cout << "\n 전투 승리! [" << monster->getName() << "]를 처치했습니다!\n";
			std::cout << "=========================================\n";

			// 보상 1: 경험치 50 고정 획득 (레벨업 연산은 캐릭터 내부 함수가 처리)
			character->GainExp(50);

			// 보상 2: 골드 10~20 범위 랜덤 획득
			int rewardGold = RandomMt19937<int>(10, 20);
			character->setGold(character->getGold() + rewardGold);
			std::cout << " 골드 +" << rewardGold << " G 획득! (현재 골드: " << character->getGold() << "G)\n";

			// 보상 3: 30% 확률로 랜덤 아이템 획득
			ItemDrop item;
			item.itemDrop(character);

			std::cout << "=========================================\n";
			delete monster;
		}
	}

}

void BattleManager::displayMonsterStatus(Monster* monster)
{
	std::cout << "\n========= [속성 상세정보] =========\n";
	std::cout << " 이름     : " << monster->getName() << std::endl;
	std::cout << " HP       : " << monster->getHealth() << std::endl;
	std::cout << " 공격력   : " << monster->getAttack() << std::endl;
	std::cout << " 방어력   : " << monster->getDefense() << std::endl;
	std::cout << "===================================\n";
}