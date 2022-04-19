#include <stdio.h>
#include <windows.h>
#include <handleapi.h>
#pragma comment(lib, "user32.lib")

INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved) {
  int nResult = MessageBox(Null, "DLL Injected!", "Life", MB_ICONINFORMATION | MB_OK);
  sleep(50000);
  return TRUE;
}

BOOL CloseHandle(HANDLE hObject) {

  // call the actual CloseHandle(hObject);

}
