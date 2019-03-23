#ifndef __STACK_DEBUG_H__
#define __STACK_DEBUG_H__


//#include "PlWindows.h"
#include <Windows.h>
#include <string>
#include <atlstr.h>
#include <vector>
//#include "system/platform/PlatformChecker.h"

// Limits the maximal number of functions in call stack (optimization)
enum {MAX_DEBUG_STACK_ENTRIES = 80};

struct StackDebug
{
	StackDebug(){}

	/*******************VARIABLES********************************/
	bool m_bIsFatalError;
	std::vector<std::string> m_functions;

	void(*m_postBackupProcess) ();

	static const char* const szFatalErrorCode;
	/************************************************************/

	/*******************STRUCT FUNCTIONS*************************/
	static const char* TranslateExceptionCode(DWORD dwExcept);

	static void PutVersion(char* ver);
	
	static void Screenshot(const char* szFileName); 

	static void WriteLineToLog(const char* format, ...);
	/************************************************************/

	// Returns single instance of DebugStack (necessary if another platform)
	//static StackDebug* instance();

	virtual int		handleException(EXCEPTION_POINTERS* exception_pointer) { return 0; } //Exception pointer
	virtual void	CollectCurrentStackFrame(int maxStackEntries = MAX_DEBUG_STACK_ENTRIES);
	// Collects the low-level callstack frames

	/*
	A stack frame is a frame of data that gets pushed onto the stack. 
	In the case of a call stack, 
	a stack frame would represent a function call and its argument data.
	*/

	// Returns number of collected stack frames (pCallStack - function for collect, maxStackEntries - total number of functions in the stack)
	virtual int		CollectCallStackFrame(void** pCallStack, int maxStackEntries) { return 0; }

	// Collects low level callstack for given thread handle
	virtual int		CollectCallStack(HANDLE thread, void** pCallStack, int maxStackEntries) { return 0; }

	// Returns the module name of a given address
	virtual std::string	GetModuleNameForAddr(void* addr) { return "[Unknown]"; } //Unknown - default

	virtual bool	GetProcNameForAddr(void* addr, CString& procName, void*& baseAddr, std::string& filename, int& line) //void*& - will return a pointer to a pointer
	{
		filename = "[Unknown]"; //if default
		line = 0;
		baseAddr = addr;
#if PLATFORM_64BIT
		procName.Format("[%016llX]", (UINT64) addr); //[%016llX] - hexadecimal system
#else
		procName.Format("[%08X]", (UINT32) addr); // [%08X] - octal system
#endif
		return false;
	}

	virtual std::string	GetCurrentFilename() { return "[unknown]"; }

	virtual void	LogCallStack();
	virtual void	FatalError(const char*); //check the app and triggers fatal error
	virtual void	ReportBug(const char*); // notifies of an error, but does not close the program

	virtual void	FileCreationCallback(void(*postBackupProcess)()); // this function will return a function and a pointer to postBackupProcess

	//accepts functions in stack (current stack info)
	void			getCallStack(std::vector<std::string>& functions) { functions = m_functions; }

}StackDebug;

/*
DELETE "VIRTUAL" ON FUNC IF UNLESS OVERRIDE IS REQUIRED
*/

#endif // !__STACK_DEBUG_H__
