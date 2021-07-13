#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 201;
const int IMPOSSIBLE = 2000000;

int n, k;
int value[MAXN][2];
int cache[3][MAXN][MAXN];

//prevState: �� ���� ���� ���� ���
//���� ����: 0
//���� ����: 1
//���� ����: 2
//���� ������ �Ұ���
int minClosedValue(int prevState, int line, int closed) {
	if (closed == k) return 0;
	if (line == n && closed < k) return IMPOSSIBLE;

	int& ret = cache[prevState][line][closed];
	if (ret != -1) return ret;

	if (prevState == 0) {
		ret = minClosedValue(0, line + 1, closed);
		ret = min(ret, value[line][0] + minClosedValue(1, line + 1, closed + 1));
		ret = min(ret, value[line][1] + minClosedValue(2, line + 1, closed + 1));
	}
	if (prevState == 1) {
		ret = minClosedValue(0, line + 1, closed);
		ret = min(ret, value[line][0] + minClosedValue(1, line + 1, closed + 1));
	}
	if (prevState == 2) {
		ret = minClosedValue(0, line + 1, closed);
		ret = min(ret, value[line][1] + minClosedValue(2, line + 1, closed + 1));
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> n >> k;

	int totalValue = 0;
	for (int i = 0; i < n; ++i)
		for(int j = 0; j < 2; ++j){
			cin >> value[i][j];
			totalValue += value[i][j];
		}

	cout << totalValue - minClosedValue(0, 0, 0);
	return 0;
}