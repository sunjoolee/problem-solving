#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long ll;

//parent[i]: i번보다 번호가 크고, 배정 가능한 방 중 가장 번호가 작은 방의 번호
//parent[i] = i일 경우 방 배정 가능 -> 방 배정 후 parent[i] = i+1
unordered_map<ll, ll> parent;


//u가 속한 트리의 루트 번호 반환
int find(int u) {
	//부모가 자기 자신을 가리키는 경우 u는 루트 노드
	if (u == parent[u]) return u;

	//경로 압축(path compression) 최적화 구현
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

