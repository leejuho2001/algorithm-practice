#define _CRT_SECURE_NO_WARNINGS

// 18110_solved.ac
/*
#include<stdio.h>
#include<algorithm>
using namespace std;

int main() {
	int n;
	int opinions[30050] = {};

	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", opinions + i);
	sort(opinions, opinions + n);

	float less = (float)n * 0.15 + 0.5;
	int Intless = (int)less;
	int resultN = n - Intless * 2;
	int sum = 0;

	for (int i = less; i < n - less; i++) {
		sum += opinions[i];
	}

	float average = (float)sum / resultN + 0.5;
	int result = (int)average;
	printf("%d", result);
}*/

//25083_새싹
/*
#include<stdio.h>


int main() {
	printf("		 ,r\'\"7"); puts("");
	printf("r`-_   ,\'  ,/"); puts("");
	printf(" \\. \".L_r\'"); puts("");
	printf("   `~\\/"); puts("");
	printf("	  |"); puts("");
	printf("	  |");
}

*/

//2775_부녀회장이 될테야
/*
#include<stdio.h>


int DT[20][20];
int hotel(int a, int b) {
	if (DT[a][b]) return DT[a][b];
	else {
		if (a == 0) return b;

		int res = 0;
		for (int i = 1; i <= b; i++) {
			res += hotel(a - 1, i);
		}
		return DT[a][b] = res;
	}
}

int main() {
	int n; scanf("%d", &n);
	for (int _ = 0; _ < n; _++) {
		int a, b; scanf("%d %d", &a, &b);
		printf("%d\n", hotel(a, b));
	}
}
*/

//7568_덩치
/*
#include<stdio.h>

typedef struct _person {
	int weight;
	int length;
	int rank;
}person;

int main() {
	person people[55] = {};
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		people[i].weight = a;
		people[i].length = b;
	}

	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int q = 0; q < n; q++) {
			if (people[i].weight < people[q].weight && people[i].length < people[q].length)cnt++;
		}

		people[i].rank = cnt + 1;
	}

	for (int i = 0; i < n; i++) {
		printf("%d ", people[i].rank);
	}
}
*/

/*
#include<stdio.h>
#include<algorithm>
using namespace std;

int MAX = 0;
int MAXADDRESS = 0;

bool isSecond = false;

int nums[8050] = {};
int number[500050] = {};

int main() {
	int sum = 0;
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", number + i);
		nums[number[i]+4000] ++;
		sum += number[i];
	}

	sort(number, number + n);

	for (int i = 0; i < 8002; i++) {
		if (nums[i] > MAX) {
			MAX = nums[i];
			MAXADDRESS = i;
			isSecond = false;
			continue;
		}

		if (isSecond == false && nums[i] == MAX) {
			MAXADDRESS = i;
			isSecond = true;
		}
	}
	float avr = (float)sum / n + 0.5;

	printf("%d", (int)avr);
	printf("%d", number[n / 2]);
	printf("%d", MAXADDRESS - 4000);
	printf("%d", nums[n - 1] - nums[0]);
}*/

// 1051_숫자 정사각형
/*
#include<stdio.h>
int n, m;
int matrix[55][55];

int max = 0;
int main() {
	scanf("%d %d", &n, &m);
	int smaller = n < m ? n : m;

	for (int i = 0; i < n; i++) {
		for (int q = 0; q < m; q++) {
			char temp;
			scanf(" %c", &temp);
			matrix[i][q] = temp - '0';
		}
	}
	int size = 0;

	while (size <= smaller - 1) {
		for (int i = 0; i < n - size; i++) {
			for (int q = 0; q < m - size; q++) {
				bool condition1 = matrix[i][q] == matrix[i + size][q];
				bool condition2 = matrix[i][q] == matrix[i][q + size];
				bool condition3 = matrix[i + size][q] == matrix[i + size][q + size];


				//printf("%d %d %d :: %d, %d, %d, %d\n", i, q, size, matrix[i][q], matrix[i + size][q], matrix[i][q + size], matrix[i + size][q + size]);

				if (condition1 && condition2 && condition3) {
					if (max < (size + 1) * (size + 1)) max = (size + 1) * (size + 1);
				}
			}
		}
		size++;
	}

	printf("%d", max);
}
*/

/*
#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;

struct cmp {
	bool operator()(int a, int b) {
		if (abs(a) == abs(b)) return a > b;
		else return abs(a) > abs(b);
	}
};

priority_queue<int, vector<int>, cmp> prq;

int main() {
	int n; scanf("%d", &n);

	for (int _ = 0; _ < n; _++) {
		int temp;
		scanf("%d", &temp);

		if (temp == 0) {
			if (!prq.empty()) {
				printf("%d\n", prq.top());
				prq.pop();
			}
			else {
				printf("0\n");
			}
		}
		else {
			prq.push(temp);
		}
	}
}
*/
/*
#include<stdio.h>
#include<math.h>

int min[50005];

int main() {
	int n; scanf("%d", &n);

	int m; scanf("%d", &m);
	printf("%d", (int)sqrt(m));
}
*/


