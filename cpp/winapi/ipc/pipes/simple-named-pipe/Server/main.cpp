#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

#define BUFSIZE 512

VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD);

DWORD WINAPI InstanceThread(LPVOID lpvParam)
// This routine is a thread processing function to read from and reply to a client
// via the open pipe connection passed from the main loop. Note this allows
// the main loop to continue executing, potentially creating more threads of
// of this procedure to run concurrently, depending on the number of incoming
// client connections.
{
    HANDLE hHeap = GetProcessHeap();
    TCHAR* pchRequest = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));
    TCHAR* pchReply = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));

    DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0;
    BOOL fSuccess = FALSE;
    HANDLE hPipe = NULL;

    // Do some extra error checking since the app will keep running even if this
    // thread fails.

    if (lpvParam == NULL)
    {
        _tprintf(_T("\n[*] Pipe Server - Processing thread: ERROR - Pipe Server Failure:\n"));
        _tprintf(_T("   InstanceThread got an unexpected NULL value in lpvParam.\n"));
        _tprintf(_T("   InstanceThread exitting.\n"));
        if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
        if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
        return (DWORD)-1;
    }

    if (pchRequest == NULL)
    {
        _tprintf(_T("\n[*] Pipe Server - Processing thread: ERROR - Pipe Server Failure:\n"));
        _tprintf(_T("   InstanceThread got an unexpected NULL heap allocation.\n"));
        _tprintf(_T("   InstanceThread exitting.\n"));
        if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
        return (DWORD)-1;
    }

    if (pchReply == NULL)
    {
        _tprintf(_T("\n[*] Pipe Server - Processing thread: ERROR - Pipe Server Failure:\n"));
        _tprintf(_T("   InstanceThread got an unexpected NULL heap allocation.\n"));
        _tprintf(_T("   InstanceThread exitting.\n"));
        if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
        return (DWORD)-1;
    }

    _tprintf(_T("[*] Pipe Server - Processing thread: Thread created, receiving and processing messages.\n"));

    // The thread's parameter is a handle to a pipe object instance.
    hPipe = (HANDLE)lpvParam;

    // Read requests and writes replies to the pipe until the pipe client closes its handle.
    while (1)
    {
        // Read client data from the pipe.
        // Note this simplistic code only allows messages up to BUFSIZE characters in length.
        fSuccess = ReadFile(
            hPipe,        // handle to pipe
            pchRequest,    // buffer to receive data
            BUFSIZE * sizeof(TCHAR), // size of buffer
            &cbBytesRead, // number of bytes read
            NULL);        // not overlapped I/O

        if (!fSuccess || cbBytesRead == 0)
        {
            if (GetLastError() == ERROR_BROKEN_PIPE)
            {
                _tprintf(_T("[*] Pipe Server - Processing thread: Client disconnected.\n"));
            }
            else
            {
                _tprintf(_T("[*] Pipe Server - Processing thread: ReadFile failed, GLE=%d.\n"), GetLastError());
            }
            break;
        }

        // Process the incoming message.
        GetAnswerToRequest(pchRequest, pchReply, &cbReplyBytes);

        // Write the reply to the pipe.
        fSuccess = WriteFile(
            hPipe,        // handle to pipe
            pchReply,     // buffer to write from
            cbReplyBytes, // number of bytes to write
            &cbWritten,   // number of bytes written
            NULL);        // not overlapped I/O

        if (!fSuccess || cbReplyBytes != cbWritten)
        {
            _tprintf(_T("[*] Pipe Server - Processing thread: WriteFile failed, GLE=%d.\n"), GetLastError());
            break;
        }
    }

    // When done, the thread
    // - flushes the pipe,
    // - disconnects,
    // - closes its pipe handle,
    // - and terminates.

    // Flush the pipe to allow the client to read the pipe's contents
    // before disconnecting. Then disconnect the pipe, and close the
    // handle to this pipe instance.
    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);

    HeapFree(hHeap, 0, pchRequest);
    HeapFree(hHeap, 0, pchReply);

    _tprintf(_T("[*] Pipe Server - Processing thread: Exiting.\n"));
    return 1;
}

