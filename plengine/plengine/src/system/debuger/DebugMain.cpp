#pragma once
//#include <DbgHelp.h>
#include <map>

#include "../log_system/Log.h"
#include "FileName.h"
#include "DebugMain.h"

//#define BUFSIZE 512
#ifndef _DEBUG
#define new DEBUG_NEW
#endif

#define DEBUG_EVENT_MSG				WM_APP + WM_KEYDOWN // thread msging (WM_KEYDOWN = 0x0100)

// MAIN DEBUG CODE ///////////////////////////////////////////////////////////////////////////

void Debugger::SetDbgMode(bool bDebug)
{
	if (!bDebug)
		//printf("Debug was succesfully started");
		DbgLog(Info, "Debug was succesfully started", 0, 1);
	else
		//printf("Debugging process stopped");
		DbgLog(Info, "Debug was succesfully started", 0, 1);

	m_bIsDebugging = bDebug;
}

void Debugger::DbgThreadProc()
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

	CString strEventMsg; // A CString object supports either the wchar_t type or the wchar_t type
	std::map<LPVOID, CString> DllNameMap;

	DEBUG_EVENT debug_event = { 0 }; // Event ID, process ID, thread ID (FUNCTION OF OBTAINING PROCESS DATA - in process) 

	bool bContinueDbg = true;

	DWORD dwContinueStatus = DBG_CONTINUE;

	while (bContinueDbg)
	{
		if (!WaitForDebugEvent(&debug_event, INFINITE))
			return;
	/*
	As soon as the WaitForDebugEvent is completed and control returns,
	we will receive a debugger message,
	and after that we will call ContinueDebugEvent to continue execution of the code.
	*/

		switch (debug_event.dwDebugEventCode)
		{
		case CREATE_PROCESS_DEBUG_EVENT:
			{
				strEventMsg = GetFileNameFromHandle(debug_event.u.CreateProcessInfo.hFile);
			}
			break;
		case CREATE_THREAD_DEBUG_EVENT:
			{
				strEventMsg.Format
				(
					"Thread 0x%x (ID: %d) created at: 0x%x", 
					debug_event.u.CreateThread.hThread, 
					debug_event.dwThreadId, 
					debug_event.u.CreateThread.lpStartAddress // LPTHREAD_START_ROUTINE pointer (indicates where the image was loaded in memory)
				);				
			}
			break;
		case EXIT_THREAD_DEBUG_EVENT:
			{
				strEventMsg.Format
				(
					"The thread %d exited with code: %d", 
					debug_event.dwThreadId, 
					debug_event.u.ExitThread.dwExitCode
				);				
			}
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			{
				strEventMsg.Format("0x%x", debug_event.u.ExitProcess.dwExitCode);				
			}
			break;
		case LOAD_DLL_DEBUG_EVENT:
			{
				strEventMsg = GetFileNameFromHandle(debug_event.u.LoadDll.hFile);

				DllNameMap.insert(std::make_pair(debug_event.u.LoadDll.lpBaseOfDll, strEventMsg));
			
				strEventMsg.AppendFormat("%x", debug_event.u.LoadDll.lpBaseOfDll);				
			}
			break;
		case UNLOAD_DLL_DEBUG_EVENT:
			{
				strEventMsg.Format("%s", DllNameMap[debug_event.u.UnloadDll.lpBaseOfDll]);				
			}
			break;
		case OUTPUT_DEBUG_STRING_EVENT:
			{
				OUTPUT_DEBUG_STRING_INFO & DebugString = debug_event.u.DebugString;	// (OUTPUT_DEBUG_STRING_INFO & DebugString) = LPSTR (not exactly)
				
				WCHAR *msg = new WCHAR[DebugString.nDebugStringLength];// Don't care if string is ANSI, and we allocate double
				ZeroMemory(msg, DebugString.nDebugStringLength);

				ReadProcessMemory(pi.hProcess, DebugString.lpDebugStringData, msg, DebugString.nDebugStringLength, NULL);

				if (DebugString.fUnicode) //support Unicode
				{
					strEventMsg = msg;
				}
				else
				{
					strEventMsg = (LPSTR)msg; //LPSTR to CString (Unicode) conversion
				}

				delete[]msg; // If pointer refers to an array, place empty brackets before pointer
			}
			break;
		case EXCEPTION_DEBUG_EVENT: // Exception Handling
			{
				EXCEPTION_DEBUG_INFO& exception = debug_event.u.Exception;

				switch (exception.ExceptionRecord.ExceptionCode)
				{
				case STATUS_BREAKPOINT:
					{
						strEventMsg = "Break Point!";
					}
					break;
					
				default:
					if (exception.dwFirstChance == true)
					{
						strEventMsg.Format
						(
							"First chance exception at %x, exception code: 0x%08x",
							exception.ExceptionRecord.ExceptionAddress,
							exception.ExceptionRecord.ExceptionCode
						);
					}
					//else OS handle

					// There are cases where OS ignores the dwContinueStatus, 
					// and executes the process in its own way.
					// For first chance exceptions, this parameter is not-important
					// but still we are saying that we have NOT handled this event.

					// Changing this to DBG_CONTINUE (for 1st chance exception also), 
					// may cause same debugging event to occur continously.

					dwContinueStatus = DBG_EXCEPTION_NOT_HANDLED;
				}
				break;
			}
		}
	}

	//SendMessage(DEBUG_EVENT_MSG, (WPARAM)&strEventMsg, debug_event.dwDebugEventCode); 

	ContinueDebugEvent(debug_event.dwProcessId, debug_event.dwThreadId, dwContinueStatus);

	/*
	Calling ContinueDebugEvent, we ask the OS to continue executing the debugging program.
	dwProcessId and dwThreadId point us to a process and thread.
	We got these values from WaitForDebugEvent.
	The last parameter indicates whether to continue or not.
	This parameter will have value only when an exception has come to debugging.
	*/

	//Reset
	dwContinueStatus = DBG_CONTINUE;
}

