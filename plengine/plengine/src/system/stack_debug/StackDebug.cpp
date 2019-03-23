//#include"stdAfx.h" //compile optimization
#include "StackDebug.h"

const char* const StackDebug::szFatalErrorCode = "FATAL_ERROR";

StackDebug::StackDebug() : m_bIsFatalError(false), m_postBackupProcess(0)
{

}

void StackDebug::FileCreationCallback(void(*postBackupProcess)())
{
	m_postBackupProcess = postBackupProcess;
}


const char* StackDebug::TranslateExceptionCode(DWORD dwExcept)
{
	switch (dwExcept)
	{
	case EXCEPTION_ACCESS_VIOLATION:

		break;
	case EXCEPTION_DATATYPE_MISALIGNMENT:

		break;
	case EXCEPTION_BREAKPOINT:

		break;
	case EXCEPTION_SINGLE_STEP:

		break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:

		break;
	case EXCEPTION_FLT_DENORMAL_OPERAND:

		break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:

		break;
	case EXCEPTION_FLT_INEXACT_RESULT:

		break;
	case EXCEPTION_FLT_INVALID_OPERATION:

		break;
	case EXCEPTION_FLT_OVERFLOW:

		break;
	case EXCEPTION_INT_DIVIDE_BY_ZERO:

		break;
	case EXCEPTION_INT_OVERFLOW:

		break;
	case EXCEPTION_PRIV_INSTRUCTION:

		break;
	case EXCEPTION_IN_PAGE_ERROR:

		break;
	case EXCEPTION_ILLEGAL_INSTRUCTION:
		
		break;
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		
		break;
	case EXCEPTION_STACK_OVERFLOW:
		
		break;
	case EXCEPTION_INVALID_DISPOSITION:
		
		break;
	case EXCEPTION_GUARD_PAGE:
		
		break;
	case EXCEPTION_INVALID_HANDLE:
		
		break;



	case STATUS_FLOAT_MULTIPLE_FAULTS: // Multiple floating-point faults

		break;
	case STATUS_FLOAT_MULTIPLE_TRAPS: // Multiple floating-point traps

		break;

	default:
		return "Unknown";
		break;
	}
	
}