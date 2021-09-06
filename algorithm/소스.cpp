#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

//��ǥ�� �ִ�
const double MAXX = 1001;

typedef pair<double, double> dot;
typedef vector<dot> polygon;

double ccw(dot a, dot b) {
	return a.first * b.second - a.second * b.first;
}

double ccw(dot p, dot a, dot b) {
	a.first -= p.first; a.second -= p.second;
	b.first -= p.first; b.second -= p.second;
	return ccw(a, b);
}

bool leftTurn(dot p, dot a, dot b) {
	return ccw(p, a, b) > 0;
}

double norm(dot a) {
	return hypot(a.first, a.second);
}

double dot_product(dot a, dot rhs) {
	return a.first * rhs.first + a.second * rhs.second;
}

dot normalize(dot a) {
	return { a.first / norm(a), a.second / norm(a) };
}


//1. �׶��� ��ĵ

//�� ��Ʈ�� ���� �� �Լ�
bool cmp(vector<dot>& dots, dot& a, dot& b) {
	double cross = ccw(dots[0], a, b);
	
	//�� ���� �� ���� ���� ���� ���� ��� �ݽð� �������� ����
	if (cross != 0)
		return (cross > 0);

	//�� ���� �� ���� ���� �ִ� ��� p[0]�� ����� ���� �տ� ������ ����
	if (norm({dots[0].first - a.first, dots[0].second - a.second }) < norm({dots[0].first - b.first, dots[0].second - b.second}))
		return true;
	return false;
}

//��� ��带 �������� ���� �ݽð� �������� ����(�� ��Ʈ)
void quickSortByAngle(vector<dot>& dots, int first, int last) {
	if (first >= last) return;

	int pivot = first;
	int i = first + 1;
	int j = last;

	while (i <= j) {
		while (i <= last && cmp(dots, dots[i], dots[pivot])) i++;
		while (j > first && !cmp(dots, dots[j], dots[pivot])) j--;

		if (i >= j) break;

		swap(dots[i], dots[j]);
	}
	swap(dots[pivot], dots[j]);

	quickSortByAngle(dots, first, j - 1);
	quickSortByAngle(dots, j + 1, last);
	return;
}

polygon convexHull(vector<dot>& dots) {
	double minX = MAXX, minY = MAXX;
	int minIdx = 0;

	//y��ǥ�� ���� ���� �� (y��ǥ�� ���ٸ� x��ǥ�� ���� ���� ��) 
	for (int i = 0; i < dots.size(); i++) {
		if (minY > dots[i].second || (minY == dots[i].second && minX > dots[i].first)) {
			minX = dots[i].first;
			minY = dots[i].second;
			minIdx = i;
		}
	}
	swap(dots[minIdx], dots[0]);

	quickSortByAngle(dots, 1, dots.size() - 1);

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

	//���� ������ ���Եǰ� �Ǵ� ���� ���� = idx + 1
	polygon hull;
	for (int i = 0; i < idx + 1; ++i)
		hull.push_back(dots[stack[i]]);

	return hull;
}

//2. ȸ���ϴ� Ķ���۽� 

//�ð� �ݴ� �������� �־��� ���� �ٰ��� p
double diameter(const polygon& p) {
	int n = p.size();

	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();

	dot calipersA = { 0, 1 };
	double ret = norm({ p[right].first - p[left].first, p[right].second - p[left].second });

	vector<dot> toNext(n);
	for (int i = 0; i < n; ++i)
		toNext[i] = normalize({ p[(i + 1) % n].first - p[i].first, p[(i + 1) % n].second - p[i].second });

	int a = left, b = right;
	while (a != right || b != left) {
		double cosThetaA = dot_product(calipersA, toNext[a]);
		double cosThetaB = dot_product({ -calipersA.first, -calipersA.second }, toNext[b]);

		if (cosThetaA > cosThetaB) {
			calipersA = toNext[a];
			a = (a + 1) % n;
		}
		else {
			calipersA = { -toNext[b].first, -toNext[b].second };
			b = (b + 1) % n;
		}
		ret = max(ret, norm({ p[a].first - p[b].first , p[a].second - p[b].second }));
	}

	return ret;
}

int main(void) {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int C;
	cin >> C;

	vector<dot> dots;

	for (int i = 0; i < C; ++i) {
		double x, y;
		cin >> x >> y;
		dots.push_back({ x,y });
	}

	//�Ҽ��� �Ʒ� 7�ڸ����� ���
	cout << fixed;
	cout.precision(7);

	if (C < 3) {
		double ret = 0.0;
		for (int i = 0; i < C; ++i) {
			for (int j = 0; j < C; ++j) {
				ret = max(ret, norm({ dots[i].first - dots[j].first, dots[i].second - dots[j].second }));
			}
		}
		cout << ret;
		return 0;
	}

	polygon hull = convexHull(dots);
	cout << diameter(hull);
	return 0;
}