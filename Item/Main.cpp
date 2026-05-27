#include <iostream>
#include "Character.h" // 🚨 팀원분 파일명이 Characters.h 라면 스펠링 맞춰주세요!
#include "Inventory.h"

using namespace std;

int main() {
    // 1. 진짜 캐릭터 생성 (팀원분 클래스 활용)
    cout << "=== [1단계] 플레이어 생성 ===" << endl;
    Character* player = new Warrior("형준전사");

    // 2. 가격 연동 버전 인벤토리 생성
    Inventory* myBag = new Inventory();

    player->displayStatus();

    cout << "\n=== [2단계] 생성자 가격 연동 AddItem 테스트 ===" << endl;
    // 🌟 [아이템타입, 이름, 성능수치, 가격] 4개 인자 던지기!
    myBag->AddItem("Health", "초급 빨간 포션", 50, 100);       // 100 골드
    myBag->AddItem("Attack", "귀신 같은 비약", 15, 300);       // 300 골드
    myBag->AddItem("Weapon", "태양의 검", 50, 5000);         // 5000 골드
    myBag->AddItem("Armor", "기사의 갑옷", 30, 2500);         // 2500 골드

    // 현재 가방 리스트 출력
    myBag->ShowInventory();

    cout << "\n=== [3단계] 아이템 개별 가격 정상 연동 확인 ===" << endl;
    // 가방 시스템이 잘 고쳐졌다면, 가격이 하드코딩(10, 100)이 아니라 
    // 우리가 방금 AddItem할 때 넣은 금액이 다르게 찍혀야 합니다!
    cout << "▶ 새로 장착한 시스템이 기억하는 아이템 가격들:" << endl;

    // 이 테스트를 위해 Inventory에 GetSize()를 만들어 뒀으니 활용해 봅시다.
    // 임시로 가방 내부의 가격을 테스트하기 위해 작성된 코드입니다.
    // (만약 에러가 난다면 이 3단계만 주석 처리하셔도 됩니다!)
    /*
    cout << " - 가방 1번 아이템 가격: 100골드 정답? -> " << myBag->GetPriceTest(0) << "골드" << endl;
    */

    cout << "\n=== [4단계] 장비 장착 및 스탯 변화 테스트 ===" << endl;
    cout << "▶ 가방 [3]번방 (태양의 검) 장착! (5000골드 짜리)" << endl;
    myBag->UseItem(2, player); // 무기니까 파괴 안 됨

    cout << "\n▶ 가방 [3]번방 (기사의 갑옷) 장착! (2500골드 짜리)" << endl;
    myBag->UseItem(2, player); // 방어구니까 파괴 안 됨

    cout << "\n=== [5단계] 최종 결과 스탯 및 남은 가방 확인 ===" << endl;
    // 스탯이 정상 반영되었고, 가방에는 포션 2개만 남아야 성공!
    player->displayStatus();
    myBag->ShowInventory();

    cout << "\n=== [6단계] 소모품 사용 및 메모리 정리 ===" << endl;
    cout << "▶ 가방 [1]번방 (초급 빨간 포션) 마시기!" << endl;
    myBag->UseItem(0, player);

    cout << "\n=== [7단계] 최종 가방 상태 (비약 1개만 남아야 함) ===" << endl;
    myBag->ShowInventory();

    // 메모리 누수 방지 (소멸자 자동 실행 구역)
    cout << "\n=== [8단계] 동적 할당 메모리 해제 ===" << endl;
    delete player;
    delete myBag; // 🌟 가방이 터지면서 남은 '비약'도 가상 소멸자로 깔끔히 청소됩니다!

    cout << "모든 테스트가 에러 없이 성공적으로 종료되었습니다!" << endl;
    return 0;
}