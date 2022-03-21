#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

int bitCount(int x) {
	if (x == 0) return 0;
	return (x % 2) + bitCount(x / 2);
}

int solution(vector<vector<string>> relation) {
	int answer = 0;

	//찾은 후보키 속성 집합들
	vector<ll> candidateKey;

	//후보키 속성 집합의 크기 작은 것부터 찾기
	for (int size = 1; size <= relation[0].size(); ++size) {

		//속성의 모든 부분 집합
		for (ll subset = 1LL; subset <= (1 << relation[0].size()) - 1; subset++) {
			if (bitCount(subset) != size) continue;

			//1. 최소성 검사
			//이미 찾은 후보키 속석의 집합 포함하고 있다면 continue
			bool shouldContinue = false;
			for (int i = 0; i < candidateKey.size(); ++i) {
				ll intersection = candidateKey[i] & subset;
				if (intersection == candidateKey[i]) {
					shouldContinue = true;
					break;
				}
			}
			if (shouldContinue) continue;

			//2. 유일성 검사
			bool unique = true;
			set<string> relationString;

			for (int i = 0; i < relation.size(); ++i) {
				string str = "";
				for (int key = 0; key < relation[0].size(); ++key) {
					if (subset & (1 << key)) str += relation[i][key];
				}
				if (relationString.find(str) != relationString.end()) {
					unique = false;
					break;
				}
				relationString.insert(str);
			}
			if (!unique) continue;

			candidateKey.push_back(subset);
			answer++;
		}
	}

	return answer;
}

int main() {
	solution({ {"100", "ryan", "music", "2"},
		{"200", "apeach", "math", "2"},
		{"300", "tube", "computer", "3"},
		{"400", "con", "computer", "4"},
		{"500", "muzi", "music", "3"},
		{"600", "apeach", "music", "2"} });
}