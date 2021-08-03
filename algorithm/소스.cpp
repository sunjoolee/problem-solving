#include <iostream>
#include <string>
using namespace std;


int n;

//현재까지 만든 string의 길이 len
void good(string str, int len) {
	//좋은 수열인지 판단
	if (str.size() > 1) {
		for (int s = 1; s <= str.size() / 2; ++s)
			if (str.substr(str.size() - s, s) == str.substr(str.size() - 2 * s, s))
				return;
	}
	
	//base case
	if (len == n) {
		cout << str;
		exit(0);
	}

	//숫자 후보 1,2,3
	good(str + '1', len + 1);
	good(str + '2', len + 1);
	good(str + '3', len + 1);

	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> n;

	good("", 0);
	return 0;
}