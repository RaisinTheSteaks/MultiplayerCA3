#include <stdlib.h>
#include <stdio.h>
#include <RoboCatClientPCH.h>

bool LogCreated = false;

void Log(std::string message)
{
	FILE *file;
	int err;
	if (!LogCreated) {
		//file = fopen(LOGFILE, "w");
		err = fopen_s(&file, LOGFILE, "w");
		LogCreated = true;
	}
	else
	{
		//file = fopen(LOGFILE, "a");
		err = fopen_s(&file, LOGFILE, "a");
	}
		
	if (err != NULL) {
		if (LogCreated)
			LogCreated = false;
		return;
	}
	else
	{
		message += "\n";
		fputs(message.c_str(), file);
		fclose(file);
	}

	if (file)
		fclose(file);
}

void LogErr(std::string message)
{
	Log(message);
	Log("\n");
	// Bad thing
}