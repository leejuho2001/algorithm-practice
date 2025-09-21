#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

/*
	---- 1562_��� �� ----
	DP�� 3�������� ��.
	[����][��������][������]
	 = [����-1][����+-1][��] + ����-1[����][��+-1]

	 1�� 9�� ��� �� ���ΰ�?
	 ==> 0�� 10���� ���� �� �ִ�.
	 ���⼭, 0�� 10�� �ʱ�ȭ�� �����ʾ� ��� 0���� ���������ָ�, ����� ���� �ʴ°Ͱ� ���� ȿ���� �� �� �ִ�.
*/

#define piv 1000000000
int DT[101][11][11];
long long int DT2[41][11][11];

int main() {
	DT[10][9][0] = 1;
	DT[11][1][9] = 1;
	DT2[10][9][0] = 1;
	DT2[11][1][9] = 1;

	for (int i = 11; i <= 100; i++) {
		for (int q = 1; q <= 9; q++) {
			for (int z = 0; z <= 9; z++) {
				int forward = (DT[i - 1][q - 1][z] + DT[i - 1][q + 1][z]) % piv;
				int backward;
				if (z == 0) backward = DT[i - 1][q][z + 1];
				else backward = (DT[i - 1][q][z - 1] + DT[i - 1][q][z + 1]) % piv;
				DT[i][q][z] = (forward + backward) % piv;
			}
		}
	}

	for (int i = 11; i <= 40; i++) {
		for (int q = 1; q <= 9; q++) {
			for (int z = 0; z <= 9; z++) {
				long long int forward = (DT2[i - 1][q - 1][z] + DT2[i - 1][q + 1][z]) ;
				long long int backward;
				if (z == 0) backward = DT2[i - 1][q][z + 1];
				else backward = (DT2[i - 1][q][z - 1] + DT2[i - 1][q][z + 1]) ;
				DT2[i][q][z] = (forward + backward) ;
			}
		}
	}
	int n;
	scanf("%d", &n);
	

	long long int sum = 0;
	/*
	for (int i = 1; i <= 9; i++) {
		for (int q = 0; q <= 9; q++) {
			sum += DT[n][i][q];
			sum %= 1000000000;
		}
	}*/
	
	for (int i = 1; i <= 40; i++) {
		long long int temp = 0;
		for (int q = 1; q <= 9; q++) {
			for (int z = 0; z <= 9; z++) {
				temp += (long long int)DT2[i][q][z];
				
			}
		}
		sum += temp % 1000000000;
	}

	printf("%lld", sum);
	

}

/* 10���� 30����
1
3
14
37
117
287
770
1800
4420
9994
23249
51307
115156
249487
546042
1166004
2505150
5287425
11200451
23414399
49050151
*/