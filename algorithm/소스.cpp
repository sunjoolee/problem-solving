#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

//최적화 문제: M개의 블루레이로 모든 레슨을 녹화할 수 있는 블루레이의 크기 중 최솟값을 구해라
//결정 문제:  크기 x 혹은 x이하인 블루레이 M개로 모든 레슨을 녹화할 수 있는가?

int n, m;
vector<int> lesson;

bool decision(double x) {
	//모든 레슨을 녹화하기 위해 필요한 블루레이의 개수
	int cnt = 1;

	//하나의 블루레이에 들어갈 레슨의 길이의 합
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		if (sum + lesson[i] > x) {
			cnt++;
			sum = lesson[i];
		}
		else sum += lesson[i];
	}

	return cnt <= m;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	//가장 길이가 긴 레슨의 길이
	int longestlesson = 0;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		lesson.push_back(input);

		longestlesson = max(longestlesson, input);
	}
	
	double hi = 10000;
	double lo = longestlesson;
	for (int it = 0; it < 100; ++it) {
		double mid = (hi + lo) / 2;

		if (decision(mid)) hi = mid;
		else lo = mid;
	}

	cout << lo;

	return 0;
}