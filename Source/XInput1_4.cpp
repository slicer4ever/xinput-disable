#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <Xinput.h>
#include "XInput1_4.h"
#include <iostream>

#define XINPUT_GAMEPAD_GUIDE 0x400

HINSTANCE mHinst, mHinstDLL;
FARPROC mProcs[14];

LPCSTR mImportNames[] = {
	(LPCSTR )100, (LPCSTR )101, (LPCSTR )102, (LPCSTR )103, 
	(LPCSTR )104, (LPCSTR )108, "DllMain", "XInputEnable", 
	"XInputGetAudioDeviceIds", "XInputGetBatteryInformation", "XInputGetCapabilities", "XInputGetKeystroke", 
	"XInputGetState", "XInputSetState", 
};

static CHAR *                      //   return error message
getLastErrorText(                  // converts "Lasr Error" code into text
CHAR *pBuf,                        //   message buffer
ULONG bufSize)                     //   buffer size
{
	DWORD retSize;
	LPTSTR pTemp = NULL;

	if (bufSize < 16) {
		if (bufSize > 0) {
			pBuf[0] = '\0';
		}
		return(pBuf);
	}
	retSize = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ARGUMENT_ARRAY,
		NULL,
		GetLastError(),
		LANG_NEUTRAL,
		(LPTSTR)&pTemp,
		0,
		NULL);
	if (!retSize || pTemp == NULL) {
		pBuf[0] = '\0';
	}
	else {
		pTemp[strlen(pTemp) - 2] = '\0'; //remove cr and newline character
		sprintf(pBuf, "%0.*s (0x%x)", bufSize - 16, pTemp, GetLastError());
		LocalFree((HLOCAL)pTemp);
	}
	return(pBuf);
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
	mHinst = hinstDLL;
	if (fdwReason == DLL_PROCESS_ATTACH) {
		char sysdir[255], path[255];
		GetSystemDirectory( sysdir, 254 );
		sprintf( path, "%s\\XInput1_4.dll", sysdir );
		printf("XInput path: %s\n", path);
		mHinstDLL = LoadLibrary(path);
		MessageBox(nullptr, path, "HERE", MB_OK);
		if (!mHinstDLL) {
			MessageBox(nullptr, "Error loading library.", "", MB_OK);
			char buffer[500];
			printf("LoadLibrary failed\n");
			printf("error: %s\n", getLastErrorText(buffer, sizeof(buffer)));
			return (FALSE);
		}

		for ( int i = 0; i < 14; i++ )
			mProcs[ i ] = GetProcAddress( mHinstDLL, mImportNames[ i ] );
	} else if ( fdwReason == DLL_PROCESS_DETACH ) {
		FreeLibrary( mHinstDLL );
	}
	return ( TRUE );
}


// XInputGetStateEx
DWORD WINAPI ordinal100(DWORD index, XINPUT_STATE *state) {
	typedef DWORD(__stdcall *MXInputGetStateEX)(DWORD, XINPUT_STATE *);
	MXInputGetStateEX Func = (MXInputGetStateEX)mProcs[0];
	return Func(index, state);
}


//  ?? 
INT_PTR __stdcall ordinal101() {
	return 0;
}

//  ?? 
INT_PTR __stdcall ordinal102() {
	MessageBox(nullptr, "ordinal102 called!", "Unknown", MB_OK);
	return 0;
}

//  ?? 
INT_PTR __stdcall ordinal103() {
	MessageBox(nullptr, "ordinal103 called!", "Unknown", MB_OK);
	return 0;
}

//  ?? 
INT_PTR __stdcall ordinal104() {
	MessageBox(nullptr, "ordinal104 called!", "Unknown", MB_OK);
	return 0;
}

//  ?? 
INT_PTR __stdcall ordinal108() {
	MessageBox(nullptr, "ordinal108 called!", "Unknown", MB_OK);
	return 0;
}

// DllMain
BOOL WINAPI _DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved){
	typedef BOOL(__stdcall *MDLLMain)(HINSTANCE, DWORD, LPVOID);
	MDLLMain Func = (MDLLMain)mProcs[6];
	return Func(hinstDLL, fdwReason, lpvReserved);
}

// XInputEnable
void WINAPI _XInputEnable(BOOL enable) {
	typedef void(__stdcall *MXInputEnable)(BOOL);
	MXInputEnable Func = (MXInputEnable)mProcs[7];
	return Func(enable);
}

// XInputGetAudioDeviceIds
DWORD WINAPI _XInputGetAudioDeviceIds(DWORD dwUserIndex, LPWSTR pRenderDeviceID, UINT *pRenderCount, LPWSTR pCaputreDeviceID, UINT* pCaptureCount) {
	typedef DWORD(__stdcall *MXInputGetAudioDeviceIDS)(DWORD, LPWSTR, UINT*, LPWSTR, UINT*);
	MXInputGetAudioDeviceIDS Func = (MXInputGetAudioDeviceIDS)mProcs[8];
	return Func(dwUserIndex, pRenderDeviceID, pRenderCount, pCaputreDeviceID, pCaptureCount);
}

// XInputGetBatteryInformation
DWORD WINAPI _XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION *pBatteryInformation) {
	typedef DWORD(__stdcall *MXInputGetBatteryInformation)(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*);
	MXInputGetBatteryInformation Func = (MXInputGetBatteryInformation)mProcs[9];
	return Func(dwUserIndex, devType, pBatteryInformation);
}

// XInputGetCapabilities
DWORD WINAPI _XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES *pCapabilities) {
	typedef DWORD(__stdcall *MXInputGetCapabilities)(DWORD, DWORD, XINPUT_CAPABILITIES*);
	MXInputGetCapabilities Func = (MXInputGetCapabilities)mProcs[10];
	return Func(dwUserIndex, dwFlags, pCapabilities);
}

// XInputGetKeystroke
DWORD WINAPI _XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke) {
	typedef DWORD(__stdcall *MXInputGetKeystroke)(DWORD, DWORD, PXINPUT_KEYSTROKE);
	MXInputGetKeystroke Func = (MXInputGetKeystroke)mProcs[11];
	return Func(dwUserIndex, dwReserved, pKeystroke);
}

// XInputGetState
DWORD WINAPI _XInputGetState(DWORD dwUserIndex, XINPUT_STATE *pState) {
	typedef DWORD(__stdcall *MXInputGetState)(DWORD, XINPUT_STATE*);
	MXInputGetState Func = (MXInputGetState)mProcs[12];
	DWORD Result = Func(dwUserIndex, pState);
	if (Result == 0) { //0 out result doing nothing!
		memset(&pState->Gamepad, 0, sizeof(pState->Gamepad));
	}

	return Result;
}

// XInputSetState
DWORD WINAPI _XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration) {
	typedef DWORD(__stdcall *MXInputSetState)(DWORD, XINPUT_VIBRATION*);
	MXInputSetState Func = (MXInputSetState)mProcs[13];
	return Func(dwUserIndex, pVibration);
}

