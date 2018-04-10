#include "process_stat.h"
#include <windows.h>
#include <stdio.h>
#include "mylog.h"

const char processName[] = "ubserver2.exe";
const char logName[] = "log_cpu.txt";

int main(int argc, char **argv)
{
	int pid = -1;

	char *myProcessName = NULL;
	if (argc == 2)
	{
		myProcessName = argv[1];
	}
	else{

		myProcessName = "ubserver2.exe";
	}
	 
	pid = GetPidFromName(myProcessName);
	if (pid == -1)
	{
		printf("cann't find the process. please confirm the processName\n");
		return 0;
	}
	printf("processName = %s pid = %d\n", myProcessName, pid);
	printf("���ڼ�¼��%s", logName);
	while (1)
	{
		int cpu;
		uint64_t mem, vmem, r, w;
		cpu = get_cpu_usage(pid);
		get_memory_usage(pid, &mem, &vmem);
		get_io_bytes(pid, &r, &w); //�ڱ�������û�ã��ڱ�ĵط����á���

		Mylog_ log(logName);
		log.writeLogTime();
		log.recordMessage("cpu: %d%%    �ڴ棺%u MB", cpu, mem / (1024*1024));

		Sleep(1000*30); //��¼���
	}
	return 0;
}