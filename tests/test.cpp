#include <iostream>
#include <time.h>
#include "zbinbin/log/log.h"
#include "zbinbin/thread/Thread.h"

int main(int argc, char** argv) {
	using namespace zbinbin;
	using namespace std;

	LoggerPtr logger(new Logger());
	// logger->addAppender(LogAppenderPtr(new StdoutLogAppender));
	LogAppenderPtr fileAppender(new FileLogAppender("/tmp/sylar.log"));
	logger->addAppender(fileAppender);

	
	// LogEventPtr event(new LogEvent(__FILE__, __LINE__, 0, CurrentThread::tid(), 2, ::time(0)));
	// auto& log = event->getLogStream();
	// log << "Hello sylar!";
	// logger->log(LogLevel::Level::DEBUG, event);
	{
		
	}
	LOG_INFO(logger) <<  "Hello sylar!";

	return 0;
}
