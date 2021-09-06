#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> dot;
typedef vector<dot> polygon;

//���տ� ���Ե� �������� ��ǥ
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

//y�� ���� ũ�� x�� ���� ���� ���� �� �տ� ������ ����
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
		//ph���� �����ϴ� ���Ͱ� ���� ������ �� next�� ã�´� 
		//������ ���� ���� �� ������ ���� �� ���� �����Ѵ�
		dot ph = hull.back();
		dot next = points[0];
		for (int i = 1; i < n; ++i) {
			double cross = ccw(ph, next, points[i]);
			double dist = norm(dot_minus(next, ph)) - norm(dot_minus(points[i], ph));

			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		//���������� ���ƿ� ��� ����
		if (next == pivot) break;

		//next�� ���� ������ ���Խ�Ų��
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