#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 2001;

int num[MAXN];
int cache[MAXN][MAXN];

bool palindrome(int s, int e) {
	if (s >= e) return true;

	int& ret = cache[s][e];
	if (ret != -1) return ret;

	if (num[s] == num[e])
		return ret = palindrome(s + 1, e - 1);
	else 
		return ret = false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < MAXN; ++i)
		memset(cache[i], -1, sizeof(cache[i]));

	int N, M;
	cin >> N ;
	for (int i = 1; i <= N; ++i)
		cin >> num[i];
	cin >> M;
	for (int i = 0; i < M; ++i) {
		int s, e;
		cin >> s >> e;
		cout << palindrome(s, e) << "\n";
	}

	return 0;
}

