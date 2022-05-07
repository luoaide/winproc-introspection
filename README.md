# Windows Process Introspection

## Input
the path to the target executable and a time interval

## Output
A table of handles that shows handles by type that the process interacted with.
The goal is to provide the analyst with a snapshot of the system resources used
by the process.


## Overview
1. Run our program with a path to the target executable
2. We will start a suspended process running your target
3. We will perform DLL injection on that process to hook CloseHandle
4. We will then start your process.
5. At the designated time interval, we will run handles.exe (from Sysinternals)
6. Whenever CloseHandle is called, we will log the resource being closed.
7. When the target process finishes or the user interupts, we will output results
8. The logs of resource names (handles.txt) will be filtered and we will present the set of all resources touched by the target.
