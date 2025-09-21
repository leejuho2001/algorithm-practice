#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2042_구간 합 구하기 ----

	기본적인 매커니즘 -> 하나의 수가 바뀌게 될 경우, 그 뒤의 구간합이 바뀌게 된다.
	따라서 해당 수에 대해서 증가 / 감소 여부를 기록해 두면 그걸 통해 구간합의 값을 추론할 수 있다.

	문제점 : 이 방식은 최악의 경우 구간합을 구하는 횟수 x 수의 개수만큼 연산이 일어나게 된다.
	하지만, 수의 개수가 1000000개로 너무 크기 때문에 이를 다 따진다면 시간초과가 발생하게 된다.(최악의 경우 약 100억개의 핵심연산)

	해결방식 : 리스트를 사용한다.
	배열과 비교했을 때, 리스트의 단점은 앞에서부터 순차적으로 탐색할 수 밖에 없다는 점이지만, 위 풀이에선 앞에서부터 풀이하는것이 강제되므로
	index를 많이 차지하지 않는다는 리스트의 장점이 더욱 크다.

	-> 시간초과.

	::-> 세그먼트 트리를 사용할것.
*/
/*
#include<iostream>
#include<list>
using namespace std;

class loong {
private:
	int digit;
	char sign;
	string digits;
	

public:
	
	void		set(const string& str);
	string		get_number(const loong& ref); 

	loong&		operator=(const loong &ref);

	loong		operator+(const loong& ref);
	


	string		get_number(const loong& ref) { return digits; }
	void		set(const string& str) {
		char temp[35];
		if(str.c_str()[0] == '-') temp[0] = 
		
		for (int i = str.length() - 1; i >= endPoint; i--) {
			
		}
	}

};

istream& operator>>(const istream& in, loong L) {
	string temp;
	cin >> temp;

	L.set(temp);

	return in;
}

ostream& operator<<(ostream& out, const loong& ref) {
	out<<ref.

}



list<long long int> changes;
*/