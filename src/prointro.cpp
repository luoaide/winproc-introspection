#include <windows.h>
#include <stdio.h>
#include "detours.h"
#include "detver.h"
#include "syelog.h"
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "user32.lib")


// Address of the real CloseHandle API
BOOL (WINAPI *True_CloseHandle)(HANDLE) = CloseHandle;
 
// Our intercept function
BOOL WINAPI HookedCloseHandle(HANDLE hObject)
{
    // Run handles.exe here with PID
    int handle_pid = GetCurrentProcessId();
    system("C:\\Users\\user\\Desktop\\project\\winproc-introspection\\src\\Handle\\handle.exe -p " + handle_pid);
    return True_CloseHandle(hObject);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID p)
{
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
        {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID&)True_CloseHandle, HookedCloseHandle);
    
            LONG lError = DetourTransactionCommit();
            if (lError != NO_ERROR) {
                MessageBox(NULL, "Process Introspection", "DLL NOT INJECTED", MB_ICONINFORMATION|MB_OK);
                return FALSE;
            }
        }
        break;
    
        case DLL_PROCESS_DETACH:
        {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourDetach(&(PVOID&)True_CloseHandle, HookedCloseHandle);
    
            LONG lError = DetourTransactionCommit();
            if (lError != NO_ERROR) {
                MessageBox(NULL, "Process Introspection", "DLL NOT INJECTED", MB_ICONINFORMATION|MB_OK);
                return FALSE;
            }
        }
        break;
    }
}





