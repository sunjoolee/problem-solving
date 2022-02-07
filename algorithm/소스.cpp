#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

set<int> ans; 
vector<string> user_id_g;
vector<string> banned_id_g;

int bitCount(int x) {
	if (x == 0) return 0;
	return (x % 2) + bitCount(x / 2);
}


bool match(string a, string b) {
	if (a.length() != b.length()) return false;

	for (int i = 0; i < a.length(); ++i) {
		if (a[i] == '*' || b[i] == '*') continue;
		if (a[i] != b[i]) return false;
	}
	return true;
}

void dp(int banned_index, int bitmask) {
	if (banned_id_g.size() == banned_index) {
		if (bitCount(bitmask) == banned_id_g.size()) {
			ans.insert(bitmask);
		}
		return;
	}

	for (int i = 0; i < user_id_g.size(); ++i) {
		if (match(user_id_g[i], banned_id_g[banned_index])) {
			if ((bitmask & (1 << i)) == 0) {
				dp(banned_index + 1, bitmask | (1 << i));
			}
		}
	}
}

int solution(vector<string> user_id, vector<string> banned_id) {
	user_id_g = user_id;
	banned_id_g = banned_id;

	int answer = 0;

	dp(0, 0);
	answer = ans.size();

	return answer;
}



