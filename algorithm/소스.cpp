
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int k;
	cin >> k;
	for (int i = 0; i < k; ++i) {
		cout << "Class " << i + 1<<"\n";
		int n;
		cin >> n;

		vector<int> vec;
		for (int j = 0; j < n; ++j) {
			int input;
			cin >> input;
			vec.push_back(input);
		}
		sort(vec.begin(), vec.end());
		
		int gap = -1;
		for (int j = 0; j < vec.size() - 1; ++j) {
			gap = max(gap, vec[j + 1] - vec[j]);
		}

		cout << "Max " << vec[vec.size() - 1];
		cout << ", ";
		cout << "Min " << vec[0];
		cout << ", ";
		cout << "Largest gap " << gap << "\n";
	}
	return 0;
}