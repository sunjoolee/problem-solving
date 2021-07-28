#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector<string> coin;

	for (int i = 0; i < n; ++i) {
		string input;
		cin >> input;
		coin.push_back(input);
	}
	
	int minT = 401;

	//모든 행에 대해서 뒤집을지 말지 결정
	for (ull k = 0; k < (1 << n); ++k) {
		//전체 동전 뒷면의 개수;
		int totalT = 0;

		for (int j = 0; j < n; ++j) {

			//현재 열에서 동전 뒷면의 개수
			int colT = 0;
			for (int i = 0; i < n; ++i) {
				char now;

				//i번 째 행을 뒤집기로 결정된 경우
				if ((1 << i) & k) {
					if (coin[i][j] == 'T') now = 'H';
					if (coin[i][j] == 'H') now = 'T';
				}
				else now = coin[i][j];

				if (now == 'T') ++colT;
			}
			
			//열을 뒤집는 경우와 뒤집지 않는 경우 중 동전 뒷면의 개수 적게 만드는 경우를 선택
			totalT += min(n - colT, colT);
		}

		minT = min(minT, totalT);
	}

	cout << minT;
	return 0;
}