#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		vector<int> score;
		for (int i = 0; i < 5; ++i) {
			int input;
			cin >> input;
			score.push_back(input);
		}

		sort(score.begin(), score.end());

		if (abs(score[1] - score[3]) >= 4) cout << "KIN\n";
		else cout << score[1] + score[2] + score[3] << "\n";
	}

	return 0;
}