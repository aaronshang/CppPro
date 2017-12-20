#include <iostream>
#include "Base01/Number.h"
#include <vector>
#include "cjson/cjsonTest.h"
#include <string>
using namespace std;

int main(){

	cout << "hello" << endl;

	//testJson();

	//long long guid = 223499391602595000;
	//int port = 3;

	//CNumber *numObj = new CNumber();
	//int num = numObj->GetINT(guid, port);
	//cout << num << endl;
	//delete numObj;

	//int bigNum = (int(pow((double)2, (double)16)));
	//cout << bigNum << endl;

	string json1 = GetJsonTransGPS("ok");
	string json2 = GetJsonTransGPS(json1);
	cout << json2 << endl;
	return 0;

}