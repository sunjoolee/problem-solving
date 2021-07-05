#include <iostream>
#include <algorithm>
using namespace std;

int N;
//index 1~N
int requiredJob[101]; 
int requiredTime[101]; 
int jobFinishedTime[101] = { 0 };

int getTotalTime() {
	int ret = 0;

	for (int i = 1; i <= N; ++i) {
		jobFinishedTime[i] = jobFinishedTime[requiredJob[i]] + requiredTime[i];
		ret = max(ret, jobFinishedTime[i]);
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; ++i) {
		cin >> requiredTime[i];

		int n;
		cin >> n;
		for (int j = 1; j <= n; ++j)
			cin >> requiredJob[i];
	}
	
	cout << getTotalTime();
	return 0;
}