/*
#include<stdio.h>

int main() {
	int n; scanf("%d", &n);
	int temp = n;
	temp = (temp % 10) * 10 + (temp % 10 + temp / 10) % 10;
	int cnt = 1;
	int a, b;
	while ( temp!= n) {
		a = temp % 10; b = temp / 10;
		temp = a * 10 + (a + b) % 10;
		cnt++;
	}

	printf("%d", cnt);
}
*/
/*
#include<stdio.h>
#include<string.h>

typedef struct _loong {
	long long int under;
	long long int over;
	char sign;
}dlong;

dlong dlongInput() {
	char temp[24] = {};
	int start1 = 11, end1 = 0, end2 = 12;
	scanf("%s", temp);
	for (int i = strlen(temp); i < 24; i++) {
		temp[i] = '0';
	}
	dlong result = {};
	if (temp[0] == '-') result.sign = '-', start1++, end1++, end2++;

	for (int i = start1; i >= end1; i--) {
		result. over *= 10;
		result. over += (temp[i] - '0');
	}
	for (int i = 23; i > end2; i--) {
		result. under *= 10;
		result. under += (temp[i] - '0');
	}

	return result;
}

void dlongOutput(dlong dl) {
	if (dl.sign == '-') printf("-");
	if (dl.over > 0) { 
		printf("%lld", dl.over); 
		printf("%012lld", dl.under);
	}
	else {
		printf("%lld", dl.under);
	}
}

int main() {
	dlong dd = dlongInput();
	dlongOutput(dd);
}*/

/*
#include<stdio.h>
int main() {
	int nums[42] = {};
	int sums[42] = {};
	int n, s; scanf("%d %d", &n, &s);
	for (int i = 1; i <= n; i++) {
		scanf("%d", nums + i);
		sums[i] = sums[i - 1] + nums[i];
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int q = i + 1; q <= n; q++) {
			if (sums[q] - sums[i] == s) cnt++;
		}
	}
	for (int i = 0; i <= n; i++) {
		printf("%d ", sums[i]);
	}
	puts("");
	printf("%d", cnt);
}
*/

/*
#include<stdio.h>

long long int w, h, f, c, x1, y1, x2, y2;
long long int s;

int main() {
	scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &w, &h, &f, &c, &x1, &y1, &x2, &y2);

	long long int piv = 2 * f;
	long long int ovlap = 0, novlap = 0;
	f = f > w / 2 ? w-f : f;
	s = w * h;
	if (f + x2 <= piv) {
		ovlap = (y2 - y1) * (x2 - x1);
	}
	else {
		novlap = ( (f+x2) - piv) * (y2 - y1);
		ovlap = (piv - (f+x1)) * (y2 - y1);
	}

	s -= novlap * (c + 1) + ovlap * 2 * (c + 1);

	printf("%lld", s);

}
*/
/*
#include<stdio.h>
int used[10] = {};
long long int cnt = 0;

void strn(int cur, int level, int length) {
	//printf("%d %d %d\n", cur, level, length);

	used[cur]++;
	if (level == length) {
		for (int i = 0; i < 10; i++) {
			if (used[i] == 0) { 
				used[cur]--;
				return; }
		}
		cnt++;
		used[cur]--;
		return;
	}

	if (cur > 0) strn(cur - 1, level + 1, length);
	if (cur < 9) strn(cur + 1, level + 1, length);
	used[cur]--;
}

int get_stairnums(int length) {
	cnt = 0;

	for (int i = 1; i <= 9; i++) {
		for (int i = 0; i < 10; i++) used[i] = 0;
		strn(i, 1, length);
	}

	return cnt%1000000000;
}

int main() {
	int n;
	for (int i = 10; i < 31; i++) {
		printf("%d\n", get_stairnums(i));
	}
}*/



/*
int max = -1;

void findd(long long int a, long long int b, int level) {
	if (a > b) return;
	if (a == b) {
		if (max == -1 || level < max) max = level;
	}

	findd(a * 10 + 1, b, level + 1);
	findd(a * 2, b, level + 1);
}

int main() {
	long long int a, b;
	scanf("%lld %lld", &a, &b);
	findd(a, b, 1);

	printf("%d", max);
}*/

