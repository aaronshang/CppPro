// hello.cpp : 定义控制台应用程序的入口点。
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
	* 再开一个控制台，接收不到“调用进程”的标准输入
	* USBPcapCMD程序有类似操作，接收不到“管道”方式的参数
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


