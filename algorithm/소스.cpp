#include <iostream>
#include <bitset>
using namespace std;

//64 bit (0 ~ 18,446,744,073,709,551,615)
typedef unsigned long long ull;

int n;
int a[41] = { 0 };
unsigned sum;	

//비트마스크 기법 이용
//오른쪽에서 i번째 비트 = msg[i]
ull msg = 0;

bool promising(int start, unsigned nowSum) {
	unsigned maxSum = nowSum;
	
	for (int i = start; i <= n; ++i) {
		maxSum += a[i];
		if (maxSum >= sum)
			return true;
	}

	return false;
}

bool decrypt(int start, unsigned nowSum) {
	//base case 
	if (sum < nowSum)
		return false;
	if (sum == nowSum) {
		//msg[start + 1] ~ msg[n] 0으로 set
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

	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	cin >> sum;

	decrypt(1, 0);

	for (int i = 1; i <= n; ++i){
		msg /= 2;
		cout << msg % 2;
	}

	return 0;
}