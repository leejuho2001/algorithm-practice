#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2448_별찍기 11 ----

                       *                3, 12
                      * *
                     *****
                    *     *
                   * *   * *
                  ***** *****          2, -6  , 2, +6 
                 *           *
                * *         * *
               *****       *****        
              *     *     *     *
             * *   * *   * *   * *
            ***** ***** ***** *****
           *   
    :: 12의 경우.

    base : n번째 줄의 앞의 띄어쓰기의 갯수
    = 24-n개.

    입력되는 수는 3 * 2^n의 형태를 가진다.
    --> 2^n과 모종의 관계를 가진다.

    재귀적 형태를 가지고 있다.
    = 재귀로, 이차원 배열에 놓는 형태로 구현한다.
    별찍기 = 다른걸 입력할 필요가 없음 = true/false로 구분 가능.

    어떻게 재귀적인가?
    하나의 삼각형 = 길이가 반인 삼각형 -> 왼쪽반, 꼭대기, 오른쪽 반.
    
    삼각형은 가장 윗 꼭짓점의 위치와, 길이로 표현한다.
    그렇게 될 경우, 왼쪽반과 오른쪽 반의 윗 꼭짓점 위치는
    왼쪽반 : 원래 - 길이 반(x), +0.5길이(y), 오른쪽 반 : 원래 +0.5길이(x), +0.5길이(y)로 표현된다.
*/

#include<stdio.h>
bool graph[3500][7000] = {};


void triangle(int x, int y, int size, int length) {
    //printf("%d %d\n", x, y);
    if (size == 1) {
        graph[x][y] = true;
        graph[x + 1][y - 1] = true;
        graph[x + 1][y + 1] = true;
        for (int i = -2; i <= 2; i++) {
            graph[x + 2][y+i] = true;
        }
        return;
    }
    triangle(x, y, size - 1, length / 2);
    triangle(x + length / 2, y - length / 2, size - 1, length / 2);
    triangle(x + length / 2, y + length / 2, size - 1, length / 2);
}

int main() {
    int n;
    scanf("%d", &n);
    int temp = n;
    int cnt = 0;
    temp /= 3;
    while (temp > 0) {
        cnt++;
        temp /= 2;
    }

    triangle(1, n, cnt, n);

    for (int i = 1; i <= n; i++) {
        for (int q = 1; q <= n *2; q++) {
            if (graph[i][q] == true) printf("*");
            else printf(" ");
        }
        puts("");
    }
}