/*
#include<stdio.h>
#include<queue>
#include<stack>
using namespace std;

queue<int> forBFS;
stack<char>commands;

bool visited[10005];
char command[10005];
int before[10005];

int cal1(int a) {
	return (a * 2) % 10000;
}

int cal2(int a) {
	return (a + 9999) % 10000;
}

int cal3(int a) {
	return (a % 1000) * 10 + a / 1000;
}

int cal4(int a) {
	return (a / 10) + (a % 10) * 1000;
}

void init() {
	for (int i = 0; i < 10002; i++) {
		visited[i] = 0;
		before[i] = 0;
		command[i] = 0;
	}
}

void visit(int curr, int value, char mode) {
	visited[value] = true;
	before[value] = curr;
	command[value] = mode;
	forBFS.push(value);
}

void BFS(int start) {
	visited[start] = true;
	before[start] = -1;
	forBFS.push(start);

	while (!forBFS.empty()) {
		int curr = forBFS.front();
		
		int val1 = cal1(curr);
		int val2 = cal2(curr);
		int val3 = cal3(curr);
		int val4 = cal4(curr);

		if (visited[val1] == false) {
			visit(curr, val1, 'D');
		}
		if (visited[val2] == false) {
			visit(curr, val2, 'S');
		}
		if (visited[val3] == false) {
			visit(curr, val3, 'L');
		}
		if (visited[val4] == false) {
			visit(curr, val4, 'R');
		}

		forBFS.pop();
	}
}


int main() {
	int n; scanf("%d", &n);
	int s, e;
	for (int _ = 0; _ < n; _++) {
		init();
		scanf("%d %d", &s, &e);
		BFS(s);
		int temp = e;
		while (temp != s) {
			commands.push(command[temp]);
			temp = before[temp];
		}

		while (!commands.empty()) {
			printf("%c", commands.top());
			commands.pop();
		}
		puts("");
	}
}
*/

/*
#include<stdio.h>
#include<list>
using namespace std;

void find_dividers


int main() {
	int n; scanf("%d", &n);
	bool flag = false;
	bool isNotPrime = false;
	int temp = n;
	int i = 0;
	int mod = 0;

	for (int i = 2; i <= n && temp>1; i++) {
		if (temp % i == 0) {
			if (isNotPrime == false) isNotPrime = true;
			while (temp % i == 0) {
				if (flag == true) printf(" * ");
				printf("%d", i);

				flag = true;
				temp /= i;
			}
		}
	}
}
*/

/*
#include<stdio.h>

int max = -1, min = 500;
int map[505][505];

int main() {
	int minTime = -1;
	int minheight = -1;
	int n, b, m;
	scanf("%d %d %d", &n, &m, &b);

	for (int i = 0; i < n; i++) {
		for (int q = 0; q < m; q++) {
			scanf("%d", &map[i][q]);

			if (map[i][q] > max) max = map[i][q];
			if (map[i][q] < min) min = map[i][q];
		}
	}

	int tempb = b;
	int minus = 0, plus = 0;

	for (int a = max; a >= min; a--) {
		minus = 0, plus = 0;
		
		for (int i = 0; i < n; i++) {
			for (int q = 0; q < m; q++) {
				if (map[i][q] > a) minus += (map[i][q] - a);
				else plus += a - map[i][q];
			}
		}

		if (plus > b + minus) continue;
		else {
			int res = plus + minus * 2;
			if (res < minTime || minTime == -1) { 
				minTime = res; 
				minheight = a;
			}
		}
	}

	printf("%d %d", minTime, minheight);
}*/ // 마인 크래프트

/*
#include<stdio.h>

int main() {
	int cnt = 0, n;
	int res = 0;

	scanf("%d", &n);
	for (int i = 1; cnt < n; i++) {
		int temp = i;
		while (temp > 0) {
			if (temp % 1000 == 666) {
				cnt++;
				break;
			}

			temp /= 10;
		}
		if (cnt == n) res = i;
	}
	printf("%d", res);
}
*/ //영화감독 숌

/*
#include<stdio.h>
long long int lans[10005];
long long int k, n;

int main() {
	scanf("%lld %lld", &k, &n);
	long long int sum = 0;

	for (int i = 0; i < k; i++) {
		scanf("%lld", lans + i);
		sum += lans[i];
	}

	for (long long int i = sum / n; i > 0; i--) {
		int tempp = 0;
		for (int q = 0; q < k; q++) {
			tempp += lans[q] / i;
		}

		if (tempp >= n) {
			printf("%lld", i);
			return 0;
		}
	}
}*/

