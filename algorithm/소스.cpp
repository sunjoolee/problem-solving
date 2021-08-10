#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

//최적화 문제: k개의 그룹으로 나눴을 때 각 그룹의 맞은 문제의 합 중 최솟값의 최댓값을 구해라
//결정 문제: 각 그룹에서 맞은 문제의 합이 x혹은 x이상이 되도록 시험지를 k개의 그룹으로 나눌 수 있는가?

int n, k;
vector<int> score;

bool decision(double x) {
	int group = 0;

	//그룹에서 맞은 문제의 개수의 합
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += score[i];
		if (sum >= x) {
			sum = 0;
			group++;
		}
	}
	
	return group >= k;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >>k;

	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		score.push_back(input);
	}

	double hi = 20 *100000;
	double lo = 0;
	for (int it = 0; it < 100; ++it) {
		double mid = (hi + lo) / 2;

		if (decision(mid)) lo = mid;
		else hi = mid;
	}

	cout << lo;
	return 0;
}