#include <iostream>
#include "logging.h"
#include <stdlib.h>

FILE * Logger::logger = fopen("logger","w");

DataFlowException::DataFlowException(const char *type, const char *error)
{

	sprintf(msg, "Throwing Exception: (%s): %s",type,error);
	Logger::LogEvent(msg);
}

void Logger::LogEvent(const char *event)
{
//	if (Logger::getLogger() == NULL)
//		Logger::getLogger() = fopen("logger","w");
 	fprintf(logger,"%s\n",event);
}

void Logger::Finalize()
{
	fclose(Logger::getLogger());
}