🚀 Process Manipulation with wait() and kill() in Linux 🛠️
🏆 Objective
Learn how to manipulate processes using the wait() and kill() functions, as well as utilizing Linux system signals.

📖 Introduction
🌀 Process States
A process can execute in user mode or kernel mode. The lifecycle of a process can be divided into various states, each with specific characteristics. Processes continually change states according to well-defined rules, influenced by the competition for scarce resources like the CPU.

🔄 Possible Process States
User Mode Execution.
Kernel Mode Execution.
Ready to Execute in Memory - Ready to run as soon as scheduled by the kernel.
Sleeping in Memory - Not ready to run until an event occurs; resides in main memory.
Ready to Execute and Swapped Out - Ready to run but must be loaded into main memory first.
Sleeping and Swapped Out - Waiting for an event and swapped to secondary storage.
Swapped Out - Returning from kernel mode to user mode but swapped out, allowing context switch.
Created - Newly created and not ready to execute.
Zombie - Process no longer exists but leaves a record for the parent process to collect.
📦 Process Context
A process's context includes its code, global user variable values, data structures, CPU register values, process table entry values, user and kernel stack values.

📡 Signals
Signals are a mechanism for process communication and manipulation in Linux. A signal is a special message sent to a process, and they are asynchronous. When a process receives a signal, it handles it immediately, without finishing the current line of code.

Signals are specified by numbers but referenced by names in programs. To use signals, include the <signal.h> header. The system sends signals to processes in response to specific conditions, e.g., SIGBUS (bus error), SIGSEGV (segmentation fault), SIGFPE (floating-point exception) terminate the process and produce a core file.

📤 Sending Signals
A process can also send signals to another process. For example, SIGTERM and SIGKILL are used to terminate processes, while SIGHUP is used to wake up a process.

A signal handler should do the minimal necessary work to handle the signal and return control to the main program or terminate it. A signal handler can be interrupted by another signal.

🗂️ Signal Groups
Process Termination Signals.
Process-Induced Exception Signals - e.g., accessing out-of-bounds memory, floating-point errors.
Irrecoverable System Call Errors.
User-Mode Process Signals - e.g., sending a signal via kill.
Terminal Interaction Signals - e.g., pressing Ctrl+C.
Step-by-Step Execution Signals - used by debuggers.
🚩 Common UNIX System V Signals
SIGHUP (1): Terminal disconnect or process group leader termination.
SIGINT (2): Interruption, usually via Ctrl+C.
SIGQUIT (3): Quit, usually via Ctrl+.
SIGILL (4): Illegal instruction detected by hardware.
SIGTRAP (5): Trace trap, sent during step-by-step execution.
SIGIOT (6): I/O trap instruction.
SIGEMT (7): Emulator trap instruction.
SIGFPE (8): Floating-point error.
SIGKILL (9): Irrevocably terminates the process.
SIGBUS (10): Bus error due to invalid memory access.
SIGSEGV (11): Segmentation violation.
SIGSYS (12): Invalid system call argument.
SIGPIPE (13): Write to a pipe with no readers.
SIGALRM (14): Timer expired.
SIGTERM (15): Software termination signal.
SIGUSR1 (16): User-defined signal 1.
SIGUSR2 (17): User-defined signal 2.
SIGCLD (18): Child process terminated.
SIGPWR (19): Power failure.
🛠️ Development
Example 1 - Process Waiting
Sometimes, a parent process needs to wait for all its child processes to complete. This can be achieved using the wait() function, which blocks the parent process until the child process finishes.

The wait() function returns a status code, providing information about how the child process terminated. Here are some useful macros for interpreting this status:

WIFEXITED: Returns true if the child terminated normally.
WEXITSTATUS: If WIFEXITED is true, returns the exit status.
WIFSIGNALED: Returns true if the child process ended due to a signal.
WTERMSIG: If WIFSIGNALED is true, returns the terminating signal number.
WCOREDUMP: Returns true if a core dump was produced.
WIFSTOPPED: Returns true if the process is stopped.
WSTOPSIG: If WIFSTOPPED is true, returns the signal number that stopped the process.
📜 Happy coding and process managing! 🚀

🌐 Client-Server SSH Project 🚀
📚 Overview
This project involves creating a Client-Server system that remotely executes commands, similar to commercial or free SSH Client-Server systems. Developed in C, this project emphasizes socket programming in a Linux environment.

📝 Table of Contents
Introduction
Requirements
Development
Libraries Used
Client-Server Communication
Client Program
Server Program
Program Functions
Final Output
Conclusion
References
Code
🎯 Requirements
Create a Client-Server system to execute remote commands.
Developed using TCP/IP sockets with remote connection.
Must be programmed in C within a Linux or MacOS environment.
📖 Development
I. Libraries Used
The libraries used in the project include:

stdio.h: Standard Input/Output functions.
stdlib.h: Dynamic memory management and utility functions.
string.h: String manipulation functions.
unistd.h: Unix standard functions.
sys/types.h: System data types.
sys/socket.h: Socket programming functions.
netinet/in.h: Network address structures.
arpa/inet.h: Internet operations.
II. Client-Server Communication
The Client and Server communicate remotely via TCP sockets. The Server listens for incoming connections from the Client.

III. Client Program
The Client program connects to the Server using the provided IP address and port. It sends commands to the Server and receives the execution results.

IV. Server Program
The Server program listens for incoming connections on a specified port. It executes the received commands and sends the results back to the Client.

V. Program Functions
Key functions include:

Creating the Client Socket: Using socket().
Configuring the Server Address Structure: Using struct sockaddr_in.
Connecting to the Server: Using connect().
Main Loop: Sending commands and receiving results.
VI. Final Output
The output demonstrates the Client connecting to the Server, sending commands, and receiving results.

🏁 Conclusion
This project showcases the implementation of a basic Client-Server architecture using C and socket programming in a Linux environment. The practical experience gained in network programming and system commands execution is invaluable for developing robust network applications.

📚 References
PROTECO. (n.d.). Sockets TCP/IP. Retrieved December 4, 2023, from UNAM.v
