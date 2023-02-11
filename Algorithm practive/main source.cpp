#include<iostream>
#include<stack>
using namespace std;

void input(stack<int> sta) {
	for (int i = 0; i < 10; i++) {
		sta.push(i);
	}
}

int main() {
	stack<int> st;
	input(st);

	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;


}