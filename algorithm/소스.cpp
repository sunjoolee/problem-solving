#include <string>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

// k�� 1 �̻� 10^12 ������ �ڿ���
// k�� Ŭ ���, ull Ÿ���� bitmask�� ��� ���� ǥ���� �� ����!

typedef long long ll;
typedef unsigned long long ull;

vector<ll> solution(ll k, vector<ll> room_number) {
	vector<ll> answer;

	ull bitmask = (1 << k) - 1;

	for (int i = 0; i < room_number.size(); ++i) {
		ll room = room_number[i] - 1;

		//bitmask�� room��° ���� ���� ���� Ȯ��
		if (bitmask & (1 << room)) {
			answer.push_back(room + 1);
			//room��° ���� ����
			bitmask &= ~(1 << room);
		}
		else {
			// ���ϴ� �溸�� ��ȣ�� ũ�鼭 ����ִ� �� �� ���� ��ȣ�� ���� ��
			ull mask = bitmask & -(1 << room);
			ll room2 = log2(mask & (~mask + 1));

			answer.push_back(room2 + 1);
			//room2��° ���� ����
			bitmask &= ~(1 << room2);
		}

	}

	return answer;
}

