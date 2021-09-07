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

//0. dot ����

dot dot_minus(dot a, dot b) {
	return {a.first - b.first, a.second - b.second};
}

double ccw(dot a, dot b) {
	return a.first * b.second - a.second * b.first;
}

double ccw(dot p, dot a, dot b) {
	a = dot_minus(a, p);
	b = dot_minus(b, p);
	return ccw(a, b);
}

bool leftTurn(dot p, dot a, dot b) {
	return ccw(p, a, b) > 0;
}

double norm(dot a) {
	return hypot(a.first, a.second);
}

dot normalize(dot a) {
	return { a.first / norm(a), a.second / norm(a) };
}

double dot_product(dot a, dot rhs) {
	return a.first * rhs.first + a.second * rhs.second;
}


//1. �׶��� ��ĵ

//�� ��Ʈ�� ���� �� �Լ�
bool cmp(dot p, dot a, dot b) {
	double cross = ccw(p, a, b);

	if (cross != 0)
		return (cross > 0);

	//�� ���� �� ���� ���� �ִ� ��� p�� ����� ���� �տ� ������ 
	double dist1 = norm(dot_minus(p, a));
	double dist2 = norm(dot_minus(p, b));
	if (dist1 < dist2) return true;
	return false;
}

void quickSortByAngle(vector<dot>& dots, int first, int last) {
	if (first >= last) return;

	int pivot = first;
	int i = first + 1;
	int j = last;

	while (i <= j) {
		while (i <= last && cmp(dots[0], dots[i], dots[pivot])) i++;
		while (j > first && !cmp(dots[0], dots[j], dots[pivot])) j--;

		if (i >= j) break;

		swap(dots[i], dots[j]);
	}
	swap(dots[pivot], dots[j]);

	quickSortByAngle(dots, first, j - 1);
	quickSortByAngle(dots, j + 1, last);
	return;
}

//�������� ã�� ���� �� �Լ�
bool cmp2(dot a, dot b) {
	//������: y��ǥ�� ���� ���� �� (y��ǥ�� ���ٸ� x��ǥ�� ���� ���� ��) 
	if (a.second < b.second) return true;
	if (a.second == b.second) return a.first < b.first;
	return false;
}

polygon convexHull(vector<dot>& dots) {
	
	//������ dots[0]
	sort(dots.begin(), dots.end(), cmp2);
	
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
	double ret = norm(dot_minus(p[right], p[left]));

	vector<dot> toNext(n);
	for (int i = 0; i < n; ++i) {
		int next;
		i - 1 < 0 ? next = n - 1 : next = i - 1;
		toNext[i] = normalize(dot_minus(p[next], p[i]));
	}

	int a = left, b = right;
	while (a != right || b != left) {
		double cosThetaA = dot_product(calipersA, toNext[a]);
		double cosThetaB = dot_product(dot_minus({ 0,0 }, calipersA), toNext[b]);

		if (cosThetaA > cosThetaB) {
			calipersA = toNext[a];
			a - 1 < 0 ? a = n - 1 : --a;
		}
		else {
			calipersA = dot_minus({ 0,0 }, toNext[b]);
			b - 1 < 0 ? b = n - 1 : --b;
		}
		ret = max(ret, norm(dot_minus(p[a], p[b])));
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

	//�Ҽ��� �Ʒ� 7�ڸ����� ����ϵ��� ����
	cout << fixed;
	cout.precision(7);

	if (C < 3) {
		double ret = 0.0;
		for (int i = 0; i < C; ++i) {
			for (int j = 0; j < C; ++j) {
				ret = max(ret, norm(dot_minus(dots[i], dots[j])));
			}
		}
		cout << ret;
		return 0;
	}

	polygon hull = convexHull(dots);
	cout << diameter(hull);
	return 0;
}