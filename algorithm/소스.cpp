#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int bitCount(long long x) {
	if (x == 0) return 0;
	return (x % 2) + bitCount(x / 2);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n, k;
	cin >> n >> k;

	//남극의 모든 단어 anta ~ tica
	//최소 5개의 알파벳 필요 (a, c, i, n, t)
	if (k < 5) {
		cout << "0";
		return 0;
	}
	//26개의 알파벳을 모두 배운 경우 모든 단어 읽을 수 있음
	if (k == 26) {
		cout << n;
		return 0;
	}

	//남극의 단어들이 각각 사용하는 알파벳 비트마스크 저장
	vector<long long> wordsAlpha;
	//long long maxUsedAlpha = 0LL;

	for (int i = 0; i < n; ++i) {
		string input;
		cin >> input;

		long long usedAlpha = 0LL;
		for (int i = 0; i < input.length(); ++i) {
			usedAlpha |= (1 << (input[i] - 'a'));
		}
		//maxUsedAlpha = max(maxUsedAlpha, usedAlpha);

		wordsAlpha.push_back(usedAlpha);
	}

	
	//꼭 필요한 5개의 글자
	long long acint = 0LL;
	acint |= (1 << ('a' - 'a'));
	acint |= (1 << ('c' - 'a'));
	acint |= (1 << ('i' - 'a'));
	acint |= (1 << ('n' - 'a'));
	acint |= (1 << ('t' - 'a'));

	//배운 알파벳 비트마스크
	long long learnAlpha;

	int maxCnt = 0;
	for (learnAlpha = acint; learnAlpha <= (1<<26); ++learnAlpha) {
		if ((learnAlpha & acint) != acint) continue;
		if (bitCount(learnAlpha) > k) continue;
		
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if((learnAlpha & wordsAlpha[i]) == wordsAlpha[i]) cnt++;
		}
		maxCnt = max(maxCnt, cnt);
	}

	cout << maxCnt;
	return 0;
}