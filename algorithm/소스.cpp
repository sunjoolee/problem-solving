#include <iostream>
using namespace std;

//64 bit (0 ~ 18,446,744,073,709,551,615)
typedef unsigned long long ull;

int n;
ull a[41] = { 0 };
ull s; // 0 ~ 2000000000
int msg[41] = { 0 };

bool decrypt(int start, ull sum) {
	//base case
	if (s == sum) {
		for (int j = start + 1; j <= n; ++j)
			msg[j] = 0;
		return true;
	}
	if (s < sum || start > n)
		return false;

	//recursive call
	if (decrypt(start + 1, sum + a[start])) {
		msg[start] = 1;
		return true;
	}
	else if (decrypt(start + 1, sum)) {
		msg[start] = 0;
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
	cin >> s;

	decrypt(1, 0);

	for (int i = 1; i <= n; ++i)
		cout << msg[i];

	return 0;
}