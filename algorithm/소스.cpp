#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int MAX = 2000;

int S;
int cache[2000][1000];

int getTime(int sum, int clipBoard) {
	//base case
	if (sum == S) return 0;
	if (sum > 2 * S) return MAX;

	//메모이제이션
	int& ret = cache[sum][clipBoard];
	if (ret != -1) return ret;

	int min = MAX;
	//복사 연산
	if (sum != clipBoard) {
		int copy = getTime(sum, sum);
		if (min > copy) min = copy;
	}
	//붙여넣기 연산
	if (sum < S && clipBoard != 0) {
		int paste = getTime(sum + clipBoard, clipBoard);
		if (min > paste) min = paste;
	}
	//하나 빼기 연산
	if (sum > S) {
		int sub = getTime(sum - 1, clipBoard);
		if (min > sub) min = sub;
	}

	return ret = min + 1;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 2000; ++i)
		memset(cache[i], -1, sizeof(cache[i]));

	cin >> S;
	cout << getTime(1, 0);
	return 0;
}