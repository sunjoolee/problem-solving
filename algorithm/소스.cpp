#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> dot;
typedef vector<dot> polygon;

//집합에 포함된 격자점의 좌표
vector<dot> points;

//dot a -  dot b
dot dot_minus(dot a, dot b) {
	return { a.first - b.first, a.second - b.second };
}

double norm(dot a) {
	return hypot(a.first, a.second);
}

int ccw(dot a, dot b) {
	return a.first * b.second - a.second * b.first;
}

int ccw(dot p, dot a, dot b) {
	a = dot_minus(a, p); 
	b = dot_minus(b, p);
	return ccw(a, b);
}

//y가 가장 크고 x가 가장 작은 점이 맨 앞에 오도록 정렬
bool cmp(dot& a, dot& b) {
	if (a.second > b.second) return true;
	if (a.second == b.second) return a.first < b.first;
	return false;
}

void giftWrap() {
	int n = points.size();
	
	sort(points.begin(), points.end(), cmp);
	dot pivot = points[0];
	
	polygon hull;
	hull.push_back(pivot);

	while (true) {
		//ph에서 시작하는 벡터가 가장 왼쪽인 점 next를 찾는다 
		//평행인 점이 여러 개 있으면 가장 먼 것을 선택한다
		dot ph = hull.back();
		dot next = points[0];
		for (int i = 1; i < n; ++i) {
			double cross = ccw(ph, next, points[i]);
			double dist = norm(dot_minus(next, ph)) - norm(dot_minus(points[i], ph));

			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		//시작점으로 돌아온 경우 종료
		if (next == pivot) break;

		//next를 볼록 껍질에 포함시킨다
		hull.push_back(next);
	}

	cout << hull.size() << "\n";
	for (auto it = hull.begin(); it != hull.end(); ++it)
		cout << it->first << " " << it->second << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int P;
	cin >> P;
	while (P--) {
		points.clear();
		
		int N;
		cin >> N;
		for (int i = 0; i < N; ++i) {
			int x, y;
			cin >> x >> y;
			points.push_back({ x,y });
		}

		giftWrap();
	}
	return 0;
}