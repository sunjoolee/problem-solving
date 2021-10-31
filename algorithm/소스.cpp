#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
char map[50][50];

int dir_R[4] = { 0, 0, 1, -1 };
int dir_C[4] = { -1, 1, 0, 0 };

//�켱���� ť�� ���� ����ü
struct pq_struct {
	pair<int, int> location;
	pair<int, int> garbage;
};

//�켱���� ����� ���� ����ü
struct compare {
	bool operator() (pq_struct& a, pq_struct& b) {
		if (a.garbage.first > b.garbage.first) return true;
		if (a.garbage.first == b.garbage.first)
			return a.garbage.second > b.garbage.second;
		return false;
	}
};

void dijkstra(pair<int, int> start, pair<int, int> flower) {
	pair<int, int> min_garbage[50][50];
	//�ʱ�ȭ
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) {
			min_garbage[i][j] = { -1, -1 };
		}
	}
	min_garbage[start.first][start.second] = { 0,0 };
 
	priority_queue<pq_struct, vector<pq_struct>, compare> pq;
	pq.push({ start, { 0 , 0 } });

	while (!pq.empty()) {
		pair<int, int> here = pq.top().location;
		pair<int, int> garbage = pq.top().garbage;
		pq.pop();

		//�� ���� ��ΰ� �̹� �߰ߵǾ��ٸ� ����
		if (min_garbage[here.first][here.second].first != -1 && min_garbage[here.first][here.second] < garbage) continue;


		//���� ��ġ�� ���� ��ġ�� ���
		if (here == flower) {
			cout << garbage.first << " " << garbage.second;
			return;
		}

		//���� ��ġ�� ������ ĭ�� ���
		if (map[here.first][here.second] == 'g') {
			garbage.first++;
		}
		//���� ��ġ�� ����ְ�, ������� ������ ĭ�� ���
		else if (map[here.first][here.second] == '.') {
			for (int i = 0; i < 4; ++i) {
				int adj_R = here.first + dir_R[i];
				int adj_C = here.second + dir_C[i];
			
				if (adj_R < 0 || adj_R >= N) continue;
				if (adj_C < 0 || adj_C >= M) continue;

				if (map[adj_R][adj_C] == 'g') {
					garbage.second++;
					break;
				}
			}
		}

		//���� ��ġ�� �̵�
		for (int i = 0; i < 4; ++i) {
 			pair<int, int> there = {here.first + dir_R[i], here.second + dir_C[i]};

			if (there.first < 0 || there.first >= N) continue;
			if (there.second < 0 || there.second >= M) continue;

			if (min_garbage[there.first][there.second].first == -1 || min_garbage[there.first][there.second] > garbage) {
				min_garbage[there.first][there.second] = garbage;
				pq.push({there, garbage});
			}
		}
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);

	cin >> N >> M;

	pair<int, int> start, flower;
	for (int i = 0; i < N; ++i) {
		string input;
		cin >> input;

		for (int j = 0; j < M; ++j) {
			map[i][j] = input[j];
			if (map[i][j] == 'S'|| map[i][j] == 's') start = { i, j };
			if (map[i][j] == 'F'|| map[i][j] == 'f') flower = { i, j };
		}
	}

	dijkstra(start, flower);
	return 0;
}