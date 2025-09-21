#define _CRT_SECURE_NO_WARNINGS
/*
    ---- 11053_가장 긴 증가하는 부분 수열 ----

    :: 숫자의 최대 갯수가 1000개이므로,
    가장 단순한 형태의 DP를 사용한다.

    다른 자료형을 사용하지 않고, 배열만으로 문제 해결.
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