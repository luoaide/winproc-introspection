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
              MessageBox(HWND_DESKTOP, L"Failed to detour", L"Process Instrospection", MB_OK);
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
              MessageBox(HWND_DESKTOP, L"Failed to detour", L"Process Instrospection", MB_OK);
              return FALSE;
          }
      }
      break;
  }
}

// Address of the real WriteFile API
BOOL (WINAPI *True_CloseHandle)(HANDLE) = CloseHandle;

// Our intercept function
BOOL WINAPI HookedCloseHandle(HANDLE hObject) {
  //DO STUFF
  return True_CloseHandle(hObject);
}
