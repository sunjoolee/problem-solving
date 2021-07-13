#include<iostream>
#include <algorithm>
#include <math.h>
using namespace std;

typedef long long int ll;
const int MAXN = 100000;
const ll MAXSUM = 1000000000 * MAXN;

int N;
int A[MAXN + 1] = { 0 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	//A 오름차순으로 입력 됨
	for (int i = 0; i < N; i++)
		cin >> A[i];

	//산성 용액으로만 주어지는 경우
	if ((A[0] >= 0) && (A[N - 1] >= 0)) {
		cout << A[0] << " " << A[1];
		return 0;
	}
	//염기성 용액으로만 주어지는 경우
	if ((A[0] < 0) && (A[N - 1] < 0)) {
		cout << A[N - 2] << " " << A[N - 1];
		return 0;
	}

	//0 또는 0 초과하는 가장 첫번째 수
	int lb = lower_bound(A, A + N, 0) - A;

	int left, right, minleft, minright;

	minleft = left = lb - 1;
	minright = right = lb;

	long long minsum = MAXSUM;
	long long sum;

	//가장 작은 양수 두개
	if (right != N - 1) {
		sum = A[right] + A[right + 1];
		if (minsum > abs(sum)) {
			minsum = abs(sum);
			minleft = right;
			minright = right + 1;
		}
	}
	//가장 작은 음수 두개
	if (left != 0) {
		sum = A[left - 1] + A[left];
		if (minsum > abs(sum)) {
			minsum = abs(sum);
			minleft = left - 1;
			minright = left;
		}
	}
	//양수하나 음수 하나
	while (left < right) {
		sum = A[left] + A[right];
		if (minsum > abs(sum)) {
			minsum = abs(sum);
			minleft = left;
			minright = right;
		}

		if (sum == 0) break;
		if (sum > 0) {
			if (left == 0) break;
			left--;
		}
		else {
			if (right == N - 1) break;
			right++;
		}
	}

	cout << A[minleft] << " " << A[minright];
	return 0;
}


