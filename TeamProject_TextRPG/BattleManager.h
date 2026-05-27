#pragma once



class Character;
class Monster;


class BattleManager {

private :
	Character* character;

	bool isBoss; //보스  출현 여부

	bool isBossCleared = false; //보스 클리어 체크

public :

	BattleManager(Character* character, bool isBoss = false)
		: character(character),isBoss(isBoss){
		;
	}

	// 몬스터 레벨 스케일링
	// character->getLevel() 에 따라 몬스터 레벨 결정
	Monster* generateMonster(int level);

	void startBattle();

	bool isBossBattle() const { return isBoss; } //보스 전투중?
	bool isBossClearedResult() const { return isBossCleared; } //보스 클리어 여부

};