// Run LOG thread
LRESULT Debugger::DbgEventLog(WPARAM wParam, LPARAM lParam) // LPARAM - Window id(HANDLE), WPARAM - Activation flag 
{
	CString* pMsg = (CString*)wParam;

	switch (lParam)
	{
	case CREATE_PROCESS_DEBUG_EVENT:
		{
			DbgLog(Info, "Process started", 0, *pMsg); // remove fucking zero
			TotalEvents++;
			break;
		}
	case CREATE_THREAD_DEBUG_EVENT:
		{
			DbgLog(Info, "Thread created", 0, *pMsg);// remove fucking zero
			ThreadCount++;
			TotalEvents++;
			break;
		}
	case EXIT_THREAD_DEBUG_EVENT:
		{
			DbgLog(Info, "Thread exited", 0, *pMsg);// remove fucking zero
			ThreadCount--;
			TotalEvents++;
			break;
		}
	case EXIT_PROCESS_DEBUG_EVENT:
		{
			DbgLog(Info, "Process exited with code", 0, *pMsg);// remove fucking zero
			TotalEvents++;
			break;
		}
	case LOAD_DLL_DEBUG_EVENT:
		{
			DbgLog(Info, "DLL loaded", 0, *pMsg);// remove fucking zero
			DLLCount++;
			TotalEvents++;
			break;
		}
	case UNLOAD_DLL_DEBUG_EVENT:
		{
			DbgLog(Info, "DLL unloaded", 0, *pMsg);// remove fucking zero
			DLLCount--;
			TotalEvents++;
			break;
		}
	case OUTPUT_DEBUG_STRING_EVENT:
		{
			DbgLog(Info, "Debug message", 0, *pMsg);// remove fucking zero
			OutputDebugCount++;
			TotalEvents++;
			break;
		}
	case EXCEPTION_DEBUG_EVENT:
		{
			DbgLog(Info, "Debug exception", 0, *pMsg);// remove fucking zero
			ExceptionCount++;
			TotalEvents++;
			break;
		}	
	}

	//CString counts;

	DbgLog(Service, "Total debugging events", 0, TotalEvents);// remove fucking zero

	DbgLog(Service, "Threads", 0, ThreadCount);// remove fucking zero

	DbgLog(Service, "DLLs", 0, DLLCount);// remove fucking zero

	DbgLog(Service, "Exceptions", 0, ExceptionCount);// remove fucking zero

	DbgLog(Service, "Output debugs", 0, OutputDebugCount);// remove fucking zero

	if (lParam == EXIT_PROCESS_DEBUG_EVENT)
	{
		SetDbgMode(false);
	}

	return 0;
}

DWORD WINAPI DbgThread(void* param)
{
	Debugger *pThis = static_cast<Debugger*>(param);

	pThis->DbgThreadProc();

	return 0;
}


