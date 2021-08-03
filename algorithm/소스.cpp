#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

//Ç×»ó a > b
int GCD(int a, int b) {
	if (a % b == 0) return b;
	else return GCD(b, a % b);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	cin >> n >> m;

	if (n < m) {
		int tmp = m;
		m = n;
		n = tmp;
	}

	int gcd = GCD(n, m);
	int lcm = n * m / gcd;
	cout << gcd << "\n" << lcm;
	return 0;
}