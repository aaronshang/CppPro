#include "Number.h"
#include <math.h>
#include <iostream>
using namespace std;

CNumber::CNumber()
{
}

CNumber::~CNumber()
{
}

void CNumber::test()
{
	float i = -87.5;
	int j = i;
	cout << "defalut" << j << endl;
	j = ceil(i);
	int k = floor(i);
	cout <<"ceil"<< j << endl;
	cout << "floor" << k << endl;
}