/*
#include<stdio.h>
#include<string.h>
#include<stack>
using namespace std;

stack<int>beforeSum1;
stack<int>beforeSum2;

stack<int>result;

int main() {
	char temp1[10050] = {};
	char temp2[10050] = {};
	scanf(" %s", temp1);
	scanf(" %s", temp2);

	for (int i = 0; i < strlen(temp1); i++) {
		beforeSum1.push(temp1[i] - '0');
	}

	for (int i = 0; i < strlen(temp2); i++) {
		beforeSum2.push(temp2[i] - '0');
	}
	int carry=0;
	int num1 = 0;
	int num2 = 0;
	while (!beforeSum1.empty() || !beforeSum2.empty()) {
		num1 = 0, num2 = 0;
		if (!beforeSum1.empty()) {
			num1 = beforeSum1.top();
			beforeSum1.pop();
		}

		if (!beforeSum2.empty()) {
			num2 = beforeSum2.top();
			beforeSum2.pop();
		}

		int tempres = num1 + num2 + carry;
		if (tempres >= 10) carry = 1;
		else carry = 0;

		result.push(tempres % 10);
	}

	if (carry == 1) result.push(1);

	while (!result.empty()) {
		printf("%d", result.top());
		result.pop();
	}
}*/

/*
#include<stdio.h>
int n; char map[105][105];
int visited[105][105];
int cnt1, cnt2;


void DFS1(int x, int y, char color) {
	visited[x][y] = 1;
	if (x < n && map[x + 1][y] == color && visited[x + 1][y] != 1) DFS1(x + 1, y, color);
	if (x > 1 && map[x - 1][y] == color && visited[x - 1][y] != 1) DFS1(x - 1, y, color);
	if (y < n && map[x][y + 1] == color && visited[x][y + 1] != 1) DFS1(x, y + 1, color);
	if (y > 1 && map[x][y - 1] == color && visited[x][y - 1] != 1) DFS1(x, y - 1, color);

}


void DFS2(int x, int y, char color) {
	visited[x][y] = 2;

	if (color == 'G' || color == 'R') {
		if (x < n && (map[x + 1][y] == 'G' || map[x + 1][y] == 'R') && visited[x + 1][y] != 2)DFS2(x + 1, y, color);
		if (x > 1 && (map[x - 1][y] == 'G' || map[x - 1][y] == 'R') && visited[x - 1][y] != 2)DFS2(x - 1, y, color);
		if (y < n && (map[x][y + 1] == 'G' || map[x][y + 1] == 'R') && visited[x][y + 1] != 2)DFS2(x, y + 1, color);
		if (y > 1 && (map[x][y - 1] == 'G' || map[x][y - 1] == 'R') && visited[x][y - 1] != 2)DFS2(x, y - 1, color);
	}

	else {
		if (x < n && map[x + 1][y] == color && visited[x + 1][y] != 2) DFS2(x + 1, y, color);
		if (x > 1 && map[x - 1][y] == color && visited[x - 1][y] != 2) DFS2(x - 1, y, color);
		if (y < n && map[x][y + 1] == color && visited[x][y + 1] != 2) DFS2(x, y + 1, color);
		if (y > 1 && map[x][y - 1] == color && visited[x][y - 1] != 2) DFS2(x, y - 1, color);
	}
}


void normal() {
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			if (visited[i][q] != 1) {
				cnt1++;
				DFS1(i, q, map[i][q]);
			}
		}
	}
}


void GR() {
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			if (visited[i][q] != 2) {
				cnt2++;
				DFS2(i, q, map[i][q]);
			}
		}
	}
}


int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			scanf(" %c", &map[i][q]);
		}
	}

	normal();
	GR();

	printf("%d %d", cnt1, cnt2);
} */ // 10026_적록색약
/*
#include<stdio.h>
#include<string.h>
#include<stack>
using namespace std;

stack<char>balance;

int main() {
	int cnt;
	char temp[150] = {};
	bool flag = false;
	bool first = true;
	while (1) {
		while (!balance.empty())balance.pop();
		fgets(temp, sizeof(temp), stdin);
		//printf("%s  ::  %d\n", temp, strlen(temp));
		if (temp[0] == '.') return 0;

		bool flag = true;
		for (int i = 0; i < strlen(temp) && temp[i] != '.'; i++) {
			if (temp[i] == '(')  balance.push('(');
			if (temp[i] == ')') {
				if (!balance.empty() && balance.top() == '(')  balance.pop();
				else {
					//puts("minus1-1");
					flag = false;
					break; 
				}
			}
			if (temp[i] == '{') balance.push('{');
			if (temp[i] == '}') {
				if (!balance.empty() && balance.top() == '{') balance.pop();
				else {
					//puts("minus2-1");
					flag = false;
					break;
				}
			}
			if (temp[i] == '[')  balance.push('[');
			if (temp[i] == ']') {
				if (!balance.empty() && balance.top() == '[')  balance.pop();
				else {
					//puts("minus3-1");
					flag = false;
					break;
				}
			}
		}

		if (balance.empty() && flag == true) printf("yes\n");
		else printf("no\n");

	}
}*/ //4949
/*
#include<stdio.h>
#include<algorithm>

using namespace std;
int numCnts[8005];
int nums[500050];

int n;

int main() {
	scanf("%d", &n);
	int sum = 0;
	int MANY = -1;
	int how = -1;
	bool isSecond = false;

	for (int i = 0; i < n; i++) {
		scanf("%d", nums+i);
		sum += nums[i];

		numCnts[nums[i] + 4000]++;
	}
	sort(nums, nums + n);

	for (int i = 0; i <= 8000; i++) {
		if (numCnts[i] > how) {
			//printf("case1 :: %d\n", i - 4000);
			how = numCnts[i];
			MANY = i;
			isSecond = false;
			continue;
		}

		if (numCnts[i] == how && isSecond == false) {
			//printf("case2 :: %d\n", i - 4000);
			isSecond = true;
			MANY = i;
		}
	}

	int aver;
	if (sum < 0) {
		aver = -(-1 * sum + (n / 2)) / n;
	}
	else aver = (sum + (n / 2)) / n;

	printf("%d\n", aver);
	printf("%d\n", nums[n / 2]);
	printf("%d\n", MANY-4000);
	printf("%d", nums[n - 1] - nums[0]);

}*/ //2108_통계학

