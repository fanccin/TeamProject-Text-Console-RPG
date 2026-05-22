#include <iostream>
#include "LogManager.h"

using namespace std;

// 0. 캐릭터 생성 및 정보 출력 로그 정의
void LogManager::PrintCharacterInfo(const string& playerName, int level, int hp, int attack)
{
    cout << "캐릭터 " << playerName << " 생성 완료! 레벨: " << level
        << ", 체력: " << hp << ", 공격력: " << attack << endl;
}

// 1.몬스터 등장, 공격 및 피해 로그 정의
void LogManager::PrintMonsterAppearAndAttack(const string& monsterName, int monsterMaxHp, int monsterAtk,
    const string& attackerName, const string& targetName,
    int damage,  int currentHp)
{
    // 몬스터 등장 문구 출력
    cout << "몬스터 " << monsterName << " 등장! 체력: " << monsterMaxHp << ", 공격력: " << monsterAtk << endl;

    // 음수 체력 방지 보정
    int displayCurrentHp = (currentHp < 0) ? 0 : currentHp;

    // 공격 및 피해 로그를 곧바로 이어서 출력
    cout << attackerName << "가 " << targetName << "을 공격합니다! "
        << targetName << " 체력: " << displayCurrentHp << endl;
}

//2. 체력 +50(포션) : 현재 체력을 50 회복 형태로 출력
void LogManager::PrintPotionEffect(int healAmount)
{
    cout << "체력 +" << healAmount << "(포션) : 현재 체력을 " << healAmount << " 회복" << endl;
}

//3. 공격력 + 10: 해당 전투에만 효과 발휘 형태로 출력
void LogManager::PrintBattleBuffEffect(int statAmount)
{
    cout << "공격력 + " << statAmount << " : 해당 전투에만 효과 발휘" << endl;
}


// 4. 경험치,골드 및 경험치 획득 로그 정의 
void LogManager::PrintRewardLog(const string& playerName, int expAmount, int goldAmount, int currentExp, int maxExp, int currentGold)
{
    cout << playerName << "가 " << expAmount << " EXP와 " << goldAmount << " 골드를 획득했습니다. "
        << "현재 EXP: " << currentExp << "/" << maxExp << ", 골드: " << currentGold << endl;
}

// 5. 몬스터 처치 기록 누적 함수 (예시: Hero가 Goblin을 공격합니다! Goblin 처치!)
void LogManager::RecordKill(const string& monsterName)
{
	// 맵에 처치 수 누적
	killCounts[monsterName]++;

	// "몬스터이름 처치!" 로 출력 
	cout << monsterName << " 처치!" << endl;
}

// 6. 누적 처치 통계 출력 함수
void LogManager::PrintKill() const
{
    cout << "\n=========================================" << endl;
    cout << "             몬스터 처치 통계             " << endl;
    cout << "=========================================" << endl;

    if (killCounts.empty())
    {
        cout << " 처치한 몬스터가 없습니다." << endl;
    }
    else
    {
        for (const auto& pair : killCounts)
        {
            cout << "  " << pair.first << " : 총 " << pair.second << " 마리" << endl;
        }
    }

    cout << "=========================================\n" << endl;
}