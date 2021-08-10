#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const int MAXN = 2097152 + 5; // = 2^21  + 5

//Ʈ�� ����, Ʈ�� ��� ��
int k, n;
//<���� ����Ʈ���� �����ϴ� ������ ����ġ, ������ ����Ʈ���� �����ϴ� ������ ����ġ >
vector<pair<ull, ull>> edge (MAXN, make_pair(0,0));

//��� �湮
int visited[MAXN];
//toLeaf[i]: ��� i ~ ���� �Ÿ��� �ִ�
ull toLeaf[MAXN] = { 0 };

//toLeaf[] ��� 
ull getToLeaf(int curnode) {
	visited[curnode] = 1;

	ull maxdist = 0;

	//���� ����Ʈ��
	if ((curnode * 2 <= n) && (visited[curnode * 2] == 0)) {
		if (edge[curnode].first > 0)
			maxdist = max(maxdist, edge[curnode].first + getToLeaf(curnode * 2));
	}
	//������ ����Ʈ��
	if ((curnode * 2 + 1 <= n) && (visited[curnode * 2 + 1] == 0)) {
		if (edge[curnode].second > 0)
			maxdist = max(maxdist, edge[curnode].second + getToLeaf(curnode * 2 + 1));
	}

	toLeaf[curnode] = maxdist;
	return maxdist;
}

//��Ʈ ��忡������ ������ ����ġ ��ȭ
void addWeight(int curnode, int maxdist) {
	visited[curnode] = 1;

	//���� ����Ʈ��
	if ((curnode * 2 <= n) && (visited[curnode * 2] == 0)) {
		if (edge[curnode].first > 0) {
			//���� ������ ����ġ = (��Ʈ~���� �Ÿ��� �ִ� - ���� ����Ʈ��~���� �Ÿ��� �ִ�)
			edge[curnode].first = (maxdist - toLeaf[curnode * 2]);

			//��� ȣ�� -> ���� ����Ʈ���� ���� ����ġ ����
			addWeight(curnode * 2, maxdist - edge[curnode].first);
		}
	}
	//������ ����Ʈ��
	if ((curnode * 2 + 1 <= n) && (visited[curnode * 2 + 1] == 0)) {
		if (edge[curnode].second > 0) {
			//���� ������ ����ġ = (��Ʈ~���� �Ÿ��� �ִ� - ������ ����Ʈ��~���� �Ÿ��� �ִ�)
			edge[curnode].second = (maxdist - toLeaf[curnode * 2 + 1]);

			//��� ȣ�� -> ������ ����Ʈ���� ���� ����ġ ����
			addWeight(curnode * 2 + 1, maxdist - edge[curnode].second);
		}	
	}

	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> k;

	n = pow(2, k + 1) - 1;
	
	//���� ��� ���� ������ ������ ����ġ �Է¹ޱ�
	for (int i = 1; i <= n - pow(2, k); ++i) {
		int w1, w2;
		cin >> w1 >> w2;

		edge[i] = make_pair(w1, w2);
	}

	//��� ~ ���� �Ÿ��� �ִ� toLeaf[] ���
	memset(visited, 0, sizeof(visited));
	getToLeaf(1);

	//��Ʈ�� ����� �������� ����ġ ����
	//��Ʈ ~ ���� �Ÿ��� �ִ�: toLeaf[��Ʈ]
	memset(visited, 0, sizeof(visited));
	addWeight(1, toLeaf[1]);

	//Ʈ���� ������ ����ġ�� �� ���
	ull sum = 0;
	for (int i = 1; i <= n; ++i) {
		sum += edge[i].first;
		sum += edge[i].second;
	}
	cout << sum;

	return 0;
}