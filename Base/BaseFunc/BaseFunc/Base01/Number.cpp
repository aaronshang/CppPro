#include "Number.h"
#include <math.h>
#include <iostream>
#include <string>
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

int CNumber::GetINT(long long guid, int port)
{
	char temp[32] = { 0 };
	sprintf(temp, "%lld", guid);
	string guidStr = temp;
	string halfStr = "";
	for (int i = 0; i < guidStr.length(); i++)
	{
		if (i % 2 == 1)
		{
			halfStr.append(guidStr.substr(i, 1));
		}
	}
	return 0;
}