/*
#include<stdio.h>

int k, n;
long long int lengths[10050];
long long int min = -1;


long long int count(long long int q) {
	long long int cnt = 0;
	for (int i = 0; i < k; i++) {
		cnt += lengths[i] / q;
	}
	return cnt;
}
long long int bi_search(long long int s, long long int e) {
	long long int center = (s + e) / 2;

	long long int cnt = count(center);
	if (s > e || e==0) return -1;
	if (s == e) return s;

	if (e == s + 1) {
		//printf("%d", count(e));
		if (count(e) >= (long long int)n) return e;
		else return s;
	}
	
	
	if (cnt < n) return bi_search(s, center - 1);
	if (cnt >= n) return bi_search(center, e);
}






int main() {
	scanf("%d %d", &k, &n);

	for (int i = 0; i < k; i++) {
		scanf("%lld", lengths + i);
		if (min == -1 || min < lengths[i])min = lengths[i];
	}

	long long int longer = bi_search(1, min);
	printf("%lld", longer);
}*/ //1654_랜선 자르기

/*

#include<stdio.h>
#include<algorithm>
using namespace std;
int n;
int cnt, resCnt;
int map[505][505];
int res[30000];

void DFS(int i, int q) {
	cnt++;
	map[i][q] = 2;
	int adder[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	for (int z = 0; z < 4; z++) {
		if (map[i + adder[z][0]][q + adder[z][1]] == 1)
			DFS(i + adder[z][0], q + adder[z][1]);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			char temp;
			scanf(" %c", &temp);
			map[i][q] = temp - '0';
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			if (map[i][q] == 1) {
				cnt = 0;
				DFS(i, q);

				res[resCnt++] = cnt;
			}
		}
	}

	sort(res, res + resCnt);

	printf("%d\n", resCnt);
	for (int i = 0; i < resCnt; i++) printf("%d\n", res[i]);
}

*/

/*
#include<stdio.h>

int targ;

long long int padovan(long long int f, long long int s, long long int t, int num) {
	if (targ <= 3) return 1;

	else if (targ == num) return t;

	return padovan(s, t, f + s, num+1);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int _ = 0; _ < n; _++) {
		scanf("%d", &targ);
		printf("%lld\n", padovan(1, 1, 1, 3));
	}
}*/

/*
#include<stdio.h>

int map[105][105];
int res[105][105];

int visited[105];
int n;
void DFS(int start, int current, bool st) {
	if(st != true) visited[current] = start;

	for (int i = 1; i <= n; i++) {
		if (map[current][i] == 1 && visited[i] != start)
			DFS(start, i, false);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) scanf("%d", &map[i][q]); 
	}



	for (int i = 1; i <= n; i++) {
		DFS(i, i, true);

		for (int q = 1; q <= n; q++) {
			if (visited[q] == i) res[i][q] = 1;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) printf("%d ", res[i][q]);
		puts("");
	}
}
*/
/*
#include<stdio.h>

bool map[105][105];
int visited[105][105];
int n, m;

void DFS(int x, int y) {

	if (x > 1 && map[x - 1][y] && (visited[x - 1][y] == 0 || visited[x - 1][y] > visited[x][y] + 1)) {
		visited[x - 1][y] = visited[x][y] + 1;
		DFS(x - 1, y);
	}
	if(x<n && map[x + 1][y] && (visited[x + 1][y] == 0 || visited[x+1][y] > visited[x][y] + 1)) {
		visited[x + 1][y] = visited[x][y] + 1;
		DFS(x + 1, y);
	}
	if(y>1 && map[x][y - 1] && (visited[x][y - 1] == 0 || visited[x][y-1] > visited[x][y] + 1)) {
		visited[x][y - 1] = visited[x][y] + 1;
		DFS(x, y - 1);
	}
	if(y<m && map[x][y + 1] && (visited[x][y + 1] == 0 || visited[x][y+1] > visited[x][y] + 1)) {
		visited[x][y + 1] = visited[x][y] + 1;
		DFS(x, y + 1);
	}
}

int main() {
	char temp = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= m; q++) {
			scanf(" %c", &temp);
			if (temp == '1') map[i][q] = true;
		}
	}
	visited[1][1] = 1;
	DFS(1, 1);

	printf("%d", visited[n][m]);
} */ // 경로찾기

