#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const ull MAX_TIME = (ull)2000000000 * (ull)30;

int N, M;
int durtime[10001];

int main(void){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; i++)
		cin >> durtime[i];

	//사람 수가 놀이기구 수보다 작거나 같은 경우
	//놀이기구 번호가 작은 것 부터 하나씩 차례대로 탑승한다
	if (N <= M){
		cout << N;
		return 0;
	}

	//N명의 사람이 모두 놀이기구를 탑승하게 되는 최소 시간 (이분 탐색)
	ull minTime = MAX_TIME;

	ull low = 0;
	ull high = MAX_TIME;
	for (int it = 0; it < 100; ++it) {
		ull mid = (low + high) / 2;

		//결정 문제: x분동안 N명의 사람이 놀이기구에 탑승할 수 있는가?
		//0초에 모든 놀이기구에 한 사람씩 탑승하므로 cnt = M부터 시작
		ull cnt = M;
		for (int i = 0; i < M; i++)
			cnt += mid / durtime[i];

		if (cnt >= N) {
			minTime =min(minTime, mid);
			high = mid;
		}
		else low = mid;
	}

	//마지막 사람이 타는 놀이기구의 번호 구하기!
	
	//minTime - 1 시간까지 놀이기구에 탑승하게 되는 사람 수
	ull cnt = M;
	for (int i = 0; i < M; i++) 
		cnt += (minTime - 1) / durtime[i];
	

	// minTime 시간에 놀이기구에 탑승하게 되는 사람 수
	for (int i = 0; i < M; i++){
		if (minTime % durtime[i] == 0)
			++cnt;

		if (cnt == N){
			cout << i + 1;
			return 0;
		}
	}

	return 0;
}
