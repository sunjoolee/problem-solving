#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll orderToBitmask(string order) {
	ll bitmask = 0LL;
	for (int i = 0; i < order.length(); ++i) {
		bitmask |= (1 << (order[i]-'A'));
	}
	return bitmask;
}

string bitmaskToOrder(ll bitmask) {
	string order = "";
	for (int i = 0; i < 26; ++i) {
		if (bitmask & (1 << i)) order += (char)('A' + i);
	}
	return order;
}

int bitCount(int x) {
	if (x == 0) return 0;
	return (x % 2) + bitCount(x / 2);
}

vector<string> solution(vector<string> orders, vector<int> course) {

	vector<ll> orderBitmasks;
	for (int i = 0; i < orders.size(); ++i) {
		orderBitmasks.push_back(orderToBitmask(orders[i]));
	}

	vector<string> answer;

	for (int i = 0; i < course.size(); ++i) {
		int courseSize = course[i];

		vector<ll> courseBitmasks;
		int maxCnt = 2;
		for (ll subset = 0LL; subset < (1 << 26); subset++) {
			if (bitCount(subset) != courseSize) continue;

			int cnt = 0;
			for (int j = 0; j < orderBitmasks.size(); ++j) {
				if ((subset & orderBitmasks[j]) == subset) cnt++;
			}
			
			if (cnt == maxCnt) courseBitmasks.push_back(subset);
			else if (cnt > maxCnt) {
				maxCnt = cnt;
				courseBitmasks.clear();
				courseBitmasks.push_back(subset);
			}
		}

		for (int j = 0; j < courseBitmasks.size(); ++j) {
			answer.push_back(bitmaskToOrder(courseBitmasks[j]));
		}
	}

	return answer;
}