#define _CRT_SECURE_NO_WARNINGS
/*
    ---- 11053_���� �� �����ϴ� �κ� ���� ----

    :: ������ �ִ� ������ 1000���̹Ƿ�,
    ���� �ܼ��� ������ DP�� ����Ѵ�.

    �ٸ� �ڷ����� ������� �ʰ�, �迭������ ���� �ذ�.
*/

#include<stdio.h>

int numbers[1050];
int DT[1050];
int Max = 0;

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", numbers + i);

    for (int i = 0; i < n; i++) {
        DT[i] = 1;
        for (int q = i - 1; q >= 0; q--) {
            if (numbers[i] > numbers[q] && DT[i] <= DT[q]) DT[i] = DT[q] + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (DT[i] > Max) Max = DT[i];
    }

    printf("%d", Max);
}