// hello.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
#define BUFFERSIZE 10

int _tmain(int argc, _TCHAR* argv[])
{
	printf("I am hero. hello!\n");

	/*
	* �ٿ�һ������̨�����ղ��������ý��̡��ı�׼����
	* USBPcapCMD���������Ʋ��������ղ������ܵ�����ʽ�Ĳ���
	*/
	//FreeConsole();
	//freopen("CONOUT$", "w", stdout);
	//freopen("CONOUT$", "w", stderr);
	//if (AllocConsole() == FALSE)
	//{
	//	return -1;
	//}
	//freopen("CONIN$", "r", stdin);
	//freopen("CONOUT$", "w", stdout);
	//freopen("CONOUT$", "w", stderr);


	char buffer[BUFFERSIZE];
	printf("Enter a message: \n");
	while (fgets(buffer, BUFFERSIZE, stdin) != NULL)
	{
		printf("%s\n", buffer);
		if (buffer[0] == 'q')
		{
			break;
		}
	}

	//string i;
	//while (true)
	//{
	//	cin >> i;
	//	cout<< i << endl;
	//	fflush(stdout);
	//	if (i[0]=='q')
	//	{
	//		break;
	//	}
	//}
	return 0;
}


