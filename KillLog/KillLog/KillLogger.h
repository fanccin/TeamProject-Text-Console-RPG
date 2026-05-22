#pragma once
#include <string>
#include <map>

using namespace std;

class KillLog
{
private:
	// 몬스터 이름과 처치 횟수를 저장하는 map
	map<string, int> killHistory;

public:
	// 몬스터 처치될때 마다 몬스터 이름 불러와서 킬수 누적
	void RecordKill(string monsterName);

	// 킬로그 보여주는 함수
	void DisplayKillLog();
};
