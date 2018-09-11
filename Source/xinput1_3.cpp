#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <Xinput.h>
#include "xinput1_3.h"

#define XINPUT_GAMEPAD_GUIDE 0x400


HINSTANCE mHinst, mHinstDLL;
FARPROC mProcs[12];

LPCSTR mImportNames[] = {
	(LPCSTR )100, (LPCSTR )101, (LPCSTR )102, (LPCSTR )103, 
	"DllMain", "XInputEnable", "XInputGetBatteryInformation", "XInputGetCapabilities", 
	"XInputGetDSoundAudioDeviceGuids", "XInputGetKeystroke", "XInputGetState", "XInputSetState", 
};

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
	mHinst = hinstDLL;
	if ( fdwReason == DLL_PROCESS_ATTACH ) {
		char sysdir[255], path[255];
		GetSystemDirectory( sysdir, 254 );
		sprintf( path, "%s\\xinput1_3.old.dll", sysdir );
		mHinstDLL = LoadLibrary( path );
		if (!mHinstDLL) {
			sprintf(path, "%s\\xinput1_3.dll", sysdir);
			mHinstDLL = LoadLibrary(path);
			if (!mHinstDLL) return FALSE;
		}


		for ( int i = 0; i < 12; i++ )
			mProcs[ i ] = GetProcAddress( mHinstDLL, mImportNames[ i ] );
	} else if ( fdwReason == DLL_PROCESS_DETACH ) {
		FreeLibrary( mHinstDLL );
	}
	return ( TRUE );
}

DWORD WINAPI ordinal100(DWORD index, XINPUT_STATE *state) {
	typedef DWORD(__stdcall *MXInputGetStateEX)(DWORD, XINPUT_STATE *);
	MXInputGetStateEX Func = (MXInputGetStateEX)mProcs[0];
	return Func(index, state);
}

//  ?? 
INT_PTR WINAPI ordinal101() {
	return 0;
}

//  ?? 
INT_PTR WINAPI ordinal102() {
	return 0;
}

//  ?? 
INT_PTR WINAPI ordinal103() {
	return 0;
}

// DllMain
BOOL WINAPI _DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	typedef BOOL(__stdcall *MDLLMain)(HINSTANCE, DWORD, LPVOID);
	MDLLMain Func = (MDLLMain)mProcs[4];
	return Func(hinstDLL, fdwReason, lpvReserved);
}

// XInputEnable
void WINAPI _XInputEnable(BOOL enable) {
	typedef void(__stdcall *MXInputEnable)(BOOL);
	MXInputEnable Func = (MXInputEnable)mProcs[5];
	return Func(enable);
}

// XInputGetBatteryInformation
DWORD WINAPI _XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION *pBatteryInformation) {
	typedef DWORD(__stdcall *MXInputGetBatteryInformation)(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*);
	MXInputGetBatteryInformation Func = (MXInputGetBatteryInformation)mProcs[6];
	return Func(dwUserIndex, devType, pBatteryInformation);
}

// XInputGetCapabilities
DWORD WINAPI _XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES *pCapabilities) {
	typedef DWORD(__stdcall *MXInputGetCapabilities)(DWORD, DWORD, XINPUT_CAPABILITIES*);
	MXInputGetCapabilities Func = (MXInputGetCapabilities)mProcs[7];
	return Func(dwUserIndex, dwFlags, pCapabilities);
}


DWORD WINAPI XInputGetDSoundAudioDeviceGuids
(
	_In_  DWORD     dwUserIndex,          // Index of the gamer associated with the device
	_Out_ GUID*     pDSoundRenderGuid,    // DSound device ID for render (speakers)
	_Out_ GUID*     pDSoundCaptureGuid    // DSound device ID for capture (microphone)
);

// XInputGetDSoundAudioDeviceGuids
DWORD WINAPI _XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID *pDSoundRenderGuid, GUID *pDSoundCaptureGuid) {
	typedef DWORD(__stdcall *MXInputGetDSoundAudioDeviceGuids)(DWORD, GUID*, GUID*);
	MXInputGetDSoundAudioDeviceGuids Func = (MXInputGetDSoundAudioDeviceGuids)mProcs[8];
	return Func(dwUserIndex, pDSoundCaptureGuid, pDSoundRenderGuid);
}

// XInputGetKeystroke
DWORD WINAPI _XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke) {
	typedef DWORD(__stdcall *MXInputGetKeystroke)(DWORD, DWORD, PXINPUT_KEYSTROKE);
	MXInputGetKeystroke Func = (MXInputGetKeystroke)mProcs[9];
	return Func(dwUserIndex, dwReserved, pKeystroke);
}

// XInputGetState
DWORD WINAPI _XInputGetState(DWORD dwUserIndex, XINPUT_STATE *pState) {
	typedef DWORD(__stdcall *MXInputGetState)(DWORD, XINPUT_STATE*);
	MXInputGetState Func = (MXInputGetState)mProcs[10];
	DWORD Result = Func(dwUserIndex, pState);
	if (Result == 0) { //0 out result doing nothing!
		memset(&pState->Gamepad, 0, sizeof(pState->Gamepad));
	}

	return Result;
}

// XInputSetState
DWORD WINAPI _XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration) {
	typedef DWORD(__stdcall *MXInputSetState)(DWORD, XINPUT_VIBRATION*);
	MXInputSetState Func = (MXInputSetState)mProcs[11];
	return Func(dwUserIndex, pVibration);
}

