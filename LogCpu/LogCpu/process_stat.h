//process_stat.h
#ifndef PROCESS_STAT_H
#define PROCESS_STAT_H

#include <windows.h>

typedef LONG64 int64_t;
typedef ULONG64 uint64_t;

int get_cpu_usage(int pid);
int get_memory_usage(int pid, uint64_t* mem, uint64_t* vmem);
int get_io_bytes(int pid, uint64_t* read_bytes, uint64_t* write_byte);
int  GetPidFromName(LPCSTR lpProcessName);

#endif