#include <string>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

// k는 1 이상 10^12 이하인 자연수
// k가 클 경우, ull 타입의 bitmask로 모든 방을 표현할 수 없음!

typedef long long ll;
typedef unsigned long long ull;

vector<ll> solution(ll k, vector<ll> room_number) {
	vector<ll> answer;

	ull bitmask = (1 << k) - 1;

	for (int i = 0; i < room_number.size(); ++i) {
		ll room = room_number[i] - 1;

		//bitmask에 room번째 원소 포함 여부 확인
		if (bitmask & (1 << room)) {
			answer.push_back(room + 1);
			//room번째 원소 삭제
			bitmask &= ~(1 << room);
		}
		else {
			// 원하는 방보다 번호가 크면서 비어있는 방 중 가장 번호가 작은 방
			ull mask = bitmask & -(1 << room);
			ll room2 = log2(mask & (~mask + 1));

			answer.push_back(room2 + 1);
			//room2번째 원소 삭제
			bitmask &= ~(1 << room2);
		}

	}

	return answer;
}