/*
#include<stdio.h>

int map[605][605];
int n, m;
int cnt;
bool visited(int x, int y) {
	return map[x][y] < 3;
}

void DFS(int x, int y) {
	if (map[x][y] == 1) cnt++;
	map[x][y] = 4;

	if (x > 1 && visited(x - 1, y)) DFS(x - 1, y);
	if (x < n && visited(x + 1, y))DFS(x + 1, y);
	if (y > 1 && visited(x, y - 1))DFS(x, y - 1);
	if (y < m && visited(x, y + 1))DFS(x, y + 1);
}

int main() {
	scanf("%d %d", &n, &m);
	int sx = 0, sy = 0;
	char temp = 0;
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= m; q++) {
			scanf(" %c", &temp);
			if (temp == 'O')map[i][q] = 0;
			if (temp == 'I') { map[i][q] = 0; sx = i, sy = q; }
			if(temp == 'P') map[i][q] = 1;
			if (temp == 'X') map[i][q] = 3;
		}
	}
	DFS(sx, sy);
	if (cnt == 0) printf("TT");
	else printf("%d", cnt);
} */// 21736_헌내기는 친구가 필요해

/*
#include<stdio.h>

int DT[50050];
int n;
int main() {
	scanf("%d", &n);
	int targ = 0;
	for (int i = 0; i < n; i++) {
		for (int q = 1; i+q*q <= n; q++) {
			targ = i + q * q;
			if (DT[targ] == 0 || DT[targ] > DT[i] + 1)
				DT[targ] = DT[i] + 1;
		}
	}

	printf("%d", DT[n]);
} */ //17626_Four Squares
/*
#include<stdio.h>

int main() {
	int target = 0, n = 0;
	bool imp[10] = {};
	scanf("%d", &target);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int temp = 0;
		scanf("%d", &temp);
		imp[temp] = true;
	}
	int baseResult = target - 100;
	if (baseResult < 0) baseResult *= -1;


	for (int i = 0; i <= 1000500; i++) {
		int length = 0;
		int tempresult = 0;
		int tempp = i;
		bool flag = false;

		while (1) {
			int ones = tempp % 10;
			if (imp[ones] == true) {
				flag = true;
				break;
			}
			length++;
			tempp /= 10;
			if (tempp == 0)break;
		}

		if (flag == true) continue;
		tempresult = target - i;
		if (tempresult < 0) tempresult *= -1;
		tempresult += length;
		


		if (tempresult < baseResult) 
			
			baseResult = tempresult; 

	}

	printf("%d", baseResult);
}*/

/*#include<stdio.h>

int MAX = -1;
int map[505][505];
int n, m;

void checker(int x, int y) {
	int temp = 0;
	if (x < n && y < m) {
		temp = map[x][y] + map[x + 1][y + 1] + map[x + 1][y] + map[x][y + 1];
		if (temp > MAX) MAX = temp;
	}

	if (x < n && y < m - 1) {
		temp = map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x + 1][y];
		if (temp > MAX) MAX = temp;

		temp = map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x + 1][y + 1];
		if (temp > MAX) MAX = temp;

		temp = map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x + 1][y + 2];
		if (temp > MAX) MAX = temp;

		temp = map[x + 1][y] + map[x + 1][y + 1] + map[x + 1][y + 2] + map[x][y];
		if (temp > MAX) MAX = temp;

		temp = map[x + 1][y] + map[x + 1][y + 1] + map[x + 1][y + 2] + map[x][y + 1];
		if (temp > MAX) MAX = temp;

		temp = map[x + 1][y] + map[x + 1][y + 1] + map[x + 1][y + 2] + map[x][y + 2];
		if (temp > MAX) MAX = temp;

		temp = map[x][y] + map[x][y + 1] + map[x + 1][y + 1] + map[x + 1][y + 2];
		if (temp > MAX) MAX = temp;

		temp = map[x+1][y] + map[x + 1][y + 1] + map[x][y + 1] + map[x][y + 2];
		if (temp > MAX) MAX = temp;
	}

	if (x < n - 1 && y < m) {
		temp = map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x][y + 1];
		if (temp > MAX) MAX = temp;

		temp = map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x + 1][y + 1];
		if (temp > MAX) MAX = temp;

		temp = map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x + 2][y + 1];
		if (temp > MAX) MAX = temp;

		temp = map[x][y + 1] + map[x + 1][y + 1] + map[x + 2][y + 1] + map[x][y];
		if (temp > MAX) MAX = temp;

		temp = map[x][y + 1] + map[x + 1][y + 1] + map[x + 2][y + 1] + map[x + 1][y];
		if (temp > MAX) MAX = temp;

		temp = map[x][y + 1] + map[x + 1][y + 1] + map[x + 2][y + 1] + map[x + 2][y];
		if (temp > MAX) MAX = temp;

		temp = map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y + 1];
		if (temp > MAX) MAX = temp;

		temp = map[x][y + 1] + map[x + 1][y + 1] + map[x + 1][y] + map[x + 2][y];
		if (temp > MAX) MAX = temp;
	}

	if (x < n - 2) {
		temp = map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x + 3][y];
		if (temp > MAX) MAX = temp;
	}

	if (y < m - 2) {
		temp = map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x][y + 3];
		if (temp > MAX) MAX = temp;
	}
}


int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= m; q++) {
			scanf("%d", &map[i][q]);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= m; q++) {
			checker(i, q);
		}
	}

	printf("%d", MAX);
}*/

