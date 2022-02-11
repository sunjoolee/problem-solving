#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long ll;

unordered_map<ll, ll> notEmptyRoom;

ll findEmptyRoom(ll u) {
	if (notEmptyRoom.find(u) == notEmptyRoom.end()) return u;

	//경로 압축(path compression) 최적화 구현
	return notEmptyRoom[u] = findEmptyRoom(notEmptyRoom[u]);
}

vector<ll> solution(ll k, vector<ll> room_number) {
	vector<ll> answer;

	for (int i = 0; i < room_number.size(); ++i) {
		ll roomNum = room_number[i];

		if (notEmptyRoom.find(roomNum) == notEmptyRoom.end()) {
			answer.push_back(roomNum);

			notEmptyRoom[roomNum] = findEmptyRoom(roomNum + 1);
		}
		else {
			ll emptyRoomNum = findEmptyRoom(roomNum);
			answer.push_back(emptyRoomNum);

			notEmptyRoom[emptyRoomNum] = findEmptyRoom(emptyRoomNum + 1);
		}
	}

	return answer;
}
