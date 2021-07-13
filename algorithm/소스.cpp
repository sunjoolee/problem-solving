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
	//A ������������ �Է� ��
	for (int i = 0; i < N; i++)
		cin >> A[i];

	//�꼺 ������θ� �־����� ���
	if ((A[0] >= 0) && (A[N - 1] >= 0)) {
		cout << A[0] << " " << A[1];
		return 0;
	}
	//���⼺ ������θ� �־����� ���
	if ((A[0] < 0) && (A[N - 1] < 0)) {
		cout << A[N - 2] << " " << A[N - 1];
		return 0;
	}

	//0 �Ǵ� 0 �ʰ��ϴ� ���� ù��° ��
	int lb = lower_bound(A, A + N, 0) - A;

	int left, right, minleft, minright;

	minleft = left = lb - 1;
	minright = right = lb;

	long long minsum = MAXSUM;
	long long sum;

	//���� ���� ��� �ΰ�
	if (right != N - 1) {
		sum = A[right] + A[right + 1];
		if (minsum > abs(sum)) {
			minsum = abs(sum);
			minleft = right;
			minright = right + 1;
		}
	}
	//���� ���� ���� �ΰ�
	if (left != 0) {
		sum = A[left - 1] + A[left];
		if (minsum > abs(sum)) {
			minsum = abs(sum);
			minleft = left - 1;
			minright = left;
		}
	}
	//����ϳ� ���� �ϳ�
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


