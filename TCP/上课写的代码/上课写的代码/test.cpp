#include<iostream>
#include<string>

using namespace std;

int main(){
	string str = "abc";
	for (size_t i = str.size() - 1; i > 0; i--){
		cout << i << endl;
	}
	system("pause");
	return 0;
}