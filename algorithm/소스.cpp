#include <iostream>
#include <bitset>
using namespace std;

//64 bit (0 ~ 18,446,744,073,709,551,615)
typedef unsigned long long ull;

int n;
int a[41] = { 0 };
unsigned sum;	
unsigned sumFromStart[41] = { 0 };

ull msg = 0;

void calcSumFromStart() {
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			sumFromStart[i] += a[j];
			if (sumFromStart[i] >= sum) break;
			if (sumFromStart[i] > 2000000000) break;
		}
	}
	return;
}

bool promising(int start, unsigned nowSum) {
	unsigned maxSum = nowSum + sumFromStart[start];

	if (maxSum >= sum) return true;
	else return false;
}

bool decrypt(int start, unsigned nowSum) {
	//base case 
	if (sum < nowSum)
		return false;
	if (sum == nowSum) {
		//set msg[start + 1] ~ msg[n] to 0
		msg &= ((1LL << (start + 1)) - 1);
		return true;
	}

	//pruning
	if (!promising(start, nowSum))
		return false;

	//recursive call
	if (decrypt(start + 1, nowSum + a[start])) {
		//msg[start] = 1
		msg |= (1LL << start);
		return true;
	}
	else if (decrypt(start + 1, nowSum)) {
		//msg[start] =0
		msg &= ~(1LL << start);
		return true;
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//input
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	cin >> sum;
	
	calcSumFromStart();
	decrypt(1, 0);

	//output
	for (int i = 1; i <= n; ++i){
		if(msg & (1 << i)) cout << "1";
		else cout << "0";
	}

	return 0;
}