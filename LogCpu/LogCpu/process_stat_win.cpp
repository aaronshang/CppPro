//代码源自：http://www.rosoo.net/a/201112/15557.html 在此基础上进行修改
//process_stat_win.cpp
#include <windows.h>
#include <psapi.h>
#include <assert.h>
#include "process_stat.h"
#include "process.h"
#include "Tlhelp32.h"
#include <string>
using namespace std;
//#define _WIN32_WINNT 0x0501
#pragma comment(lib, "Psapi.lib")

static uint64_t file_time_2_utc(const FILETIME* ftime)
{
	LARGE_INTEGER li;
	assert(ftime);
	li.LowPart = ftime->dwLowDateTime;
	li.HighPart = ftime->dwHighDateTime;
	return li.QuadPart;
}


static int get_processor_number()
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return (int)info.dwNumberOfProcessors;
}

int get_cpu_usage(int pid)
{
	static int processor_count_ = -1;
	static int64_t last_time_ = 0;
	static int64_t last_system_time_ = 0;

	FILETIME now;
	FILETIME creation_time;
	FILETIME exit_time;
	FILETIME kernel_time;
	FILETIME user_time;
	int64_t system_time;
	int64_t time;
	int64_t system_time_delta;
	int64_t time_delta;

	int cpu = -1;
	if (processor_count_ == -1)
	{
		processor_count_ = get_processor_number();
	}
	GetSystemTimeAsFileTime(&now);

	HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);


	//原来版本中，hProcess 为 GetCurrentProcess（）
	if (!GetProcessTimes(hProcess, &creation_time, &exit_time,
		&kernel_time, &user_time))
	{
		return -1;
	}

	system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) / processor_count_;
	time = file_time_2_utc(&now);
	if ((last_system_time_ == 0) || last_time_ == 0)
	{
		last_system_time_ = system_time;
		last_time_ = time;
		return -1;
	}

	system_time_delta = system_time - last_system_time_;
	time_delta = time - last_time_;

	assert(time_delta != 0);
	if (time_delta == 0)
		return -1;

	cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);
	last_system_time_ = system_time;
	last_time_ = time;
	return cpu;
}

int get_memory_usage(int pid, uint64_t* mem, uint64_t* vmem)
{
	PROCESS_MEMORY_COUNTERS pmc;
	HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		if (mem) *mem = pmc.WorkingSetSize;
		if (vmem) *vmem = pmc.PagefileUsage;
		return 0;
	}
	return -1;
}

int get_io_bytes(int pid, uint64_t* read_bytes, uint64_t* write_byte)
{
	IO_COUNTERS io_counter;
	HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

	if (GetProcessIoCounters(hProcess, &io_counter))
	{
		if (read_bytes) *read_bytes = io_counter.ReadTransferCount;
		if (write_byte) *write_byte = io_counter.WriteTransferCount;
		return 0;
	}
	return -1;
}

/*void ReStartProcess(CString proname)
{
bool isKill = KillProcessFromName(proname);
if(isKill)
printf("kill %s success\n", proname.GetBuffer(0));
else
printf("kill %s failed\n", proname.GetBuffer(0));
CString strpath1;
strpath1 = proname;
Sleep(1000);
CreateNewProcess(strpath1);
Sleep(5000);
int i = 1;
while (FindProcessFromName(proname) == FALSE && i < 3)
{
i++;
CreateNewProcess(strpath1);
Sleep(5000);
}
}

BOOL CreateNewProcess(LPCSTR pszExeName)
{
PROCESS_INFORMATION piProcInfoGPS;
STARTUPINFO siStartupInfo;
SECURITY_ATTRIBUTES saProcess, saThread;
ZeroMemory( &siStartupInfo, sizeof(siStartupInfo) );
siStartupInfo.cb = sizeof(siStartupInfo);
saProcess.nLength = sizeof(saProcess);
saProcess.lpSecurityDescriptor = NULL;
saProcess.bInheritHandle = true;
saThread.nLength = sizeof(saThread);
saThread.lpSecurityDescriptor = NULL;
saThread.bInheritHandle = true;
return ::CreateProcess( NULL, (LPTSTR)pszExeName, &saProcess, &saThread, false,CREATE_DEFAULT_ERROR_MODE,
NULL, NULL, &siStartupInfo, &piProcInfoGPS );
}

BOOL FindProcessFromName(LPCSTR lpProcessName)
{
HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
PROCESSENTRY32 pe;
pe.dwSize = sizeof(PROCESSENTRY32);
if(!Process32First(hSnapShot,&pe))
{
return FALSE;
}
CString strProcessName = lpProcessName;
strProcessName.MakeLower();
while (Process32Next(hSnapShot,&pe))
{
CString scTmp = pe.szExeFile;
scTmp.MakeLower();
if(!scTmp.Compare(strProcessName))
{
return TRUE;
}
scTmp.ReleaseBuffer();
}
strProcessName.ReleaseBuffer();
return FALSE;
}

BOOL KillProcessFromName(LPCSTR lpProcessName)
{
HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
PROCESSENTRY32 pe;
pe.dwSize = sizeof(PROCESSENTRY32);
if(!Process32First(hSnapShot,&pe))
{
return FALSE;
}
CString strProcessName = lpProcessName;
strProcessName.MakeLower();
while (Process32Next(hSnapShot,&pe))
{
CString scTmp = pe.szExeFile;
scTmp.MakeLower();
if(!scTmp.Compare(strProcessName))
{
DWORD dwProcessID = pe.th32ProcessID; //获得pid
HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID); //不管通过pid还是进程名字最终都是为了获得进程的句柄
::TerminateProcess(hProcess,0);

CloseHandle(hProcess);
return TRUE;
}
scTmp.ReleaseBuffer();
}
strProcessName.ReleaseBuffer();
return FALSE;
}*/

int  GetPidFromName(LPCSTR lpProcessName)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapShot, &pe))
	{
		return FALSE;
	}
	//  CString strProcessName = lpProcessName; 
	string strProcessName(lpProcessName);

	//  strProcessName.MakeLower(); 
	while (Process32Next(hSnapShot, &pe))
	{
		//这里需要
		//CString scTmp = pe.szExeFile; 
		char buffer[260];
		wcstombs(buffer, pe.szExeFile, sizeof(buffer));

		string scTmp(buffer);
		//scTmp.MakeLower(); 
		if (!scTmp.compare(strProcessName))
		{
			DWORD dwProcessID = pe.th32ProcessID; //获得pid
			return dwProcessID;
		}
	}
	return -1;
}