#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int> solution(string msg) {
	transform(msg.begin(), msg.end(), msg.begin(), ::tolower);

	map<string, int> m;

	int mIndex;
	char alphabet = 'a';
	for (mIndex = 1; mIndex < 27; mIndex++) {
		m.insert({ string(1, alphabet), mIndex });
		alphabet++;
	}

	vector<int> answer;
	for (int i = 0; i < msg.length(); ) {
		bool canFind = true;
		
		int index;
		int len = 1;
		while (canFind) {
			if (i + len > msg.length()) break;

			string str = msg.substr(i, len);
			if (m.find(str) == m.end()) {
				canFind = false;
				m.insert({ str, mIndex });
				mIndex++;
			}
			else {
				index = m[str];
				len++;
			}
		}
		answer.push_back(index);
		i += (len - 1);
	}
	return answer;
}

int main() {
	solution("KAKAO");
}