#pragma once
#include "Common.h"
#include "FileName.h"

//#define BUFSIZE 512

#ifndef _DEBUG
#define new DEBUG_NEW
#endif

#define DEBUG_EVENT_MSG				WM_APP + 0x100 // thread msging 

using namespace glob;

// MAIN DEBUG CODE ///////////////////////////////////////////////////////////////////////////

void SetDbgMode(bool bDebug)
{
	if (!bDebug)
		printf("Debug was succesfully started");			//LOG 
	else
		printf("Debugging process stopped");				//LOG

	m_bIsDebugging = bDebug;
}

void DbgThreadProc()
{
	STARTUPINFO si;					// defines window, desktop and appearance
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));	// fills a block of memory with zeros
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess
	(
		NULL,						// No module name (use command line)
		NULL,						// if need cmd (argv[1])
		NULL,						// Process handle not inheritable
		NULL,						// Thread handle not inheritable
		false,						// Set handle inheritance to FALSE
		DEBUG_ONLY_THIS_PROCESS,	// CreationFlag
		NULL,						// Use parent's environment block
		NULL,						// Use parent's starting directory 
		&si,						// Pointer to STARTUPINFO structure
		&pi							// Pointer to PROCESS_INFORMATION structure
	);

	CString strEventMsg;
	std::map<LPVOID, CString> DllNameMap;

	DEBUG_EVENT debug_event = { 0 };

	bool bContinueDbg = true;

	DWORD dwContinueStatus = DBG_CONTINUE;
}

DWORD WINAPI DbgThread(/*void* param*/)
{
	DbgThreadProc();

	return 0;
}