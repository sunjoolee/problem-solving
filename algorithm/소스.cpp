#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> dot;
typedef vector<dot> polygon;

vector<dot> dots;

int ccw(dot a, dot b) {
	ll cross = a.first * b.second - a.second * b.first;

	if (cross > 0) return 1;
	else if (cross < 0) return -1;
	else return 0;
}

int ccw(dot p, dot a, dot b) {
	a.first -= p.first; a.second -= p.second;
	b.first -= p.first; b.second -= p.second;
	return ccw(a, b);
}

//ccw값을 이용하려 좌회전 여부 검사
bool leftTurn(dot p, dot a, dot b) {
	return ccw(p, a, b) > 0;
}

//퀵 소트를 위한 비교 함수
bool cmp(dot& a, dot& b) {
	dot a0 = make_pair(a.first - dots[0].first, a.second - dots[0].second);
	dot b0 = make_pair(b.first - dots[0].first, b.second - dots[0].second);

	ll cross = a0.first * b0.second - a0.second * b0.first;

	//외적 결과가 0이 아닐 때
	//외적 결과 양수(반시계 방향)이면 true, 음수(시계 방향)이면 false 반환
	if (cross != 0)
		return (cross > 0);

	//외적 결과가 0일 때(평행) 
	//Y좌표가 낮으면 (같다면 X좌표가 낮으면) true 반환
	if (a0.second != b0.second)
		return a0.second < b0.second ;
	return a0.first < b0.first;
}

//모든 노드를 기준점에 대해 반시계 방향으로 정렬(퀵 소트)
void quickSortByAngle(int first, int last) {
	if (first >= last) return;

	//맨 앞의 숫자를 퀵소트의 pivot으로 설정
	int pivot = first;
	int i = first + 1;
	int j = last;

	while (i <= j) {
		while (cmp(dots[i], dots[pivot]) && i <= last) i++;
		while (!cmp(dots[j], dots[pivot]) && j > first) j--;

		if (i >= j) break;

		swap(dots[i], dots[j]);
	}
	swap(dots[pivot], dots[j]);

	quickSortByAngle(first, j - 1);
	quickSortByAngle(j + 1, last);
	return;
}

polygon convexHull() {
	//1. 기준점 찾기
	//가장 Y좌표가 낮은 (같다면 X좌표가 낮은)점을 기준으로 한다
	int minX = 1000000000, minY = 1000000000, minIdx = 0;
	for (int i = 0; i < dots.size(); i++) {
		if (minY > dots[i].second || (minY == dots[i].second && minX > dots[i].first)) {
			minX = dots[i].first;
			minY = dots[i].second;
			minIdx = i;
		}
	}
	//dots[0]가 기준점이 되도록 swap
	swap(dots[minIdx], dots[0]);

	//2. 모든 노드를 기준점에 대해 반시계 방향으로 정렬
	quickSortByAngle(1, dots.size() - 1);

	//3. 기준점부터 시작해서, 순서대로 모든 노드에 대해서 좌회전 여부를 검사
	// 좌회전에 해당하는 선분만 찾은 것 = Convex Hull
	vector<int> stack(dots.size());
	int idx = -1;
	stack[++idx] = 0;
	stack[++idx] = 1;

	int next = 2;
	while (next < dots.size()) {
		while ((idx + 1) >= 2) {
			int second = stack[idx--];
			int first = stack[idx];

			if (leftTurn(dots[first], dots[second], dots[next])) {
				stack[++idx] = second;
				break;
			}
		}
		stack[++idx] = next++;
	}

	//4. 볼록 껍질 반환
	polygon hull;
	for (int i = 0; i < idx + 1; ++i)
		hull.push_back(dots[stack[i]]);
	
	return hull;
}

bool isInside(dot q, const polygon& p) {
	int crosses = 0;
	for (int i = 0; i < p.size(); ++i) {
		int j = (i + 1) % p.size();
		if (p[i].second > q.second != p[j].second > q.second) {
			double atX = (p[j].first - p[i].first)*(q.second - p[i].second) / (p[j].second - p[i].second) + p[i].first;
			if (q.first < atX) {
				++crosses;
			}
		}
	}
	return crosses % 2 > 0;
}


int main(void) {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int N;
	cin >> N;

	dot cow;
	cin >> cow.first >> cow.second;

	for (int i = 0; i < N; i++) {
		ll x, y;
		cin >> x >> y;
		dots.push_back(make_pair(x, y));
	}
	
	int cnt = 0;
	while (true) {
		//더이상 볼록 껍질을 만들 수 없으면 종료
		if (dots.size() < 3) break;

		polygon hull = convexHull();
		//볼록 껍질 내부에 소가 있는지 확인
		if (isInside(cow, hull)) {
			++cnt;
			//dots에서 hull에 포함된 점 제거
			for (int i = 0; i < hull.size(); ++i)
				dots.erase(find(dots.begin(), dots.end(), hull[i]));
		}
		else break;
	}

	cout << cnt;
	return 0;
}