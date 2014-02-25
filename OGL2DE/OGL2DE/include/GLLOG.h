#define GL_LOG_FILE "gl.log"
#ifndef __GLLOG_H_
#define __GLLOG_H_

#include <time.h>
#include <fstream>

bool restart_gl_log() 
{
	FILE* file = fopen(GL_LOG_FILE, "w+");
	if(!file)
	{
		fprintf(stderr, "ERROR could not open %s log file for writing\n", GL_LOG_FILE);
		return false;
	}
	time_t now = time (NULL);
	char* date = ctime (&now);
	fprintf (file, "%s local time is %s\n", GL_LOG_FILE, date);
	fclose(file);
	return true;
}

bool gl_log (const char * message, const char* filename, int line)
{
	FILE* file = fopen(GL_LOG_FILE, "a+");
	if(!file)
	{
		fprintf(stderr, "ERROR: could not open %s for writing\n", GL_LOG_FILE);
		return false;
	}
	fprintf(file, "%s:%i\n%s \n\n", filename, line, message);
	fclose(file);
	return true;
}



#endif