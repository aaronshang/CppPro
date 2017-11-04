#include <iostream>
#include "Base01/Number.h"

using namespace std;

int main(){

	cout << "hello" << endl;

	CNumber *number = new CNumber();
	number->test();
	delete number;

	return 0;

}