#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long int ull;

int n;
priority_queue<ull, vector<ull>,  greater<ull>> minheap;
ull cnt = 0;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		minheap.push(input);
	}

	//가장 작은 두 카드 묶음 선택하여 합치기
	while (true) {
		if (minheap.size() == 1) 
			break;
		
		ull a = minheap.top();
		minheap.pop();
		ull b = minheap.top();
		minheap.pop();

		cnt += (a + b);
		minheap.push(a + b);
	}

	cout << cnt;
	return 0;
}