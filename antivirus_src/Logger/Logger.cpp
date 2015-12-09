// Logger.cpp: main project file

#include "stdafx.h"
#include <tchar.h>
#using <system.dll>
#using <mscorlib.dll>

using namespace System;
using namespace System::Diagnostics;

int main(array<System::String ^> ^args)
{
	String ^sSource;
	String ^sLog;
	String ^sEvent;

	sSource = gcnew String("PM_Defender");
	sLog = gcnew String("Application");
	sEvent = gcnew String(args[0]);
	if (!EventLog::SourceExists(sSource)) EventLog::CreateEventSource(sSource, sLog);

	EventLog::WriteEntry(sSource, sEvent);
	return 0;
}