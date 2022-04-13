#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 987654321;

int N;

vector<vector<int>>dist(200, vector<int>(200, INF));

//플로이드-와샬 알고리즘
void floyd() {
	for (int i = 0; i < N; ++i) {
		dist[i][i] = 0;
	}

	//i지점 -> j지점으로 이동할 때 거쳐가는 지점 K
	for (int k = 0; k < N; ++k) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				dist[j][i] = dist[i][j];
			}
		}
	}
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {

	N = n;

	s--;
	a--;
	b--;

	for (int i = 0; i < fares.size(); ++i) {
		int c = --fares[i][0];
		int d = --fares[i][1];
		int f = fares[i][2];

		dist[c][d] = f;
		dist[d][c] = f;
	}

	floyd();

	int answer = dist[s][a] + dist[s][b];

	for (int i = 0; i < N; ++i) {
		answer = min(answer, dist[s][i] + dist[i][a] + dist[i][b]);
	}

	return answer;
}

int main() {
	solution(7, 3, 4, 1, { {5, 7, 9},{4, 6, 4},{3, 6, 1},{3, 2, 3},{2, 1, 6} });
}