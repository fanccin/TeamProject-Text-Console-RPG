#pragma once

#include <string>
#include <map>
#include "Character.h"


class Character;
class LogManager
{
private:
    // 생성자, 소멸자를 private으로 숨겨 외부 생성 차단
    LogManager() = default;
    ~LogManager() = default;
    
    // 2. 복사 생성자 및 대입 연산자 제거 (싱글톤 복사 방지)
    // LogManager::GetInstance().함수명(...)
    LogManager(const LogManager& other) = delete;
    LogManager& operator=(const LogManager& other) = delete;

    // 몬스터 처치 기록 누적용 맵
    std::map<std::string, int> killCounts;

public:
    // 언제 어디서든 하나의 객체에 접근할 수 있는 유일한 통로
    static LogManager& GetInstance()
    {
        static LogManager instance; // Lazy Initialization + Thread-safe (C++11 이상)
        return instance;
    }

    // 0. 캐릭터 생성 및 정보 출력 로그 선언 (이름, 레벨, 체력, 공격력)
    void PrintCharacterInfo(Character* character);

    // 몬스터 등장
    void PrintMonsterAppear(const std::string& monsterName, int monsterMaxHp, int monsterAtk, int monsterDef);
    
    //플레이어가 몬스터 공격/피해 로그
    void PrintAttackLog(const std::string& monsterName, int actualDamage, int currentHp, int damageType);

    //몬스터가 플레이어 공격/피해 로그
    void PrintPlayerDamagedLog(const std::string& monsterName, int damage, int playerHealth, bool isCrit);

    //체력 포션 로그
    void PrintPotionEffect(const std::string& potionName, int actualRestore);

    //공격력 포션 로그
    void PrintBattleBuffEffect(const std::string& buffName, int increaseAmount, int currentAttack);

    //경험치 획득 로그
    void PrintExpReward(int amount, int currentExp, int maxExp);

    //골드 획득 로그
    void PrintGoldReward(int rewardGold, int currentGold);

    //무기 장착 로그
    void PrintWeaponEquip(const std::string& itemName, int damage);

    //방어구 장착 로그
    void PrintArmorEquip(const std::string& itemName, int defense);

    //레벨업 로그
    void PrintLevelUp(int oldLevel, int newLevel, int hpDiff, int atkDiff, int beforeHP, int maxHP, int beforeAtk, int maxAtk);

    // 5. 몬스터 처치 기록 누적 선언
    void RecordKill(const std::string& monsterName);

    // 6. 누적 처치 출력 선언
    void PrintKill() const;
};