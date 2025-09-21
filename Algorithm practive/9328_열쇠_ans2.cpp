#define _CRT_SECURE_NO_WARNINGS
/*
	---- 9328_���� ----
	�ٽ� ���� : ���� ���� ���踦 �߰��� ����, ���ư��� ���·� ������ �ϰ� �Ǹ�
	O(n^3)�� �ð� ���⵵�� ����.
	����, �� ����� ����� �� ����.

	�ذ��� : DFS�� queue�� ����Ѵٴ� ������ ����.
	Ű�� ���� ��� �ش� Ű�� ������ �־����� üũ.
	�������, �ش� Ű�� ������ �ִٰ� ǥ���� ��, �ش� Ű�� ���� Ž������ ���ߴ� ��ϵ��� ��ǥ��
	��� queue�� push��.

	��� ��ǥ�� ���� �ƴҰ�� �ӽ÷� Ž����.
	���⼭ ���ϰ�� : �ش� ���� ���� Ű�� ���ٸ�, ���� ���ĺ��� �ش��ϴ� ť�� �ش� ���� ��ǥ�� ����ְ� continue;
	���⼭ Ű�ϰ�� : �ش� Ű�� �̹� �����Ѵٸ� Ž���� ����, �ش� Ű�� �������� �ʴ´ٸ� ������ ����� ��� Ž������ ���ߴ� ��ϵ���
						��ǥ�� �߰�.
	�� ���� ��쿣 ����� �����¿츦 Ž����.
*/


#include<stdio.h>
#include<queue>
#include<string.h>
using namespace std;

typedef struct _crd {
	int x;
	int y;
}crd;


queue<crd>lockedDoors[27];
queue<crd>forBFS;
int t, h, w;
int cnt;
bool keyHave[27];
bool visited[105][105];
char map[105][105];

void initialize() {
	cnt = 0;
	for (int i = 0; i < 27; i++) {
		keyHave[i] = false;
		while (!lockedDoors[i].empty()) {
			lockedDoors[i].pop();
		}
	}

	for (int i = 1; i <= 100; i++) {
		for (int q = 1; q <= 100; q++) {
			map[i][q] = 0;
			visited[i][q] = false;
		}
	}
}

void mapInput() {
	char hasKey[50] = {};
	scanf("%d %d", &h, &w);
	for (int i = 1; i <= h; i++) {
		for (int q = 1; q <= w; q++) {
			scanf(" %c", &map[i][q]);
			if (i == 1 || i == h || q == 1 || q == w)
				if(map[i][q] != '*')
					forBFS.push({ i, q });
		}
	}

	scanf(" %s", hasKey);
	for (int i = 0; i < strlen(hasKey); i++) {
		if (hasKey[i] >= 'a' || hasKey[i] <= 'z')
			keyHave[hasKey[i] - 'a'] = true;
	}
}

void BFS() {
	while (!forBFS.empty()) {
		crd curr = forBFS.front();
		char currBlock = map[curr.x][curr.y];

		if (visited[curr.x][curr.y] == true) {
			forBFS.pop();
			continue;
		}

		if (currBlock >= 'A' && currBlock <= 'Z' ) { // ���� �ش� ����� ���̶��
			if (keyHave[currBlock - 'A'] == false) {
				lockedDoors[currBlock - 'A'].push(curr);
				forBFS.pop();
				continue;
			} // ���� �� �� ���� ����� locked�� �ΰ�, �ƴϸ� ����Ž��
		}

		if (currBlock >= 'a' && currBlock <= 'z') { // ���� �ش� ����� Ű���
			if(keyHave[currBlock-'a'] == false){
				keyHave[currBlock - 'a'] = true;
				while (!lockedDoors[currBlock - 'a'].empty()) {
					forBFS.push(lockedDoors[currBlock - 'a'].front());
					lockedDoors[currBlock - 'a'].pop();
				}
			} // ���������� ���� Ű�� ����������� �׿� �����ϴ� ���� �� �湮���� ���� ������ ��� ť�� push
		}
		
		if (currBlock == '$') { 
			//printf("treasure Found :: %d %d\n", curr.x, curr.y);
			cnt++; 
		}
		visited[curr.x][curr.y] = true;

		if (curr.x > 1 && visited[curr.x - 1][curr.y] == false && map[curr.x - 1][curr.y] != '*')
			forBFS.push({ curr.x - 1, curr.y });
		if (curr.x < h && visited[curr.x + 1][curr.y] == false && map[curr.x + 1][curr.y] != '*')
			forBFS.push({ curr.x + 1, curr.y });
		if (curr.y > 1 && visited[curr.x][curr.y - 1] == false && map[curr.x][curr.y - 1] != '*')
			forBFS.push({ curr.x, curr.y - 1 });
		if (curr.y < w && visited[curr.x][curr.y + 1] == false && map[curr.x][curr.y + 1] != '*')
			forBFS.push({ curr.x, curr.y + 1 });
		
		forBFS.pop();
	}
}


int main() {
	scanf("%d", &t);
	for (int _ = 0; _ < t; _++) {
		initialize();
		mapInput();
		BFS();

		printf("%d\n", cnt);
	}

}