#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;


void main()
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite, hRead2, hWrite2;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
		MessageBox(NULL, "Error On CreatePipe()", "", MB_OK);
		return;
	}
	if (!CreatePipe(&hRead2, &hWrite2, &sa, 0)) {
		MessageBox(NULL, "Error On CreatePipe()", "", MB_OK);
		return;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.hStdInput = hRead2;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//USBPcapCMD hello CREATE_NEW_CONSOLE
	if (!CreateProcess(NULL, "hello.exe"
		, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
		MessageBox(NULL, "Error on CreateProcess()", "", MB_OK);
		return;
	}

	CloseHandle(hWrite);

	//char buffer[4096] = { 0 };
	DWORD bytesRead, bytesRead2;
	//char str1[1000] = "2\r\n";
	//WriteFile(hWrite2, str1, strlen(str1), &bytesRead2, NULL);

	Sleep(5000);
	char device[] = { 'q', '\r', '\n' };
	int size = sizeof(device);
	WriteFile(hWrite2, device, size, &bytesRead2, NULL);

	//while (true) {

	//	memset(buffer, 0, sizeof(buffer));
	//	if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
	//	{
	//		MessageBox(NULL, "Error on ReadFile()", "", MB_OK);
	//		break;
	//	}
	//	cout << "read size" << bytesRead << endl;

	//	if (strlen(buffer) > 0)
	//	{
	//		printf("HaHa:%s", buffer);
	//		Sleep(4000);

	//		char str1[1000] = "3\r\n";
	//		//WriteFile(hWrite2, str1, strlen(str1), &bytesRead2, NULL);

	//		char device[] = { '1', '7', '\r', '\n' };
	//		int size = sizeof(device);
	//		WriteFile(hWrite2, device, size, &bytesRead2, NULL);
	//	}
	//}

	while (true)
	{
		Sleep(1000);
	}
}

void invoke(string exe);

int main1(int argc, char* argv[])
{
	string exe = "hello.exe";
	//string exe = "USBPcapCMD.exe";
	invoke(exe);

	while (true)
	{
		Sleep(1000);
	}
	return 0;
}


void invoke(string exe)
{
	SECURITY_ATTRIBUTES saPipe;
	saPipe.nLength = sizeof(SECURITY_ATTRIBUTES);
	saPipe.lpSecurityDescriptor = NULL;
	saPipe.bInheritHandle = TRUE;

	HANDLE hReadPipe, hWritePipe;
	BOOL bSuccess = CreatePipe(&hReadPipe,
		&hWritePipe,
		&saPipe,
		0);
	if (!bSuccess)
		return;

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.hStdInput = hReadPipe;
	//si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//si.dwFlags = STARTF_USESTDHANDLES;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;


	if (CreateProcess(NULL, (char*)exe.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		Sleep(1000);
		//CloseHandle(pi.hThread);

		DWORD dw;
		
		char *str = "test";
		if (WriteFile(hWritePipe, str, strlen(str), &dw, NULL))
		{
			cout << "success" << endl;
		}
		
		fflush(stdin);
		char device[] = {'q', '\r', '\n'};
		int size = sizeof(device);
		if (WriteFile(hWritePipe, device, size, &dw, NULL))
		{
			cout << "success" << endl;
		}

		Sleep(1000);
		device[0] = 1;
		if (WriteFile(hWritePipe, device, size, &dw, NULL))
		{
			cout << "success" << endl;
			fflush(stdout);
		}


		//CloseHandle(pi.hProcess);
	}

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
}
