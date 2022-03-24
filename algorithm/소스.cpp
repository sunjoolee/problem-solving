#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode{
	int idx;
	int x;
	int y;
	TreeNode *Left;
	TreeNode *Right;
};

bool cmp(TreeNode A, TreeNode B){
	if (A.y > B.y) return true;
	else if (A.y == B.y) return(A.x < B.x);
	else return false;
}

void makeTree(TreeNode *root, TreeNode * child){
	//left child
	if (root->x > child->x){
		if (root->Left == NULL){
			root->Left = child;
			return;
		}
		makeTree(root->Left, child);
	}
	//right child
	else{
		if (root->Right == NULL){
			root->Right = child;
			return;
		}
		makeTree(root->Right, child);
	}
}

void PreOrder(TreeNode *root, vector<int> &answer){
	if (root == NULL) return;
	
	answer.push_back(root->idx);
	PreOrder(root->Left, answer);
	PreOrder(root->Right, answer);
}

void PostOrder(TreeNode *root, vector<int> &answer){
	if (root == NULL) return;
	
	PostOrder(root->Left, answer);
	PostOrder(root->Right, answer);
	answer.push_back(root->Idx);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo){
	vector<vector<int>> answer;
	
	vector<TreeNode> Tree;

	for (int i = 0; i < nodeinfo.size(); i++){
		int x = nodeinfo[i][0];
		int y = nodeinfo[i][1];
		int idx = i + 1;
		Tree.push_back({ idx, x, y, NULL, NULL });
	}

	sort(Tree.begin(), Tree.end(), cmp);
	TreeNode *root = &Tree[0];

	//모든 노드를 root를 루트로하는 이진 트리에 삽입
	for (int i = 1; i < Tree.size(); i++) {
		makeTree(root, &Tree[i]);
	}

	vector<int> Pre_V; 
	PreOrder(root, Pre_V);
	
	vector<int> Post_V;    
	PostOrder(root, Post_V);
	
	answer.push_back(Pre_V);
	answer.push_back(Post_V);
	return answer;
}
