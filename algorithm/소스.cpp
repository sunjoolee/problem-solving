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

	//������ ��� �ܾ� anta ~ tica
	//�ּ� 5���� ���ĺ� �ʿ� (a, c, i, n, t)
	if (k < 5) {
		cout << "0";
		return 0;
	}
	//26���� ���ĺ��� ��� ��� ��� ��� �ܾ� ���� �� ����
	if (k == 26) {
		cout << n;
		return 0;
	}

	//������ �ܾ���� ���� ����ϴ� ���ĺ� ��Ʈ����ũ ����
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

	
	//�� �ʿ��� 5���� ����
	long long acint = 0LL;
	acint |= (1 << ('a' - 'a'));
	acint |= (1 << ('c' - 'a'));
	acint |= (1 << ('i' - 'a'));
	acint |= (1 << ('n' - 'a'));
	acint |= (1 << ('t' - 'a'));

	//��� ���ĺ� ��Ʈ����ũ
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