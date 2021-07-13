#include<iostream>
#include <algorithm>
#include <math.h>
using namespace std;

typedef long long int ll;
const int MAXN = 5000;
const ll MAXSUM = 1000000000 * MAXN * 3;

int N;
int A[MAXN + 1] = { 0 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> A[i];

	sort(A, A+N);

	//산성 용액으로만 주어지는 경우
	if ((A[0] >= 0) && (A[N - 1] >= 0)) {
		cout << A[0] << " " << A[1] << " " << A[2];
		return 0;
	}
	//염기성 용액으로만 주어지는 경우
	if ((A[0] < 0) && (A[N - 1] < 0)) {
		cout << A[N - 3] <<" "<< A[N - 2] << " " << A[N - 1];
		return 0;
	}

	long long minsum = MAXSUM;
	int minleft, minright, minmid;
	minleft = minright = minmid = N - 1;

	for (int mid = 1; mid < N - 1; mid++) {

		long long sum;
		int left = left = mid - 1;
		int right = mid + 1;

		while (left < mid && mid < right) {
			sum = A[left] + A[mid] + A[right];
			if (minsum > abs(sum)) {
				minsum = abs(sum);
				minleft = left;
				minmid = mid;
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
	}

	cout << A[minleft] << " " << A[minmid]<<" "<< A[minright];
	return 0;
}


