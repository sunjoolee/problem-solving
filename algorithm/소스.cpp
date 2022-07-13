#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>
using namespace std;

typedef long long ll;

int n;
vector<ll> vec;

ll calcGcd(ll a, ll b) {
	ll c;
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

ll maxSum(int start, int end) {
	//�迭 ũ�� 1
	if (start == end) return vec[start];
	//�迭 ũ�� 2 
	if (start + 1 == end) return vec[start] + vec[end];

	int mid = (end - start + 1) / 2;

	//���ʺ��� ���Ҹ� �����ϴ� ���
	ll leftSum = 0;
	int idx = start;
	ll gcd = vec[start];
	while (idx <= (start + mid-1)) {
		gcd = calcGcd(gcd, vec[idx]);
		idx++;
	}
	leftSum = gcd + maxSum(start + mid, end);

	//�����ʺ��� ���Ҹ� �����ϴ� ���
	ll rightSum = 0;

	gcd = vec[end];
	while (idx <= end) {
		gcd = calcGcd(gcd, vec[idx]);
		idx++;
	}
	rightSum = gcd + maxSum(start, start + mid -1);

	return max(leftSum, rightSum);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		vec.push_back(input);
	}

	cout << maxSum(0, n - 1);
	return 0;
}