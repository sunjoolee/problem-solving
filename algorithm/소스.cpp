#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int n, m;
vector<bool> used;
vector<int> arr;

void makeArr(int len) {
	if (len == m) {
		for (int i = 0; i < len; ++i) {
			cout << arr[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int num = 1; num <= n; ++num) {
		if (used[num] == true) continue;
		
		used[num] = true;
		arr.push_back(num);

		makeArr(len + 1);

		arr.pop_back();
		used[num] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	
	cin >> n >> m;

	for (int i = 0; i <= n; ++i) {
		used.push_back(false);
	}

	makeArr(0);

	return 0;
}