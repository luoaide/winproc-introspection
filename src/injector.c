#include <stdio.h>
#include <windows.h>
#include <TlHelp32.h>
#include <string.h>
#pragma comment(lib, "user32.lib")
#define WIN32_DEFAULT_LIBS

// get the PID of the target/victim process
DWORD GetPID() {
  PROCESSENTRY32 entry;
  entry.dwSize = sizeof(PROCESSENTRY32);

  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  if(Process32First(snapshot, &entry) == TRUE) {
    while(Process32Next(snapshot, &entry) == TRUE) {
      // the name in strcmp is the victim/target we're looking for
      if(strcmp(entry.szExeFile, "Message.exe") == 0) {
        CloseHandle(snapshot);
        return entry.th32ProcessID;
      }
    }
  }
  CloseHandle(snapshot);
  return 0;
}

int main(int argc, char* argv[]) {
  char* buffer = "inject_me.dll";
  int procID = GetPID();
  if(0 == procID) {
    ExitProcess(0);
  }
  HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
  // we want to get LoadLibrary from it's dll, which is "kernel32.dll"
  LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
  // now we have a address to the method we want to load into the victim process memory space
  // like malloc, VirtualAllocEx allocated virtual address space
  LPVOID arg = (LPVOID)VirtualAllocEx(process, NULL, strlen(buffer), MEM_RESERVE | MEM_CONTENT, PAGE_READWRITE);
  // Write the argument for LoadLibrary into target process memory:
  int n = WriteProcessMemory(process, arg, buffer, strlen(buffer), NULL);
  // Inject DLL into Process's address space:
  HANDLE threadID = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)addr, arg, 0, NULL);
  CloseHandle(process);
  ExitProcess(0);
}
