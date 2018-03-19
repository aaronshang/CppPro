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

	string json1 = GetJsonTransGPS("ok", false);
	string json2 = GetJsonTransGPS(json1, true);
	cout << json2 << endl;

	parseJson(json2);


	//long long curtime = 123456789123;
	//int i = int(curtime / 1000000);
	//int j = (unsigned short)((curtime / 1000) % 1000);

	return 0;

}