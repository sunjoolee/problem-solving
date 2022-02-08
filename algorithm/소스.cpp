#include <string>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;

set<ll> hotel;

vector<ll> solution(ll k, vector<ll> room_number) {
	vector<ll> answer;

	for (ll i = 1LL; i <= k; ++i) {
		hotel.insert(i);
	}


	for (int i = 0; i < room_number.size(); ++i) {
		ll room = room_number[i];

		auto iter = hotel.find(room);
		if (iter != hotel.end()) {
			answer.push_back(room);
			hotel.erase(iter);
		}
		else {
			iter = hotel.upper_bound(room);
			answer.push_back(*iter);
			hotel.erase(iter);
		}

	}

	return answer;
}