//14500_테트로미노

/*
#include<stdio.h>

char sent[1000050];
int DT[1000050];
int n, m, cnt;

int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", sent);

	for (int i = 0; i < m; i++) {
		if (DT[i] == 0) {
			if (sent[i] == 'I') DT[i + 1] = 1;
		}

		else {
			if (sent[i] != sent[i - 1]) DT[i + 1] = DT[i] + 1;
			else {
				if (sent[i] == 'I')DT[i + 1] = 1;
				else DT[i + 1] = 0;
			}
		}
	}

	for (int i = 0; i <= m; i++) {
		if (DT[i] % 2 == 1 && DT[i] >= 2 * n + 1) cnt++;
	}
	printf("%d", cnt);
}
*/

//5525_IOIOI
/*
#include<stdio.h>

int DT[105], stair[105];
int n, m;
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n + m; i++) {
		int a, b; scanf("%d %d", &a, &b);
		stair[a] = b;
	}
	int temp = 0;
	for (int _ = 0; _ < 50; _++) {
		for (int i = 1; i <= 100; i++) {
			if (stair[i] > 0) continue;
			for (int q = 1; q <= 6; q++) {
				temp = i + q;
				if (DT[temp] == 0 || DT[temp] > DT[i] + 1) {
					DT[temp] = DT[i] + 1;
					while (stair[temp] > 0) {
						//printf("%d -> %d :: %d -> %d\n", temp, stair[temp], DT[temp], DT[stair[temp]]);
						temp = stair[temp];
						if (DT[temp] == 0 || DT[temp] > DT[i] + 1) DT[temp] = DT[i] + 1;
					}
				}
			}
		}
	}

	printf("%d", DT[100]);
}*/

// 16928_뱀과 사다리 게임

/*
#include<stdio.h>
#include<queue>
using namespace std;

int visited[200000];
int visCnt;
queue<int>forBFS;
int s, e;
void BFS() {
	forBFS.push(s);
	while (!forBFS.empty()) {
		int curr = forBFS.front();
		if (visited[e] != 0 && visited[curr] > visited[e]) return;

		if (curr < e) {
			if (curr * 2 == e && visited[curr * 2] == visited[curr] + 1) visCnt++;
			if (curr + 1 == e && visited[curr + 1] == visited[curr] + 1) visCnt++;

			if (curr * 2 != s && visited[curr * 2] == 0) {
				visited[curr * 2] = visited[curr] + 1; 
				forBFS.push(curr * 2);
			}

			if (curr + 1 != s && visited[curr + 1] == 0) {
				visited[curr + 1] = visited[curr] + 1;
				forBFS.push(curr + 1);
			}
		}

		if (curr > e) {
			if (curr - 1 != s && curr - 1 == e && visited[curr - 1] == visited[curr] + 1) visCnt++;
			if (visited[curr - 1] == 0) {
				visited[curr - 1] = visited[curr] + 1;
				forBFS.push(curr - 1);
			}
		}

		forBFS.pop();
	}

}

int main() {
	scanf("%d %d", &s, &e);
	BFS();
	printf("%d\n%d", visited[e], visCnt);
}*/


