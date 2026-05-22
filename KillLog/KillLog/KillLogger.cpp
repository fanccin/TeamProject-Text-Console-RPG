#include <iostream>
#include <string>
#include <map>
#include "KillLogger.h"

using namespace std;

//몬스터 처치 누적 기록
void KillLog::RecordKill(string monsterName)
{
	killHistory[monsterName]++;
}

// 처치기록 한 번에 출력
void KillLog::DisplayKillLog()
{
	cout << "\n========================================" << endl;
	cout << "        [ 몬스터 처치 기록 ]       " << endl;
	cout << "========================================" << endl;

	if (killHistory.empty())
	{
		cout << "처치한 몬스터가 없습니다." << endl;
	}
	else
	{
		// map을 순회하며 "* 몬스터 이름 : X 마리 처치" 형태로 화면에 나열
		for (const auto& pair : killHistory)
		{
			cout << " * " << pair.first << " : " << pair.second << "마리 처치" << endl;
		}
	}
	cout << "========================================" << endl;
}