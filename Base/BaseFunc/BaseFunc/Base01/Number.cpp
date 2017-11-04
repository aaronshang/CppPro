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

double CNumber::round(double r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

void CNumber::test()
{
	float i = -87.2;
	int j = i;
	cout << "defalut" << j << endl;
	j = ceil(i);
	int k = floor(i);
	cout <<"ceil"<< j << endl;
	cout << "floor" << k << endl;
	cout << "round" << round(i) << endl;
}



