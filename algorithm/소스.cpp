#include<iostream>
#include<cstring>
#include <algorithm>

using namespace std;

int N;
int cache[101][10];

int getCnt(int len, int num) {
	//base case
	if (num < 0 || num > 9) return 0;
	if (len == N) return 1;

	int&ret = cache[len][num];
	if (ret != -1) return ret;

	return ret = (getCnt(len + 1, num + 1) + getCnt(len + 1, num - 1)) % 1000000000;
}

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> N;
	
	int cnt = 0;
	for (int num = 1; num <= 9; num++)
		cnt  = (cnt + getCnt(1, num)) % 1000000000;

	cout << cnt;
	return 0;
}