// 12851_숨바꼭질2
/*
#include<stdio.h>
#include<queue>
using namespace std;

queue<int>forBFS;
int visited[105][105];
bool map[105][105];
int n, m, minman;

void BFS(int startNode) {
	forBFS.push(startNode);

	while (!forBFS.empty()) {
		int curr = forBFS.front();

		for (int i = 1; i <= n; i++) {
			if (i != startNode && visited[startNode][i] == 0 && map[curr][i] == true) {
				visited[startNode][i] = visited[startNode][curr] + 1;
				forBFS.push(i);
			}
		}

		forBFS.pop();
	}


}

int main() {
	scanf("%d %d", &n, &m);
	for (int _ = 0; _ < m; _++) {
		int a, b; scanf("%d %d", &a, &b);
		map[a][b] = true;
		map[b][a] = true;
	}
	for (int i = 1; i <= n; i++) {
		BFS(i);
	}

	int sum = 0;
	int min = 1000505;
	for (int i = 1; i <= n; i++) {
		sum = 0;
		for (int q = 1; q <= n; q++) {
			sum += visited[i][q];
		}

		if (sum < min) {
			minman = i;
			min = sum;
		}
	}

	printf("%d", minman);
}*/

// 1389_케빈 베이컨의 6단계 법칙

/*
#include<stdio.h>

int main() {
	int t, n;
	scanf("%d", &t);
	int MBTILIST[16];

	for (int _ = 0; _ < t; _++) {
		for (int i = 0; i < 16; i++) MBTILIST[i] = 0;
		char MBTI[5] = {};
		scanf("%d", &n);
		for (int ttt = 0; ttt < n; ttt++) {
			scanf("%s", MBTI);
			int cases = 0;
			for (int q = 0; q < 4; q++) {
				if (MBTI[q] == 'I') cases += 0;
				if (MBTI[q] == 'E') cases += 1;
				if (MBTI[q] == 'N') cases += 0;
				if (MBTI[q] == 'S') cases += 2;
				if (MBTI[q] == 'T') cases += 0;
				if (MBTI[q] == 'F') cases += 4;
				if (MBTI[q] == 'P') cases += 0;
				if (MBTI[q] == 'J') cases += 8;

			}
			MBTILIST[cases] ++;
		}

	}
}
*/
//20529_가장 가까운 세 사람의 심리적 거리
/*
#include<stdio.h>
int main() {
	int n, a, b, c, d;
	scanf("%d", &n);
	bool flag;
	for (int _ = 0; _ < n; _++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		flag = false;
		for (int i = 0; i <= b; i++) {
			int val = i * a + c;

			if (val % b == d % b) {
				printf("%d\n", i * a + c);
				flag = true;
				break;
			}
		}
		if (flag == false) printf("-1\n");
	}
}*/ // 6064_카잉 달력


/*
#include<stdio.h>
#include<math.h>
#define epsilon 10e-5
int main() {
	int x1, y1, x2, y2, r1, r2;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);

		int sqdist1 = r1 * r1;
		int sqdist2 = r2 * r2;
		int sqdist3 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

		if (x1 == x2 && y1 == y2) {
			if (r1 == r2) puts("-1");
			else puts("0");

			continue;
		}

		if (sqdist1 > sqdist2) {
			int index = sqdist1;
			sqdist1 = sqdist2;
			sqdist2 = index;
		}

		if (sqdist1 > sqdist3) {
			int index = sqdist1;
			sqdist1 = sqdist3;
			sqdist3 = index;
		}

		if (sqdist2 > sqdist3) {
			int index = sqdist2;
			sqdist2 = sqdist3;
			sqdist3 = index;
		}
		//printf("%d %d %d\n", sqdist1, sqdist2, sqdist3);

		float dist1 = sqrt((float)sqdist1);
		float dist2 = sqrt((float)sqdist2);
		float dist3 = sqrt((float)sqdist3);

		//printf("%3f %3f %3f\n", dist1, dist2, dist3);

		if (dist1 + dist2 > dist3) puts("2");
		else if (fabsf(dist1 + dist2 - dist3) < epsilon) puts("1");
		else puts("0");
		
	}
}
*/ // 1002_터렛

#include<stdio.h>
#include<queue>
using namespace std;
int main() {
	int size;
	int q, qn; // 질문 갯수
	int indexl[55] = {};
	scanf("%d %d", &size, &qn);
	for (int i = 0; i < qn; i++) {
		scanf("%d", indexl + i);
	}
	int qsize = size;
	int res = 0;
	int diff, curr = 1;
	for (int offset = 0; offset < qn; offset++) {
		diff = abs(curr - indexl[offset]);
		curr = indexl[offset];
		if (diff * 2 > size) diff = size - diff;

		for (int i = offset + 1; i < qn; i++) {
			if (indexl[i] > indexl[offset]) indexl[i] --;
		}

		res += diff;
		size--;
	}

	printf("%d", res);
}