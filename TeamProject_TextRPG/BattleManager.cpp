#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "Inventory.h"

#include <iostream>
#include <string>
#include "Random.h"
#include "Item.h"
#include "ItemDrop.h"
#include "LogManager.h"





Monster* BattleManager::generateMonster(int level) 
{

	if (isBoss) //보스생성
	{
		LogManager::GetInstance().PrintBossAppear();
		return new BossMonster(level);
	}

	int monsterProbability = RandomMt19937<int>(0,99);

	if (monsterProbability <= 40) return new Slime(level);
	else if (monsterProbability <= 75) return new Goblin(level);
	else if (monsterProbability <= 95) return new Orc(level);
	else return new Troll(level);

}
void BattleManager::startBattle()
{
	std::cout << "!!!!!   $T$  WARNING$/T$     !!!!!\n\n";
	//몬스터 생성
	//캐릭터 레벨에 따른 몬스터 레벨 스케일링
	Monster* monster = generateMonster(character->getLevel());

	//몬스터 정보 출력
	LogManager::GetInstance().PrintMonsterAppear(monster->getName(), monster->getHealth(), monster->getAttack(), monster->getDefense());

	//전투 루프
	while (character->getHealth() > 0 && monster->getHealth() > 0)
	{
		//===============플레이어 턴====================
		std::cout << "\n[" << character->getName() << "의 턴]\n";
		std::cout << "\n주사위를 굴렸습니다 ...\n";
		int playerRoll = RandomMt19937<int>(1, 100);

		//아이템 사용 선택지
		if (playerRoll <= 20) {
			{
				bool isItemUsed = false;
				while (!isItemUsed) {
					int choice;
					std::cout << "\n아이템을 사용합니다 ...\n";

					if (character->getInventory()->GetSize() == 0) {
						std::cout << "가방을 뒤졌으나 아무것도 없었습니다 ...\n\n";
						break;
					}

					//인벤토리 보여주기
					character->getInventory()->ShowInventory();
					std::cout << "\n사용할 아이템 : \n";
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
						LogManager::GetInstance().PrintCharacterInfo(character);
						continue;
					}

					if (choice < 1 || choice > character->getInventory()->GetSize()) {
						std::cout << "잘못된 입력입니다. 다시 입력하세요.\n";
						continue;
					}
					
					character->getInventory()->UseItem(choice, character);
					isItemUsed = true;

					//아이템 사용 후
					LogManager::GetInstance().PrintCharacterInfo(character);
				}
			}
		}
		//기본 공격
		else if (playerRoll <= 60) {
			int damageType = 1;
			int actualDamage = monster->takeDamage(character->getAttack());
			LogManager::GetInstance().PrintAttackLog(monster->getName(), actualDamage, monster->getHealth(), damageType);
		}
		//스킬 사용
		else if (playerRoll <= 90) {
			int damageType = 2;
			int actualDamage = monster->takeDamage(character->skillAttack());
			LogManager::GetInstance().PrintAttackLog(monster->getName(), actualDamage, monster->getHealth(), damageType);
		}
		//치명타 공격(스킬 데미지 2배)
		else {
			int damageType = 3;
			int actualDamage = monster->takeDamage(character->skillAttack()*2);
			LogManager::GetInstance().PrintAttackLog(monster->getName(), actualDamage, monster->getHealth(), damageType);
		}

		//몬스터 사망 시 전투 종료
		if (monster->getHealth() <= 0) {
			break;
		}

		//================몬스터 턴====================
		std::cout << "\n[" << monster->getName() << "의 턴]\n";
		int monsterRoll = RandomMt19937<int>(1, 100);

		//기본 공격
		if (monsterRoll <= 90) {
			{
				bool isCrit = false;
				int actualDamage = character->takeDamage(monster->getAttack());
				LogManager::GetInstance().PrintPlayerDamagedLog(monster->getName(), actualDamage, character->getHealth(), isCrit);
			}
		}
		//치명타 공격(데미지 2배)
		else {
			{
			bool isCrit = true;
			int actualDamage = character->takeDamage(monster->getAttack());
			LogManager::GetInstance().PrintPlayerDamagedLog(monster->getName(), actualDamage, character->getHealth(), isCrit);
			}
		}

	}

	//전투 결과 정산
	//전투 종료 후 공격력 버프 꺼짐
	character->clearBuff();

	//승리 시
	if (character->getHealth() > 0) {
		{
			//몬스터 처치 기록
			LogManager::GetInstance().RecordKill(monster->getName());

			// 경험치 획득 로그
			character->GainExp(50);

			// 골드 10~20 범위 랜덤 획득 / 로그
			int rewardGold = RandomMt19937<int>(10, 20);
			character->setGold(character->getGold() + rewardGold);
			LogManager::GetInstance().PrintGoldReward(rewardGold, character->getGold());

			// 보상 3: 30% 확률로 랜덤 아이템 획득
			ItemDrop item;
			item.itemDrop(character);

			std::cout << "\n";
			delete monster;

			//보스 클리어 체크
			if (isBoss)
			{
				isBossCleared = true;
			}

			return;
		}
	}
}
