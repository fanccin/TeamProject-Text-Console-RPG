#pragma once

#include <string>
#include <map>



class LogManager
{
private:
    // 몬스터 처치 기록 누적용 맵
    std::map<std::string, int> killCounts;

public:
    // 0. 캐릭터 생성 및 정보 출력 로그 선언 (이름, 레벨, 체력, 공격력)
    void PrintCharacterInfo(const std::string& playerName, int level, int hp, int attack);

    // 1.몬스터 등장, 공격 및 피해 로그 정의
    void PrintMonsterAppearAndAttack(const std::string& monsterName, int monsterMaxHp, int monsterAtk,
        const std::string& attackerName, const std::string& targetName,
        int damage,  int currentHp);
    
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