#include <iostream>
#include "LogManager.h"
#include "Character.h"

#include <chrono>
#include <thread>

using namespace std;

// 로그호출 : LogManager::GetInstance().함수명(...)

// 0. 캐릭터 생성 및 정보 출력 로그 정의
void LogManager::PrintCharacterInfo(Character* character)
{
    if (character == nullptr) return;

    cout << "\n========= [ 캐릭터 정보 ] =========" << endl;
    cout << " 이름     : " << character->getName() << endl;
    cout << " 직업     : " << character->getJob() << endl;
    cout << " 레벨     : " << character->getLevel() << " / 10" << endl;
    cout << " HP       : " << character->getHealth() << " / " << character->getMaxHealth() << endl;
    cout << " MP       : " << character->getMp() << " / " << character->getMaxMp() << endl;
    cout << " 경험치   : " << character->getExp() << " / " << character->getMaxExp() << endl;
    cout << " 공격력   : " << character->getAttack() << endl;
    cout << " 방어력   : " << character->getDefense() << endl;
    cout << " 보유골드 : " << character->getGold() << " G" << endl;
    cout << "===================================\n" << endl;
}

// 1.몬스터 등장
void LogManager::PrintMonsterAppear(const string& monsterName, int monsterMaxHp, int monsterAtk, int monsterDef)
{
    std::cout << "몬스터 [" << monsterName << "] 등장...\n\n";

    std::cout << "\n========= [ 몬스터 정보 ] =========\n";
    std::cout << " 이름     : " << monsterName << std::endl;
    std::cout << " HP       : " << monsterMaxHp << std::endl;
    std::cout << " 공격력   : " << monsterAtk << std::endl;
    std::cout << " 방어력   : " << monsterDef << std::endl;
    std::cout << "===================================\n";
}
// 2. 플레이어가 몬스터 공격
// damageType 1 = 기본, 2 = 스킬, 3 = 치명타
void LogManager::PrintAttackLog(const string& monsterName, int actualDamage, int currentHp, int damageType)
{
    if (damageType == 1) {
        cout << "\n[" << monsterName << "]에게 기본 공격을 가합니다!\n";
    }
    else if (damageType == 2) {
        cout << "\n[" << monsterName << "]에게 스킬 공격을 가합니다!\n";
    }
    else if (damageType == 3) {
        cout << "치명타!!!\n";
        cout << "\n[" << monsterName << "]에게 치명적인 공격을 가합니다!\n";
    }
        
    cout << monsterName << "이(가) " << actualDamage << "의 피해를 입었습니다! (남은 체력: " << currentHp << ")" << endl;
}

// 3. 몬스터가 플레이어 공격
// isCrit: false = 기본공격, true = 치명타
void LogManager::PrintPlayerDamagedLog(const string& monsterName, int damage, int playerHealth, bool isCrit)
{
    if (!isCrit) {
        cout << "\n[" << monsterName << "]에게 공격을 받았습니다 ...(데미지 : " << damage << ")\n";
        cout << "남은 체력 : " << playerHealth << "\n";
    }
    else {
        cout << monsterName << "이 공격을 준비합니다 ...\n";
        cout << "치명타!!!\n";
        cout << "\n[" << monsterName << "]에게 치명적인 공격을 받았습니다 ...(데미지 : " << damage << ")\n";
        cout << "남은 체력 : " << playerHealth << "\n";
    }
}

// 체력 포션 로그
void LogManager::PrintPotionEffect(const std::string& potionName, int actualRestore)
{
    cout << potionName << "을 사용하여 체력을 " << actualRestore << " 회복했습니다!" << endl;
}

// 공격력 포션 로그
void LogManager::PrintBattleBuffEffect(const std::string& buffName, int increaseAmount, int currentAttack)
{
    cout << buffName << "을 사용하여 공격력을 " << increaseAmount << " 증가시켰습니다!(이번 전투 동안만 유지됩니다)" << endl;
    cout << "현재 공격력: " << currentAttack << endl;
}

// 경험치 획득 로그
void LogManager::PrintExpReward(int amount, int currentExp, int maxExp)
{
    cout << "\n -> 경험치 +" << amount << " 획득! (현재 경험치: " << currentExp << "/" << maxExp << ")\n";
}

// 골드 획득 로그
void LogManager::PrintGoldReward(int rewardGold, int currentGold)
{
    cout << " 골드 +" << rewardGold << " G 획득! (현재 골드: " << currentGold << "G)\n";
}

// 장비 아이템 사용 로그
// 무기
void LogManager::PrintWeaponEquip(const std::string& itemName, int damage)
{
    std::cout << itemName << "을(를) 장착하여 공격력이 " << damage << " 증가했습니다!" << std::endl;
}

// 방어구
void LogManager::PrintArmorEquip(const std::string& itemName, int defense)
{
    std::cout << itemName << "을(를) 장착하여 방어력이 " << defense << " 증가했습니다!" << std::endl;
}


// 레벨업 로그
void LogManager::PrintLevelUp(int oldLevel, int newLevel, int hpDiff, int atkDiff, int beforeHP, int maxHP, int beforeAtk, int maxAtk) {
    cout << "\n레벨업 조건 충족\n";
    cout << "★☆★★☆★★☆★★☆★☆★\n";
    cout << "★☆★ LEVELUP★☆★\n";
    cout << "★☆★★☆★★☆★★☆★☆★\n";
    cout << " -> Lv." << oldLevel << " -> Lv." << newLevel << "\n";
    cout << " -> HP +" << hpDiff << " 공격력 +" << atkDiff << " 증가!\n";
    cout << "\n스탯이 상승했습니다!\n";
    cout << "HP : " << beforeHP << " -> " << maxHP << "\n";
    cout << "공격력 : " << beforeAtk << " -> " << maxAtk << "\n";
}

// 5. 몬스터 처치 기록 누적 함수
void LogManager::RecordKill(const string& monsterName)
{
	// 맵에 처치 수 누적
	killCounts[monsterName]++;

	// "몬스터이름 처치!" 로 출력 
    std::cout << "\n 전투 승리! [" << monsterName << "]를 처치했습니다!\n";
    std::cout << "=========================================\n";

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

// 보스 출현 로그 출력 함수
void LogManager::PrintBossAppear() const
{
    std::cout << "\n====================================\n";
    std::cout << "!!! Boss출현 !!!\n";
    std::cout << "드래곤이 나타났다...\n";
    std::cout << "====================================\n";
}

// 클리어 로그 출력 함수
void LogManager::PrintGameClear() const
{
    std::cout << "\n====================================\n";
    std::cout << "드래곤이 쓰러졌다...\n";
    std::cout << "세계에 평화가 찾아왔다.\n";
    std::cout << "===== GAME CLEAR =====\n";
    std::cout << "====================================\n";
}

// 크래딧 로그 출력 함수
void LogManager::ShowCredits() const
{
    std::string credits[] = {
            "\n\n\n\n\n\n\n\n\n\n\n\n",
        "\n==============================",
        "        GAME CLEAR           ",
        "==============================",
        "",
        "Director : 노신성\n",
        "Developer : 띵조\n",
        "Character System : 김민석\n",
        "Battle System : 노신성\n",
        "Monster System : 연명흠\n",
        "Item System : 김형준\n",
        "Game Log System : 홍승표\n",
        "Level up System : 이유록\n",
        "Thanks for Playing!",
        "==============================",
        "\n\n\n\n\n\n\n\n\n\n\n\n",
        "and you...",
        "\n\n\n\n\n\n\n\n\n\n\n\n"
    };

    for (auto& line : credits)
    {
        std::cout << line << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}