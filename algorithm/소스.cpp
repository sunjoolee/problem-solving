#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long ll;

//parent[i]: i������ ��ȣ�� ũ��, ���� ������ �� �� ���� ��ȣ�� ���� ���� ��ȣ
//parent[i] = i�� ��� �� ���� ���� -> �� ���� �� parent[i] = i+1
unordered_map<ll, ll> parent;


//u�� ���� Ʈ���� ��Ʈ ��ȣ ��ȯ
int find(int u) {
	//�θ� �ڱ� �ڽ��� ����Ű�� ��� u�� ��Ʈ ���
	if (u == parent[u]) return u;

	//��� ����(path compression) ����ȭ ����
	return parent[u] = find(parent[u]);
}

vector<ll> solution(ll k, vector<ll> room_number) {
	vector<ll> answer;

	for (ll i = 0; i < k; ++i)
		parent.insert({ i, i });
	
	for (int i = 0; i < room_number.size(); ++i) {
		ll roomNum = room_number[i] - 1;
		
		if (parent[roomNum] == roomNum) {
			answer.push_back(roomNum + 1);
			parent[roomNum] = roomNum + 1;
		}
		else {
			ll availableNum = find(roomNum);
			answer.push_back(availableNum + 1);
			parent[availableNum] = availableNum + 1;
		}
	}

	return answer;
}

int main() {
	ll k;
	vector<ll> room_number;
	
	cin >> k;
	for (int i = 0; i < 6; ++i) {
		ll n;
		cin >> n;
		room_number.push_back(n);
	}

	solution(k, room_number);
	return 0;
}

