#pragma once

#include <string>
#include <map>



class LogManager
{
private:
    // 생성자, 소멸자를 private으로 숨겨 외부 생성 차단
    LogManager() = default;
    ~LogManager() = default;
    
    // 2. 복사 생성자 및 대입 연산자 제거 (싱글톤 복사 방지)
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
    void PrintCharacterInfo(const std::string& playerName, int level, int hp, int attack);

    // 몬스터 등장
    void PrintMonsterAppear(const std::string& monsterName, int monsterMaxHp, int monsterAtk);
    
    //전투 중 공격/피해 로그
    void PrintAttackLog(const std::string& attackerName, const std::string& targetName, int damage,  int currentHp);

    //2. 체력 +50(포션) : 현재 체력을 50 회복 형태로 출력
    void PrintPotionEffect(int healAmount);

    //3.공격력 + 10: 해당 전투에만 효과 발휘 형태로 출력
    void PrintBattleBuffEffect(int statAmount);

    // 4. 경험치,골드 획득 로그 선언
    void PrintRewardLog(const std::string& playerName, int expAmount, int goldAmount, int currentExp, int maxExp, int currentGold);

    // 5. 몬스터 처치 기록 누적 선언
    void RecordKill(const std::string& monsterName);

    // 6. 누적 처치 출력 선언
    void PrintKill() const;
};