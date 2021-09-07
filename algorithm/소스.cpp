#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

//죄표의 최댓값
const double MAXX = 1001;

typedef pair<double, double> dot;
typedef vector<dot> polygon;

//0. dot 연산

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


//1. 그라함 스캔

//퀵 소트를 위한 비교 함수
bool cmp(dot p, dot a, dot b) {
	double cross = ccw(p, a, b);

	if (cross != 0)
		return (cross > 0);

	//세 점이 한 직선 위에 있는 경우 p와 가까운 점이 앞에 오도록 
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

//기준점을 찾기 위한 비교 함수
bool cmp2(dot a, dot b) {
	//기준점: y좌표가 가장 작은 점 (y좌표가 같다면 x좌표가 가장 작은 점) 
	if (a.second < b.second) return true;
	if (a.second == b.second) return a.first < b.first;
	return false;
}

polygon convexHull(vector<dot>& dots) {
	
	//기준점 dots[0]
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

	//볼록 껍질에 포함되게 되는 점의 개수 = idx + 1
	polygon hull;
	for (int i = 0; i < idx + 1; ++i)
		hull.push_back(dots[stack[i]]);

	return hull;
}

//2. 회전하는 캘리퍼스 

//시계 반대 방향으로 주어진 볼록 다각형 p
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

	//소수점 아래 7자리까지 출력하도록 설정
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