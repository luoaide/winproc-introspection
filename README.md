# Windows Process Introspection

## Input
PE32 File.

## Output
A table of handles that shows handles by type that the process interacted with.
The goal is to provide the analyst with a snapshot of the system resources used
by the process.


## What

Look inside a running process... what useful information can we grab
Every process has a handle table in memory
API calls all return handles to resources... get added to table.

Is it a snapshot? Or do we return results in live time or when it terminates?

closeHandle removes a handle from the process table.


How do we look inside a processes memory space... DLL injection? We need to hook
onto the process.

Existing Tool --> sysInternals gives us some functionality
handle64 and handle (32 bit) gives us some abilities

this shows us all the handles that are currently being used by the process... the problem is that this is just a snapshot in time. We want to reverse engineer the handle64 tool and analyze all the handles over the lifespan.
