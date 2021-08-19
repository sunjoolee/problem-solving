#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> money;

//결정 문제: fajomonths에서의 최대 지출이 x일 때 N개의 날들을 M개의 fajomonths로 구성할 수 있는가?  
bool decision(int x) {
	//구성된 fajomonths의 개수
	int cnt = 1;
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		if (sum + money[i] > x) {
			++cnt;
			sum = money[i];
		}
		else sum += money[i];
	}

	if (cnt <= M) return true;
	return false;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	
	int moneySum = 0;
	int moneyMax = 0;
	for (int i = 0; i < N; ++i) {
		int input;
		cin >> input;
		money.push_back(input);

		moneySum += input;
		moneyMax = max(moneyMax, input);
	}

	double lo = moneyMax;
	double hi = moneySum;
	for (int it = 0; it < 100; ++it) {
		double mid = (hi + lo) / 2;

		if (decision(mid)) hi = mid;
		else lo = mid;
	}

	cout << (int)hi;
	return 0;
}