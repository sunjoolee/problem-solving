#include<iostream>
#include<queue>

#define MAX 2000
using namespace std;

int S;

//Visit[screen][clipBoard]
bool Visit[MAX][MAX];

int BFS(){
	//queue of pair<pair<screen, clipBoard>, time>
	queue<pair<pair<int, int>, int> > Q;

	Q.push(make_pair(make_pair(1, 0), 0));
	Visit[1][0] = true;    

	while (Q.empty() == 0)
	{
		int screen = Q.front().first.first;
		int clipBoard = Q.front().first.second;
		int time = Q.front().second;
		Q.pop();

		//base case
		if (screen == S) return time;

		//copy
		if (screen > 0 && screen < MAX) {
			if (Visit[screen][screen] == false) {
				Visit[screen][screen] = true;
				Q.push(make_pair(make_pair(screen, screen), time + 1));
			}
		}
		//paste
		if (clipBoard > 0 && screen + clipBoard < MAX){
			if (Visit[screen + clipBoard][clipBoard] == false){
				Visit[screen + clipBoard][clipBoard] = true;
				Q.push(make_pair(make_pair(screen + clipBoard, clipBoard), time + 1));
			}
		}
		//sub
		if (screen > 0 && screen < MAX) {
			if (Visit[screen - 1][clipBoard] == false){
				Visit[screen - 1][clipBoard] = true;
				Q.push(make_pair(make_pair(screen - 1, clipBoard), time + 1));
			}
		}
	}
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> S;

	int R = BFS();
	cout << R;

	return 0;
}

