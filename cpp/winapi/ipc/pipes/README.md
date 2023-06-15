
## What are Pipes?

A pipe is a section of shared memory that processes use for communication (aka. Interprocess Communications). The process that creates a pipe is the "pipe server". A process that connects to a pipe is a "pipe client".

### Types

There are two types of pipes:
- anonymous pipes
- and named pipes.

Anonymous pipes require less overhead than named pipes, but offer limited services.

### Anonymous Pipes

An anonymous pipe is an unnamed, one-way pipe that typically transfers data between a parent process and a child process. Anonymous pipes are always local; they cannot be used for communication over a network.


TODO

## How to enumerate pipes

Option 1: Use pipelist.exe from Sysinternals.

```powershell
# cd SysinternalsSuite

.\pipelist64.exe
```

Option 2: Use Process Explorer from sysinternals

- Open procexp64.exe
- Go to "Find > Find Handle or DLL..."
- Enter the pattern "\Device\NamedPipe\". It will show you which processes have which pipes open.

## How named pipes works

- Each named pipe has a unique name that distinguishes it from other named pipes in the system's list of named objects.
- A pipe server specifies a name for the pipe when it calls the `CreateNamedPipe` function to create one or more instances of a named pipe.
- Pipe clients specify the pipe name when they call the `CreateFile` or `CallNamedPipe` function to connect to an instance of the named pipe.
