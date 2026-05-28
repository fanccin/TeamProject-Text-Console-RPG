#pragma once



class Character;
class Monster;


class BattleManager {

private :
	Character* character;
	
public :

	BattleManager(Character* character)
		: character(character){
		;
	}

	// 몬스터 레벨 스케일링
	// character->getLevel() 에 따라 몬스터 레벨 결정
	Monster* generateMonster(int level);

	void startBattle();

};