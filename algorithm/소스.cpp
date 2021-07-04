#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MIN = - 1001;

int N, S, M;
int V[100];
int cache[100][1000];

//i��° ���� �����ϱ� ��~������ ���� ������ �� ���� ������ ��ȭ�� �ִ밪
int getVolumeChange(int i, int sumOfVolumeChange) {
	//base case
	if (sumOfVolumeChange > (M-S)) return MIN;
	if (sumOfVolumeChange < (0-S)) return MIN;
	if (i == N) return sumOfVolumeChange;

	//�޸������̼�
	int& ret = cache[i][sumOfVolumeChange];
	if (ret != -1) return ret;

	return ret = max(getVolumeChange(i+1, sumOfVolumeChange + V[i]), getVolumeChange(i + 1, sumOfVolumeChange - V[i]));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for(int i = 0; i<100; ++i)
		memset(cache[i], -1, sizeof(cache[i]));
	
	cin >> N >> S >> M;
	for (int i = 0; i < N; ++i)
		cin >> V[i];

	int volumeChange = getVolumeChange(0, 0);

	if (volumeChange == MIN) cout << -1;
	else cout << S + volumeChange;
	return 0;
}