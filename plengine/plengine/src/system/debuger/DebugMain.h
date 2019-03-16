#pragma once
#include <Windows.h>
#include <atlstr.h>

class Debugger
{
	int TotalEvents;
	int ThreadCount, DLLCount, ExceptionCount, OutputDebugCount;

	HANDLE m_hDbgThread;
	bool m_bIsDebugging;

public:

	void SetDbgMode(bool bDebug);
	void DbgThreadProc();

	CString ProcessNameToDebug;

	LRESULT DbgEventLog(WPARAM, LPARAM);
};

