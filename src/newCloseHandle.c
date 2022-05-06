// THIS FILE MUST REPLICATE THE STRUCTURE OF HANDLEAPI.H... I.E. GIVE IT THE SAME STRUCTURE:
// https://docs.microsoft.com/en-us/windows/win32/api/handleapi/

#include <stdio.h>
#include <windows.h>
#include <handleapi.h>
#pragma comment(lib, "user32.lib")

INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved) {
  int nResult = MessageBox(Null, "Fake handleapi.h Loaded!", "Life", MB_ICONINFORMATION | MB_OK);
  sleep(50000);
  return TRUE;
}

BOOL CloseHandle(HANDLE hObject) {
// FUNCTION HOOKING...
//MICROSOFT DETOURS
//PYTHON PE FILE LIBRARY HAS SOME HOOKING CAPABILITIES.
  // call the actual CloseHandle(hObject);
}


// BELOW NOT USED... JUST CALL THE ACTUAL HANDLEAPI.H Function
BOOL CompareObjectHandles(HANDLE hFirstObjectHandle, HANDLE hSecondObjectHandle) {
  // call actual
}

BOOL DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle, HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwOptions) {
  // call actual
}

BOOL GetHandleInformation(HANDLE  hObject, LPDWORD lpdwFlags) {
  // call actual
}

BOOL SetHandleInformation(HANDLE hObject, DWORD  dwMask, DWORD  dwFlags) {
  // call actual
}
