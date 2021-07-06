#include<iostream>
#include<cstring>
#include <algorithm>

using namespace std;

const int MAX = 16;
const int INF = 987654321;

int N;
int W[MAX][MAX];
//cost[node][bitmask]: ���� ��忡�� ���ݱ��� �湮�� ����� ���� bitmask�� ���� �ּ� ���
int cost[MAX][1 << MAX];

int TSP(int node, int bitmask)
{	
	//base case: ��� ��� �湮 �Ϸ�
	//�ٽ� ������ ���÷� ���ƿ� �� �־�� �Ѵ�
	if (bitmask == ((1 << N) - 1)){
		//���� ���� 0�� ��� ���� ����Ǿ����� ���� ���
		if (W[node][0] == 0) 
			return INF;
		else 
			return W[node][0];
	}

	//�Ÿ������̼�
	int& ret = cost[node][bitmask];
	if (ret != -1) return ret;

	ret = INF;
	for (int i = 0; i < N; i++){
		//���� ���� i�� ��� ���� ����Ǿ����� ���� ��� �ǳʶٱ�
		if (W[node][i] == 0) continue;
		//i�� ��� �̹� �湮���� ��� �ǳʶٱ�
		if (bitmask & (1 << i)) continue;

		ret = min(ret, W[node][i] + TSP(i, bitmask | (1 << i)));
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cost, -1, sizeof(cost));

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> W[i][j];

	//0��° ���ú��� ��ȸ ����
	//0��° ���ø� ǥ�õ� bitmask = 00..001
	cout << TSP(0, 1);

	return 0;
}
