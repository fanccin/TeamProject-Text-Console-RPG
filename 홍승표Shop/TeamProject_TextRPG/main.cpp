// TeamProject_TextRPG.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>
#include "Character.h"
#include "Monster.h"
#include "BattleManager.h"
#include "LogManager.h"

int main()
{
	std::cout << "===== 띵조 RPG =====\n";
	std::cout << "플레이어의 이름을 알려주세요.\n";
	std::cout << "이름 : ";

	std::string rawInput;
	std::string name;

	while (true) {
		//한 줄 통째로 읽어옴
		std::getline(std::cin, rawInput);

		//입력받은 문자열에서 공백(스페이스바, 탭 등) 제거
		name = "";
		for (char c : rawInput) {
			if (!std::isspace(static_cast<unsigned char>(c))) {
				name += c;
			}
		}

		//전부 공백일 경우 예외처리
		if (name.empty()) {
			std::cout << "이름은 최소 한 글자 이상 입력해야 합니다! 다시 입력해주세요.\n";
			std::cout << "이름 : ";
			continue;
		}

		break; // 완벽하게 필터링된 이름(`name`)을 가지고 루프 탈출!
	}

	// 전체 게임의 실행 여부를 제어하는 플래그
	bool isGameRunning = true;

	while (isGameRunning) {
		// 처음 시작 or 패배 시 진입하는 전직 시스템
		std::cout << "\n\n============================================\n";
		std::cout << "< 전직 시스템 >\n";
		std::cout << name << "님, 직업을 선택해주세요!\n";
		std::cout << "1. 전사   2. 마법사   3. 도적   4. 궁수\n";
		std::cout << "============================================\n\n";
				
		Character* character = nullptr;
		bool isJobSelected = false;

		while (!isJobSelected) {
			int choice;
			std::cout << "선택 : ";
			std::cin >> choice;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(99999, '\n');
				std::cout << "숫자만 입력해주세요!\n";
				continue;
			}
			if (choice < 1 || choice > 4) {
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

		std::cout << "====================\n";
		std::cout << "캐릭터가 생성되었습니다.\n\n\n";
		LogManager::GetInstance().PrintCharacterInfo(character);

		// 캐릭터 생존 상태에서 무한 전투 루프
		bool isCharacterAlive = true;

		while (isCharacterAlive) {
			// 매 판 새로운 매니저를 생성하여 몬스터 리셋 후 전투 돌입
			BattleManager* manager = new BattleManager(character);

			std::cout << "!!!!!!!     WARNING     !!!!!!!\n";
			manager->startBattle();

			// 전투 종료 후 분기 처리
			if (character->getHealth() <= 0) {
				// 패배 분기
				int gameOverChoice;
				while (true) {
					std::cout << "\n============================================\n";
					std::cout << "... You Died ...\n";
					std::cout << "1. 처음부터 재도전하기...\n";
					std::cout << "2. 게임 완전히 종료하기...\n";
					std::cout << "============================================\n";
					std::cout << "선택 : ";
					std::cin >> gameOverChoice;

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

				// character와 manager 둘다 파괴
				delete manager;
				delete character;

				if (gameOverChoice == 1) {
					std::cout << "처음으로 돌아가 직업을 다시 선택합니다...\n";
					isCharacterAlive = false; // 전투 루프를 탈출하여 상위 전직 루프로 이동
				}
				else {
					std::cout << "게임을 종료합니다.\n";
					isCharacterAlive = false;
					isGameRunning = false;    // 전체 게임 종료
				}
			}
			else {
				// [승리 분기]
				int shopChoice;
				while (true) {
					std::cout << "\n============================================\n";
					std::cout << "수상한 상인이 다가옵니다. 대화를 하시겠습니까?\n";
					std::cout << "1. 비밀스러운 거래   2. 다음 전투 속행\n";
					std::cout << "0. 캐릭터 상태 확인\n";
					std::cout << "============================================\n";
					std::cout << "선택 : ";
					std::cin >> shopChoice;

					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(99999, '\n');
						std::cout << "숫자만 입력해주세요.\n";
						continue;
					}
					if (shopChoice == 0) {
						character->displayStatus();
						continue;
					}
					if (shopChoice < 1 || shopChoice > 2) {
						std::cout << "없는 메뉴입니다. 다시 골라주세요.\n";
						continue;
					}
					break;
				}

				if (shopChoice == 1) {
					std::cout << "상인이 소름끼치게 웃으며 물건을 보여줍니다...\n";
					// TODO: 상점 기능 함수 호출 영역
				}
				else {
					std::cout << "당신은 상인을 무시하고 바로 다음 전장을 향합니다...\n\n";
				}

				// battleManager 파괴
				// character 객체는 유지
				delete manager;
			}
		}
	} //  isGameRunning 루프 

	return 0;
}