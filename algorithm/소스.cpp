#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

bool cmp(int x, int y) {
	return x > y;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	vector<int> A;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		A.push_back(input);
	}
	//A 오름차순 정렬
	sort(A.begin(), A.end());

	vector<int> B;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		B.push_back(input);
	}
	//B 내림차순 정렬
	sort(B.begin(), B.end(), cmp);

	int res = 0;
	for (int i = 0; i < n; ++i) {
		res += (A[i] * B[i]);
	}
	cout << res;
	return 0;
}