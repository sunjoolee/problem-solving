#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<string> words) {

	int N = words.size();

	int answer = 0;

	//�ٸ� �ܾ�� ����� ���̻簡 �ִ� ���, ���̻簡 ������ ������ �ε��� ����
	vector<int> maxPrefix(N, -1);

	for (int i = 0; i < words.size(); ++i) {
		//�˻� ����
		//����� ���λ縦 ���� �ܾ�� ���̿����� ��˻��ǵ��� �˻� ���� ��� �������ֱ� 
		//�� ó������ ��� �ܾ �˻� ������ �ش��
		vector<bool> searchRange(N, true);

		//����� ���̻縦 ���� �ܾ �˻� ������ �鵵�� �� 
		if (maxPrefix[i] != -1) {
			for (int j = 0; j < N; ++j) {
				if (words[j].length() <= maxPrefix[i])
					searchRange[j] = false;
				else if (words[i].substr(0, maxPrefix[i] + 1) != words[j].substr(0, maxPrefix[i] + 1))
					searchRange[j] = false;
			}
		}
		
		//����� �ִ� ���� ���̻� ������ �ܾ���� ��
		if(maxPrefix[i] != -1) 
			answer += maxPrefix[i];
		
		for (int j = maxPrefix[i] + 1; j < words[i].length(); ++j) {
			char searchWord = words[i][j];
			answer++;

			//search ���ڿ��� �˻����� �� �˻� ����� �ϳ��� ��ȯ�Ǵ��� �˻�
			//�� �˻� ����� ���ԵǴ� ��� ���� �˻� �� �˻� ������ �����
			int searchCnt = 1;
			for (int k = 0; k < N; ++k) {
				//�ڱ� �ڽ� ��ŵ
				if (k == i) continue;

				//�˻� ������ ���Ե� �ܾ��� ��� �˻�
				if (searchRange[k]) {
					if (words[k].length() > j && words[k][j] == searchWord) {
						searchCnt++;

						//words[k]�� words[i]�� ���ڿ��� �ε��� 0~j���� ����� ���̻縦 �����ٴ� �ǹ�
						maxPrefix[i] = j;
						maxPrefix[k] = max(maxPrefix[k],j);
					}
					//�˻� ����� ���Ե��� ������ �˻� �������� ����
					else searchRange[k] = false;
				}
			}
			if (searchCnt == 1) break;
		}
	}
	
	return answer;
}

int main() {
	solution({ "go", "gone", "guild" });
}