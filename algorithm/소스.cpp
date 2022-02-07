#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_VAL = 2000000000;

int solution(vector<int> stones, int k) {
	int answer = 0;

	int minVal = MAX_VAL;
	for (int i = 0; i <= stones.size() - k; ++i) {		
		int maxVal = 0;
		for (int j = 0; j < k; ++j) {
			maxVal = max(maxVal, stones[i + j]);
		}
		minVal = min(minVal, maxVal);
	}
	answer = minVal;

	return answer;
}

int main() {
	vector<int> a;
	for (int i = 0; i < 10; ++i) {
		int input;
		cin >> input;
		a.push_back(input);
	}

	int k;
	cin >> k;

	cout << solution(a, k);
}

