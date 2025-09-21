#define _CRT_SECURE_NO_WARNINGS
/*
	---- 9328_열쇠 ----
	핵심 문제 : 문을 여는 열쇠를 발견한 이후, 돌아가는 형태로 연산을 하게 되면
	O(n^3)의 시간 복잡도를 가짐.
	따라서, 이 방법은 사용할 수 없음.

	해결방안 : DFS는 queue를 사용한다는 점에서 착안.
	키를 얻을 경우 해당 키를 가지고 있었는지 체크.
	없을경우, 해당 키를 가지고 있다고 표시한 뒤, 해당 키가 없어 탐색하지 못했던 블록들의 좌표를
	모두 queue에 push함.

	모든 좌표는 벽이 아닐경우 임시로 탐색함.
	여기서 문일경우 : 해당 문에 대한 키가 없다면, 문의 알파벳에 해당하는 큐에 해당 문의 좌표를 집어넣고 continue;
	여기서 키일경우 : 해당 키가 이미 존재한다면 탐색만 진행, 해당 키가 존재하지 않는다면 위에서 언급한 대로 탐색하지 못했던 블록들의
						좌표를 추가.
	그 외의 경우엔 평범히 상하좌우를 탐색함.
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

		if (currBlock >= 'A' && currBlock <= 'Z' ) { // 만약 해당 블록이 문이라면
			if (keyHave[currBlock - 'A'] == false) {
				lockedDoors[currBlock - 'A'].push(curr);
				forBFS.pop();
				continue;
			} // 아직 갈 수 없는 블록은 locked에 두고, 아니면 정상탐색
		}

		if (currBlock >= 'a' && currBlock <= 'z') { // 만약 해당 블록이 키라면
			if(keyHave[currBlock-'a'] == false){
				keyHave[currBlock - 'a'] = true;
				while (!lockedDoors[currBlock - 'a'].empty()) {
					forBFS.push(lockedDoors[currBlock - 'a'].front());
					lockedDoors[currBlock - 'a'].pop();
				}
			} // 가지고있지 않은 키를 가져왔을경우 그에 대응하는 문들 중 방문하지 못한 문들을 모두 큐에 push
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