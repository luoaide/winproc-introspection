#include <windows.h>
#include <stdio.h>
#include "detours.h"
#include "detver.h"
#include "syelog.h"
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "user32.lib")
#define WIN32_DEFAULT_LIBS

//Get Process ID (PID) of target process
DWORD GetPID()
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while(Process32Next(snapshot, &entry) == TRUE)
		{
			if(strcmp(entry.szExeFile, "ProcessIntrospection.exe")==0)
			{
				CloseHandle(snapshot);
				return entry.th32ProcessID;
			}
		}
	}
	CloseHandle(snapshot);
	return 0;
}

int main(int argc, char* argv[])
{
	char* buffer = "prointro.dll";
	int procID = GetPID();
	if (procID == 0)
		ExitProcess(0);
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"),
		"LoadLibraryA");
	LPVOID arg = (LPVOID)VirtualAllocEx(process, NULL, strlen(buffer),
					MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	// Write the argument for LoadLibrary into target space:
	int n = WriteProcessMemory(process, arg, buffer, strlen(buffer), NULL);
	// Inject DLL into Process's address space:
	HANDLE threadID = CreateRemoteThread(process, NULL, 0,
						(LPTHREAD_START_ROUTINE)addr, arg, 0, NULL);
	CloseHandle(process);
	ExitProcess(0);
}