#define _CRT_SECURE_NO_WARNINGS
/*
	2623_���� ���α׷�
	�Ϻ� ���α׷����� ������ ��������, �� ������ ��Ű�� ������ ����ؾ��ϴ� ����
	-> �� ������ ���� ������ �ش��� == ���������� ����� �� ����.

	�Ұ����� ��쵵 ���� -> ����׷������� ����Ŭ�� ������ ��� ��� ��忡 ���� ���������� ���� ����.
	����, ��� ��忡 ���� ���������� ���� �������, ������ ���� �� ���� ����.
	���� queue ������ != ��� ������ ��� 0�� �����.
*/


#include<stdio.h>
#include<queue>
#include<list>
using namespace std;

list<int>graph[1005];
queue<int>forTPS, answer;
int entLine[1005];
int n, m;

void topologic_sort() {
	int cur = 0;
	for (int i = 1; i <= n; i++) {
		if (entLine[i] == 0) {
			forTPS.push(i);
		}
	}

	while (!forTPS.empty()) {
		cur = forTPS.front();
		for (list<int>::iterator iter = graph[cur].begin(); iter != graph[cur].end(); iter++) {

		}
	}
}