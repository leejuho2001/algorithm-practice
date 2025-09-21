#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
int sdoku[10][10];
bool row[10][10];
bool column[10][10];
bool square [3][3][10];
int n = 9;
int cnt = 0;
int maxX = 0, maxY = 0;
bool solve(int x, int y) {
    //printf("%d %d %d\n", x, y, sdoku[x][y]);
    cnt += 1;

    if (x > maxX) {
        maxX = x;
        maxY = 0;
    }

    if (y > maxY) {
        maxY = y;
    }
    if (cnt >= 10000000) {
        return true;
    }
    int sqx = x / 3, sqy = y / 3;

    if (x == 9) {
        for (int i = 0; i < 9; i++) {
            for (int q = 0; q < 9; q++) {
                printf("%d", sdoku[i][q]);
            }
            puts("");
        }

        return true;
    }

    
    if (sdoku[x][y] != 0) {
        if (y < 8) return solve(x, y + 1);
        else return solve(x + 1, 0);
    }

    else {
        for (int i = 1; i <= 9; i++) {
            bool case1 = row[x][i] == false;
            bool case2 = column[y][i] == false;
            bool case3 = square[sqx][sqy][i] == false;

            if (case1 && case2 && case3) {
                row[x][i] = column[y][i] = square[sqx][sqy][i] = true;
                sdoku[x][y] = i;
                bool result;
                if (y < 8) result = solve(x, y + 1);
                else result = solve(x + 1, 0);

                if (result == true) return true;
                sdoku[x][y] = 0;
                row[x][i] = column[y][i] = square[sqx][sqy][i] = false;
            }
        }
    }
    return false;
}
int main() {
    for (int i = 0; i < n; i++) {
        for (int q = 0; q < n; q++) {
            char temp;
            scanf(" %c", &temp);
            sdoku[i][q] = temp - '0';
            if (sdoku[i][q] != 0) {
                row[i][sdoku[i][q]] = true;
                column[q][sdoku[i][q]] = true;
                square[i/3][q/3][sdoku[i][q]] = true;
            }
        }
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int q = 0; q < n; q++) {
            printf("%d", sdoku[i][q]);
        }
        puts("");
    }
    */
    bool res = solve(0, 0);
    //if (res == false) printf("can't solve");
    //printf("%d %d", maxX, maxY);
    return 0;
} 
