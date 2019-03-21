#pragma once

#if PLATFORM_WINAPI

#ifndef WIN32_MANAGER
	#define WIN32_MANAGER
#endif 

//#define NOMINMAX


// It does not include <Winsock.h> from Windows.h
// Manually define your <Winsock2.h> inclusion point elsewhere instead.
#ifndef _WINSOCKAPI_
	#define _WINSOCKAPI_
#endif

#if defined(_WINDOWS_) && !defined(INCLUDE_MFC_ATL) // connects winapi library via MFC
	#error "<windows.h> has been included via MFC (not PlWindows.h) "  
// PlWindows.h - main header winapi
#endif

#include <Windows.h>

/*
#if !defined(FUNCTION_RENAMER) // required to support cross-platform
	#undef func
	#undef
	#undef

	#if !defined(RESOURCE_COMPILER)
		#undef MessageBox // It is necessary to turn off the message output function of WinApi and use your
	#endif

#endif
*/

#if defined(_RELEASE) && !PLATFORM_DESKTOP /*or other*/
	#undef OutputDebugString
	#define OutputDebugString(...) (void) 0 
#endif

/*
If the program does not have a debugger, 
then the VS will automatically output lines in unicode, 
since we have our debug, we turn off the function
*/


#endif