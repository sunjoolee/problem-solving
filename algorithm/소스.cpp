#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int n, m;
vector<int> arr;

void makeArr(int lastNum) {
	//더 고를 수 있는 수 없음 -> base case
	if (arr.size() == m) {
		for (int i = 0; i < m; ++i) {
			cout << arr[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int num = lastNum + 1; num <= n; ++num) {
		arr.push_back(num);
		makeArr(num);
		arr.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	
	cin >> n >> m;

	makeArr(0);

	return 0;
}