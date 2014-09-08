// EnumSessionActive.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <Wtsapi32.h>
#include <stdio.h>

char* GetSessionStatusStr(WTS_CONNECTSTATE_CLASS sessionInfo);

int main(int argc, char* argv[])
{
	PWTS_SESSION_INFO pSessionInfo = 0;
	DWORD dwCount = 0;

	// Get the list of all terminal sessions 
	WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, 
		&pSessionInfo, &dwCount);

	DWORD dwSessionId = 0;

	// look over obtained list in search of the active session
	for (DWORD i = 0; i < dwCount; ++i)
	{
		WTS_SESSION_INFO si = pSessionInfo[i];
		
		printf("Session %d      StationName (%s)    Status (%s)\n", si.SessionId
				, si.pWinStationName, GetSessionStatusStr(si.State));

	} 	

	WTSFreeMemory(pSessionInfo);

	return 0;
}

char* GetSessionStatusStr(WTS_CONNECTSTATE_CLASS sessionInfo)
{
	switch(sessionInfo)
	{
	case WTSActive:
		return "Active";
	case WTSConnected:
		return "Connected";
	case WTSConnectQuery:
		return "ConnectQuery";
	case WTSShadow:
		return "Shadow";
	case WTSDisconnected:
		return "Disconnected";
	case WTSIdle:
		return "Idle";
	case WTSListen:
		return "Listen";
	case WTSReset:
		return "Reset";
	case WTSDown:
		return "Down";
	case WTSInit:
		return "Init";
	}

	return "Unknown";
}

