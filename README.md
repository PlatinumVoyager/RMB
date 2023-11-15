![image](https://github.com/PlatinumVoyager/RMB/assets/116006542/91315e15-e29a-4a91-beda-c992450b2375)

Return Message Buffer: Generic C utility header file with a language neutral `GetLastError()` function parser.

## Usage
Include: `rmb.h`

Example: 
```c 
#include <Windows.h> // <-- must be imported as top level declaration (topmost header file)

#include "rmb.h" // <-- included header file


int main(void)
{
  UINT returnCode;

  // GenericWindowsAPIError() - dummy function to display usage of returnMsgBuffer()
  if ((returnCode = GenericWindowsAPIError()) == MMSYSERR_NOERR)
  {
    // continue here, no error
    ;;
  }
  else
  {
    DWORD error = GetLastError(); // <- call to get last threads error-code value

    // call `returnMsgBuffer()` to convert system error to UTF-16 w/ LE BOM (Byte order Mark)
    // the Byte Order Mark or BOM is an identifier set by the first two bytes in a data stream that is to be
    // interpreted as text by the calling processes/application, etc. The BOM defines the endian value of the data stream.
    // this value can either be of LE (Little Endian) or BE (Big Endian) variants.
    // LE = least significant bit of binary representation is processed first. BE = most significant bit of binary representation is processed first.
    fwprintf(stderr, L"Error - %s\n", returnMsgBuffer(error));  // <- a.k.a convert system bit error message to a human readable text string and print to standard out

    // Ex: Error - The cluster quorum resource is not allowed to have any dependencies.
  }

  // your code goes here

  return 0;
}
```

## How it works
RMB simply calls a Windows 32 bit API function that is responsible for retrieving the calling threads last-error code value. This value is defined in the 
<a href="https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes#system-error-codes"><i>Windows Debug System Error Code Index</i></a>
(*WDSECI*)

> [!NOTE]
System defined error codes are 32 bit "Double Words" or a DWORD (unsigned long) in size. The 29th bit is reserved for application specific error codes. Bit 31 is the most significant bit.

WDSECI is an entry of Windows defined system wide error codes that an application (calling process -> spawn threads) can push onto the stack of its local "virtually" allocated thread context. These values are simply stored in registers that vary depending upon the device CPU architecture to which the current process is using its alloted time-slice (i.e, RUNNING state).


```c
LPWSTR returnMsgBuffer(DWORD errorCode)
{
    LPWSTR msgBuffer = NULL;

    DWORD result = FormatMessageW
    (
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&msgBuffer,
        0,
        NULL
    );

    return msgBuffer;
}
```
