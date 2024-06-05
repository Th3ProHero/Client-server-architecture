# 🚀 Process Manipulation with `wait()` and `kill()` in Linux 🛠️

## 🏆 Objective
Learn how to manipulate processes using the `wait()` and `kill()` functions, as well as utilizing Linux system signals.

## 📖 Introduction
### 🌀 Process States
A process can execute in user mode or kernel mode. The lifecycle of a process can be divided into various states, each with specific characteristics. Processes continually change states according to well-defined rules, influenced by the competition for scarce resources like the CPU.

### 🔄 Possible Process States
1. **User Mode Execution**.
2. **Kernel Mode Execution**.
3. **Ready to Execute in Memory** - Ready to run as soon as scheduled by the kernel.
4. **Sleeping in Memory** - Not ready to run until an event occurs; resides in main memory.
5. **Ready to Execute and Swapped Out** - Ready to run but must be loaded into main memory first.
6. **Sleeping and Swapped Out** - Waiting for an event and swapped to secondary storage.
7. **Swapped Out** - Returning from kernel mode to user mode but swapped out, allowing context switch.
8. **Created** - Newly created and not ready to execute.
9. **Zombie** - Process no longer exists but leaves a record for the parent process to collect.

### 📦 Process Context
A process's context includes its code, global user variable values, data structures, CPU register values, process table entry values, user and kernel stack values.

### 📡 Signals
Signals are a mechanism for process communication and manipulation in Linux. A signal is a special message sent to a process, and they are asynchronous. When a process receives a signal, it handles it immediately, without finishing the current line of code.

Signals are specified by numbers but referenced by names in programs. To use signals, include the `<signal.h>` header. The system sends signals to processes in response to specific conditions, e.g., `SIGBUS` (bus error), `SIGSEGV` (segmentation fault), `SIGFPE` (floating-point exception) terminate the process and produce a core file.

### 📤 Sending Signals
A process can also send signals to another process. For example, `SIGTERM` and `SIGKILL` are used to terminate processes, while `SIGHUP` is used to wake up a process.

A signal handler should do the minimal necessary work to handle the signal and return control to the main program or terminate it. A signal handler can be interrupted by another signal.

### 🗂️ Signal Groups
1. **Process Termination Signals**.
2. **Process-Induced Exception Signals** - e.g., accessing out-of-bounds memory, floating-point errors.
3. **Irrecoverable System Call Errors**.
4. **User-Mode Process Signals** - e.g., sending a signal via `kill`.
5. **Terminal Interaction Signals** - e.g., pressing Ctrl+C.
6. **Step-by-Step Execution Signals** - used by debuggers.

### 🚩 Common UNIX System V Signals
- **SIGHUP (1)**: Terminal disconnect or process group leader termination.
- **SIGINT (2)**: Interruption, usually via Ctrl+C.
- **SIGQUIT (3)**: Quit, usually via Ctrl+\.
- **SIGILL (4)**: Illegal instruction detected by hardware.
- **SIGTRAP (5)**: Trace trap, sent during step-by-step execution.
- **SIGIOT (6)**: I/O trap instruction.
- **SIGEMT (7)**: Emulator trap instruction.
- **SIGFPE (8)**: Floating-point error.
- **SIGKILL (9)**: Irrevocably terminates the process.
- **SIGBUS (10)**: Bus error due to invalid memory access.
- **SIGSEGV (11)**: Segmentation violation.
- **SIGSYS (12)**: Invalid system call argument.
- **SIGPIPE (13)**: Write to a pipe with no readers.
- **SIGALRM (14)**: Timer expired.
- **SIGTERM (15)**: Software termination signal.
- **SIGUSR1 (16)**: User-defined signal 1.
- **SIGUSR2 (17)**: User-defined signal 2.
- **SIGCLD (18)**: Child process terminated.
- **SIGPWR (19)**: Power failure.

## 🛠️ Development
### Example 1 - Process Waiting
Sometimes, a parent process needs to wait for all its child processes to complete. This can be achieved using the `wait()` function, which blocks the parent process until the child process finishes.

The `wait()` function returns a status code, providing information about how the child process terminated. Here are some useful macros for interpreting this status:
- **WIFEXITED**: Returns true if the child terminated normally.
- **WEXITSTATUS**: If `WIFEXITED` is true, returns the exit status.
- **WIFSIGNALED**: Returns true if the child process ended due to a signal.
- **WTERMSIG**: If `WIFSIGNALED` is true, returns the terminating signal number.
- **WCOREDUMP**: Returns true if a core dump was produced.
- **WIFSTOPPED**: Returns true if the process is stopped.
- **WSTOPSIG**: If `WIFSTOPPED` is true, returns the signal number that stopped the process.
