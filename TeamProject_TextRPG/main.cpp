// TeamProject_TextRPG.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>
#include "Character.h"
#include "Monster.h"
#include "BattleManager.h"
#include "LogManager.h"
#include "Shop.h"

#include <chrono>
#include <thread>



class DelayStreamBuf : public std::streambuf {
private:
	std::streambuf* sbuf;
	bool typingMode = false; //한글자씩 타이핑
	bool skipMode = false;
	std::string tagBuffer = ""; //특수 명령어 태그 감지
public:
	DelayStreamBuf(std::streambuf* originalBuf) : sbuf(originalBuf) {}
protected:
	// 콘솔에 문자가 출력될 때 실행하는 함수
	int overflow(int c) override {
		if (c == EOF) return EOF;

		// 태그 입력받기
		if (c == '$' && tagBuffer.empty()) {
			tagBuffer = "$";
			return c;
		}
		if (!tagBuffer.empty()) {
			tagBuffer += static_cast<char>(c);

			// 태그 닫을때 해석
			if (c == '$') {
				if (tagBuffer == "$D$") { // D : 1초 딜레이
					sbuf->pubsync();
					std::this_thread::sleep_for(std::chrono::milliseconds(750));
				}
				else if (tagBuffer == "$T$") { // T : 글자단위 출력모드 on
					typingMode = true;
				}
				else if (tagBuffer == "$/T$") { // /T : 글자단위 출력모드 off
					typingMode = false;
				}
				else if (tagBuffer == "$S$") {
					skipMode = true;
				}
				else if (tagBuffer == "$/S$") {
					skipMode = false;
				}
				tagBuffer = "";
				return c;
			}

			// 예외처리
			if (tagBuffer.length() > 5) {
				for (char ch : tagBuffer) sbuf->sputc(ch);
				tagBuffer = "";
			}
			return c;
		}
		// 화면에 문자 출력
		int result = sbuf->sputc(c);

		if (skipMode) {
			return result;
		}

		// 출력 연출 분기
		if (typingMode) {
			// 글자단위 모드 : 한 글자 나올 때마다 미세하게 정지
			// 한글 깨짐 방지->멀티바이트(음수) 체크 후 정지
			if (c > 0 || (c < 0 && tagBuffer.empty())) {
				sbuf->pubsync();
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
		
		// 출력한 문자가 줄바꿈(\n)이면 0.2초 정지 및 화면 갱신
		if (c == '\n') {
			sbuf->pubsync(); // 즉시 화면에 밀어냄(flush)
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		return result;
	}
};




int main()
{

	// cout 리모컨 교체
	DelayStreamBuf delayBuf(std::cout.rdbuf());
	std::cout.rdbuf(&delayBuf);

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

		break;
	}

	// 전체 게임의 실행 여부를 제어하는 플래그
	bool isGameRunning = true;

	//보스 젠용 트리거
	bool bossSpawned = false;

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

		std::cout << "===================================$D$\n\n";
		std::cout << "캐릭터가 생성되었습니다.\n";
		LogManager::GetInstance().PrintCharacterInfo(character);

		// 캐릭터 생존 상태에서 무한 전투 루프
		bool isCharacterAlive = true;

		while (isCharacterAlive) {

			//보스 등장조건 체크
			if (!bossSpawned && character->getLevel() >= 10)
			{
				bossSpawned = true;
			}

			// 매 판 새로운 매니저를 생성하여 몬스터 리셋 후 전투 돌입
			BattleManager* manager = new BattleManager(character, bossSpawned);

			manager->startBattle();

			// 보스를 클리어했다면
			if (manager->isBossBattle() && manager->isBossClearedResult())
			{
				LogManager::GetInstance().PrintGameClear();
				LogManager::GetInstance().PrintKill();
				LogManager::GetInstance().ShowCredits();
												

				delete manager;
				delete character;

				isGameRunning = false;

				break;
			}

			// 전투 종료 후 분기 처리
			if (character->getHealth() <= 0) {
				// 패배 분기
				int gameOverChoice;
				while (true) {
					std::cout << "\n============================================\n";
					std::cout << "$T$... You Died ...$/T$\n";
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
					isGameRunning = false;   // 전체 게임 종료
				}
			}
			else {
				// [승리 분기]
				int shopChoice;
				while (true) {
					std::cout << "\n$D$============================================\n";
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
						LogManager::GetInstance().PrintCharacterInfo(character);
						continue;
					}
					if (shopChoice < 1 || shopChoice > 2) {
						std::cout << "없는 메뉴입니다. 다시 골라주세요.\n";
						continue;
					}
					break;
				}

				if (shopChoice == 1) {
					std::cout << "상인이 음흉하게 웃으며 물건을 보여줍니다...$D$\n";
					{
						// 일반 지역변수로 사용
						Shop merchandise;
						merchandise.enterShop(character);
						std::cout << "\n\n당신은 상인을 뒤로하고 바로 다음 전장을 향합니다...$D$\n\n";
					}
				}
				else {
					std::cout << "당신은 상인을 뒤로하고 바로 다음 전장을 향합니다...\n\n";
				}

				// battleManager 파괴
				// character 객체는 유지
				delete manager;
			}
		}
	} //  isGameRunning 루프 

	return 0;
}