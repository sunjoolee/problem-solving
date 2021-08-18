#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

//ū �� ���� �˰���
string addString(string a, string b) {
	ll carry = 0;
	string result = "";

	while (!a.empty() || !b.empty() || carry) {
		if (!a.empty()) {
			carry += a.back() - '0';
			a.pop_back();
		}

		if (!b.empty()) {
			carry += b.back() - '0';
			b.pop_back();
		}

		result += ((carry % 10) + '0');
		carry /= 10;
	}

	reverse(result.begin(), result.end());
	return result;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string a, b;
	cin >> a >> b;

	cout << addString(a, b);

	return 0;

}