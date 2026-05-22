// TeamProject_TextRPG.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <format>
#include <vector>
#include "Character.h"
#include "Monster.h"
#include "BattleManager.h"

int main()
{   
    std::cout << "===== 띵조 RPG =====\n";
    std::cout << "플레이어의 이름을 알려주세요.\n";
    
    std::string name;
    std::cin >> name;

	//패배 후 게임 재시작 루프
	bool isGameRunning = true;
	while(isGameRunning){
		{
		// 전직 시스템
		std::cout << "\n\n============================================\n";
		std::cout << "< 전직 시스템 >\n";
		std::cout << name << "님, 직업을 선택해주세요!\n";
		std::cout << "1. 전사   2. 마법사   3. 도적   4. 궁수\n";
		std::cout << "============================================\n\n";

		Character* character = nullptr;

		bool isJobSelected = false;
		while (!isJobSelected) {
			{
			int choice;
			std::cout << "선택 : ";
			std::cin >> choice;
			//예외처리
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(99999, '\n');
				std::cout << "숫자만 입력해주세요!\n";
				continue;
			}
			if (choice < 1 || choice>4) {
				std::cout << "존재하지 않는 직업입니다. 다시 선택해주세요.\n";
				continue;
			}

			switch (choice) {
			case 1:
				character = new Warrior(name);
				std::cout << character->getJob() << "로 전직하였습니다.\n";
				isJobSelected = true;
				break;
			case 2:
				character = new Magician(name);
				std::cout << character->getJob() << "로 전직하였습니다.\n";
				isJobSelected = true;
				break;
			case 3:
				character = new Thief(name);
				std::cout << character->getJob() << "으로 전직하였습니다.\n";
				isJobSelected = true;
				break;
			case 4:
				character = new Archer(name);
				std::cout << character->getJob() << "로 전직하였습니다.\n";
				isJobSelected = true;
				break;
			default:
				std::cout << "존재하지 않는 직업입니다. 다시 선택해주세요.\n";
				continue;
			}
			}
		}

		BattleManager* manager = new BattleManager(character);
		std::cout << "====================\n";
		std::cout << "캐릭터가 생성되었습니다.\n\n\n";
    
		//캐릭터 정보 출력
		character->displayStatus();

		//캐릭터 생성 후 곧바로 전투 돌입
		std::cout << "!!!!!!!     WARNING     !!!!!!!\n";
		manager->startBattle();


		//전투 종료 후 분기
		if (character->getHealth() <= 0)
		{
			int gameOverChoice;
			// 패배 시
			while (true) {
				std::cout << "\n============================================\n";
				std::cout << "... You Died ...\n";
				std::cout << "1. 처음부터 재도전하기...\n";
				std::cout << "2. 게임 완전히 종료하기...\n";
				std::cout << "============================================\n";
				std::cout << "선택 : ";
				std::cin >> gameOverChoice;

				//예외 처리
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(99999, '\n');
					std::cout << "숫자만 입력해주세요.\n";
					continue;
				}
				if (gameOverChoice < 1 || gameOverChoice > 2) {
					std::cout << "없는 메뉴입니다. 다시 골라주세요.\n";
					continue;
				}
				break;
			}


			//다음 루프 전에 객체 파괴
			delete manager;
			delete character;

			if (gameOverChoice == 1) {
				std::cout << "처음으로 돌아가 직업을 다시 선택합니다...\n";
				continue;
			}
			else {
				std::cout << "게임을 종료합니다.\n";
				break;
			}
		}
		else
		{	
			int shopChoice;
			//승리 시
			while (true) {
				std::cout << "\n============================================\n";
				std::cout << "수상한 상인이 다가옵니다. 대화를 하시겠습니까?\n";
				std::cout << "1. 비밀스러운 거래   2. 전투 속행\n";
				std::cout << "============================================\n";
				std::cout << "선택 : ";
				std::cin >> shopChoice;

				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(99999, '\n');
					std::cout << "숫자만 입력해주세요.\n";
					continue;
				}

				if (shopChoice < 1 || shopChoice > 2) {
					std::cout << "없는 메뉴입니다. 1번이나 2번을 골라주세요.\n";
					continue;
				}

				break;
			}

			if (shopChoice == 1) {
				std::cout << "상인이 소름끼치게 웃으며 물건을 보여줍니다...\n";
				// 상점 기능
			}
			else {
				std::cout << "당신은 상인을 무시하고 바로 다음 전장을 향합니다...\n\n";
			}

			//BattleManager 객체만 파괴하고 캐릭터 객체는 유지
			delete manager;
		}
		

		
	}

        


    return 0;
}

