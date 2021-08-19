#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int N;
vector<int> A;

//A에서 이분 탐색으로 val값을 찾기 위해 필요한 비교 횟수 반환
ll binary_search(int value, int left, int right) {
	int mid = (left + right) / 2;

	if (A[mid] == value)
		return 0;

	else if (value < A[mid])
		return 1LL + binary_search(value, left, mid - 1);
	else
		return 1LL + binary_search(value, mid + 1, right);
}


//A에서 이분 탐색으로 val값을 찾기 위해 필요한 비교 횟수 반환
ll ternary_search(int value, int left, int right) {
	int left_third = left + ((right - left) / 3);
	int right_third = right - ((right - left) / 3);

	if (A[left_third] == value)
		return 0;
	else if (A[right_third] == value)
		return 1LL;
	else if (value < A[left_third])
		return 2LL + ternary_search(value, left, left_third - 1);
	else if (value < A[right_third])
		return 2LL + ternary_search(value, left_third + 1, right_third - 1);
	else
		return 2LL + ternary_search(value, right_third + 1, right);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i)
		A.push_back(i);

	int res1, res2, res3;
	res1 = res2 = res3 = 0; 
	for (int i = 0; i < N; ++i) {
		ll B, T;
		B = binary_search(A[i], 0, N - 1);
		T = ternary_search(A[i], 0, N - 1);

		if (B < T) ++res1;
		else if (B == T) ++res2;
		else if (B > T) ++res3;
	}
	
	cout << res1 << "\n" << res2 << "\n" << res3;
	return 0;
}