//mylog.h
#ifndef MYLOG_H
#define MYLOG_H

#include <time.h>
#include <stdio.h>
#include <stdarg.h>

class Mylog_
{
public:
	Mylog_::Mylog_(const char * logname) {
		logname_ = logname;
		FILE *fp = NULL;
		fp = fopen(logname_, "a+");
		fclose(fp);
	}
	Mylog_::~Mylog_()
	{
		if (fp != NULL)
			fclose(fp);
	}

	void Mylog_::writeLogTime()
	{
		fp = fopen(logname_, "a+");
		time(&rawtime);
		p = localtime(&rawtime);
		fprintf(fp, "%d/%d/%d ", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);
		fprintf(fp, "%d:%d:%d   ", p->tm_hour, p->tm_min, p->tm_sec);
		fclose(fp);
	}

	void Mylog_::recordMessage(const char * format, ...)
	{
		char buffer[256];
		va_list args;
		va_start(args, format);
		vsprintf(buffer, format, args);
		fp = fopen(logname_, "a+");
		fprintf(fp, "%s\n", buffer);
		fclose(fp);
		va_end(args);
	}

public:
	const char * logname_;
	time_t rawtime;
	tm *p;
	FILE * fp;
};

#endif