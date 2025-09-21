#define _CRT_SECURE_NO_WARNINGS

/*
	---- 7579_�� ----
	
	�⺻ ���̵�� : ��� �� Ȯ���� �� �ִ� ����Ʈ ���� �������� ������.
	����� 0�� ���, INF�� ���.(INF = 11111111) 

	��� �� ����Ʈ ���� ���� ���, ����� ���� ������� ����.
	�⺻���� ���ڴ� snapsack ������ ����.
	���� ���� ������� ���� ���� �뷮�� �����ϵ�, snapsack ������ �ٸ� ���� ����� ����
	�־��� �պ��� �� Ŀ�߸� �Ѵٴ� ��.
	DT�� ũ��� ���� ������ n * ���� �ִ�ũ�� * ���� ������ 100n
	���� �ִ� ũ��� 100 * 10000�� ��.
*/

#include<stdio.h>

typedef struct app {
	int cost;
	int volume;
};
app apps[102];
int DT[101][10005];
int min = 2000000000;

int n, m;

int main() {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) scanf("%d", &(apps + i)->volume);
	for (int i = 1; i <= n; i++) scanf("%d", &(apps + i)->cost);

	for (int i = 0; i <= 100; i++) {
		for (int q = 0; q <= 10001; q++) 
			DT[i][q] = -1;
	}
	DT[0][0] = 0;

	for (int i = 1; i <= n; i++) {
		app current = apps[i];
		int curr = i - 1;

		for (int q = 0; q <= 10000; q++) {
			if (DT[curr][q] != -1) {
				if (DT[i][q] == -1 || DT[i][q] < DT[curr][q]) DT[i][q] = DT[curr][q];
				if (DT[i][q + current.cost] == -1 || DT[i][q + current.cost] < DT[curr][q] + current.volume)
					DT[i][q + current.cost] = DT[curr][q] + current.volume;
			}

			if (DT[i][q] != -1 && DT[i][q] >= m && q < min) min = q;
		}

		
	}

	printf("%d", min);
}