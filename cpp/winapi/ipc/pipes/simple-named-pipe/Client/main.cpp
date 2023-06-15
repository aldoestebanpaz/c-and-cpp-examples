// ########################################################################
// Named pipe example.
// Pipe client.
// ########################################################################

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <conio.h>

#define BUFSIZE 512

bool OpenNamedPipeConnectionInstance(LPCTSTR lpcszPipename, HANDLE &hPipe) {
	// As soon as the pipe server creates a pipe instance, a pipe client can connect to it by calling the CreateFile or CallNamedPipe function.
	// If a pipe instance is available, CreateFile returns a handle to the client end of the pipe instance.
	// If no instances of the pipe are available, a pipe client can use the WaitNamedPipe function to wait until a pipe becomes available.

    // As soon as the pipe server creates a pipe instance, a pipe client can connect to it by calling the CreateFile or CallNamedPipe function.
    // If a pipe instance is available, CreateFile returns a handle to the client end of the pipe instance.
    // If no instances of the pipe are available, a pipe client can use the WaitNamedPipe function to wait until a pipe becomes available.
    while (1)
    {
        hPipe = CreateFile(
            lpcszPipename,                 // pipe name
            GENERIC_READ | GENERIC_WRITE,  // read and write access
            0,                             // no sharing
            NULL,                          // default security attributes
            OPEN_EXISTING,                 // opens existing pipe
            0,                             // default attributes
            NULL);                         // no template file

        // Break if the pipe handle is valid.
        if (hPipe != INVALID_HANDLE_VALUE)
            break;

        // Exit if an error other than ERROR_PIPE_BUSY occurs.
        // e.g. GLE=2 is the error ERROR_FILE_NOT_FOUND and means that given pipe does not exist.
        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            _tprintf(_T("Could not open pipe. GLE=%d\n"), GetLastError());
            return false;
        }

        // All pipe instances are busy, so wait for 20 seconds.
        if (!WaitNamedPipe(lpcszPipename, 20000))
        {
            _tprintf(_T("Could not open pipe: 20 second wait timed out."));
            return false;
        }
    }

    return true;
}

void SendMessage(HANDLE &hPipe, LPCTSTR lpvMessage) {
    BOOL    fSuccess = FALSE;
    DWORD   cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);

    _tprintf(_T("[+] Pipe Client: Sending %d byte message: \"%s\""), cbToWrite, lpvMessage);

    fSuccess = WriteFile(
        hPipe,                                 // pipe handle
        _T("Default message from client."),    // message
        cbToWrite,                             // message length
        nullptr,                               // bytes written
        NULL);                                 // not overlapped I/O

    if (!fSuccess)
    {
        _tprintf(_T("[+] Pipe Client: WriteFile to pipe failed. GLE=%d\n"), GetLastError());
    }

    _tprintf(_T("\n[+] Pipe Client: Message sent to server."));
}

void ReadMessage(HANDLE &hPipe) {
    TCHAR   chBuf[BUFSIZE];
    DWORD   cbRead;
    BOOL    fSuccess = FALSE;

    _tprintf(_T("\n[+] Pipe Client: Receiving reply...\n<Start of message>"));

    // When the message is larger than the read buffer, ReadFile returns zero after reading a partial message.
    // In this situation, GetLastError returns ERROR_MORE_DATA, and the client can read the remainder of the message using additional calls to ReadFile.
    do
    {
        // Read from the pipe.

        fSuccess = ReadFile(
            hPipe,    // pipe handle
            chBuf,    // buffer to receive reply
            BUFSIZE * sizeof(TCHAR),  // size of buffer
            &cbRead,  // number of bytes read
            NULL);    // not overlapped I/O

        if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
            break;

        _tprintf(_T("\n\"%s\""), chBuf);
    } while (!fSuccess);  // repeat loop if ERROR_MORE_DATA

    if (!fSuccess)
    {
        _tprintf(_T("[+] Pipe Client: ReadFile from pipe failed. GLE=%d"), GetLastError());
    }

    _tprintf(_T("\n<End of message>"));
}

int _tmain(int argc, TCHAR *argv[]) {
    HANDLE hPipe;

    LPTSTR lpvMessage = const_cast<LPTSTR>(_T("Default message from client."));

    if (argc > 1) {
        lpvMessage = argv[1];
    }

    _tprintf(_T("Named-Pipe Client\n"));

    // Connect to an instance of the named pipe \\.\pipe\mynamedpipe
    bool result = OpenNamedPipeConnectionInstance(_T("\\\\.\\pipe\\mynamedpipe"), hPipe);

    if (!result) {
        return -1;
    }

    // The pipe connected...

    // Set the read mode and wait mode of a pipe handle
    // Read mode: message-read mode (instead of byte-read).
    // Wait mode: (Not specified) (PIPE_WAIT is the default if no wait-mode flag is specified)
    DWORD dwMode = PIPE_READMODE_MESSAGE;
    bool fSuccess = SetNamedPipeHandleState(
        hPipe,    // pipe handle
        &dwMode,  // new pipe mode
        NULL,     // don't set maximum bytes
        NULL);    // don't set maximum time
    if (!fSuccess)
    {
        _tprintf(_T("[+] Pipe Client: SetNamedPipeHandleState failed. GLE=%d\n"), GetLastError());
        return -1;
    }

    // Write to the pipe
    SendMessage(hPipe, lpvMessage);

    // Read from the pipe
    ReadMessage(hPipe);

    _getch();
}
