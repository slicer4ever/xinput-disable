#ifndef __xinput1_3_h__
#define __xinput1_3_h__

#define naked __declspec(naked)
#define inline __forceinline


extern FARPROC mProcs[];
inline INT_PTR callordinal100() { return mProcs[0](); }
inline INT_PTR callordinal101() { return mProcs[1](); }
inline INT_PTR callordinal102() { return mProcs[2](); }
inline INT_PTR callordinal103() { return mProcs[3](); }
inline INT_PTR call_DllMain() { return mProcs[4](); }
inline INT_PTR call_XInputEnable() { return mProcs[5](); }
inline INT_PTR call_XInputGetBatteryInformation() { return mProcs[6](); }
inline INT_PTR call_XInputGetCapabilities() { return mProcs[7](); }
inline INT_PTR call_XInputGetDSoundAudioDeviceGuids() { return mProcs[8](); }
inline INT_PTR call_XInputGetKeystroke() { return mProcs[9](); }
inline INT_PTR call_XInputGetState() { return mProcs[10](); }
inline INT_PTR call_XInputSetState() { return mProcs[11](); }

#endif // __xinput1_3_h__