VOID GetAnswerToRequest(LPTSTR pchRequest,
    LPTSTR pchReply,
    LPDWORD pchBytes)
    // This routine is a simple function to print the client request to the console
    // and populate the reply buffer with a default data string. This is where you
    // would put the actual client request processing code that runs in the context
    // of an instance thread. Keep in mind the main thread will continue to wait for
    // and receive other client connections while the instance thread is working.
{
    _tprintf(_T("[*] Pipe Server - Processing thread: Client Request String: \"%s\"\n"), pchRequest);

    // Check the outgoing message to make sure it's not too long for the buffer.
    if (FAILED(StringCchCopy(pchReply, BUFSIZE, _T("default answer from server"))))
    {
        *pchBytes = 0;
        pchReply[0] = 0;
        _tprintf(_T("[*] Pipe Server - Processing thread: StringCchCopy failed, no outgoing message.\n"));
        return;
    }
    *pchBytes = (lstrlen(pchReply) + 1) * sizeof(TCHAR);
}

int _tmain(int argc, TCHAR* argv[])
{
    BOOL   fConnected = FALSE;
    DWORD  dwThreadId = 0;
    HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL;
    LPCTSTR lpszPipename = _T("\\\\.\\pipe\\mynamedpipe");

    _tprintf(_T("Named-Pipe Server\n"));

    // The main thread has an infinite loop that creates an instance of the named pipe and then waits for a client to connect.
    // When a pipe client connects, a thread is created to handle communications with that client,
    // and this loop is free to wait for another connection.
    // This loop and the main thread will run until an error occurs or the process is ended.
    for (;;)
    {
        _tprintf(_T("[+] Pipe Server - Main Loop: Main thread awaiting client connection on %s\n"), lpszPipename);

        // Create an instance of the named pipe \\.\pipe\mynamedpipe
        hPipe = CreateNamedPipe(
            lpszPipename,             // pipe name
            PIPE_ACCESS_DUPLEX,       // read/write access
            // Type mode: message-type pipe (transmit data as a stream of messages instead of stream of bytes)
            // Read mode: message-read mode (read data as a stream of messages instead of stream of bytes)
            // Wait mode: blocking-wait mode (in the other hand, with PIPE_NOWAIT aka. nonblocking-wait mode,
            //   the functions return immediately in situations where PIPE_WAIT could lead to an indefinite wait.)
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES, // max. instances
            BUFSIZE,                  // output buffer size
            BUFSIZE,                  // input buffer size
            0,                        // client time-out
            NULL);                    // default security attribute

        if (hPipe == INVALID_HANDLE_VALUE)
        {
            _tprintf(_T("[+] Pipe Server - Main Loop: CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
            return -1;
        }

        // The pipe instance was created...

        // Wait for the client to connect.
        // If it succeeds, the function returns a nonzero value.
        // If the function returns zero, GetLastError returns ERROR_PIPE_CONNECTED if a client connected before the function is called.
        //   This can happen if a client connects in the interval between the call to CreateNamedPipe and the call to ConnectNamedPipe.
        //   In this situation, there is a good connection between client and server, even though the function returns zero.
        fConnected = ConnectNamedPipe(hPipe, NULL) ?
            TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

        if (fConnected)
        {
            // A client is connected...

            _tprintf(_T("[+] Pipe Server - Main Loop: Client connected, creating a processing thread.\n"));

            // Create a separate thread for this instance of the pipe.
            // The thread for each instance handles communications for a single pipe client.
            hThread = CreateThread(
                NULL,              // no security attribute
                0,                 // default stack size
                InstanceThread,    // thread proc (function to be executed by the thread)
                (LPVOID)hPipe,     // thread parameter (a pointer to a variable to be passed to the thread)
                0,                 // not suspended (run immediately after creation)
                &dwThreadId);      // thread ID output (a pointer to a variable that receives the thread identifier)

            if (hThread == NULL)
            {
                _tprintf(_T("[+] Pipe Server - Main Loop: CreateThread failed, GLE=%d.\n"), GetLastError());
                return -1;
            }
            // Clossing the handle of the created thread.
            // Note the thread continues working normally because CloseHandle() does not destroy, terminate or supspend the thread,
            // it only destroys the handle itself, so then you don't have a handle to kill the thread or wait on it.
            else CloseHandle(hThread);
        }
        else
            // The client could not connect, so close the pipe.
            CloseHandle(hPipe);
    }

    return 0;
}
