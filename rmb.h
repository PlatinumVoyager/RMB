// define function prototype as well
LPWSTR returnMsgBuffer(DWORD errorCode);

// @param[in] errorCode - system error code returned from GetLastError()
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
