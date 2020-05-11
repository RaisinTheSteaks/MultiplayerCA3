// Copied a solution for logging from stackoverflow.

#define LOGFILE	"shadow.log"     // all Log(); messages will be appended to this file

#include <string>

extern bool LogCreated;      // keeps track whether the log file is created or not

void Log(std::string message);    // logs a message to LOGFILE
void LogErr(std::string message); // logs a message; execution is interrupted