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
PROTECO. (n.d.). Sockets TCP/IP. Retrieved December 4, 2023, from UNAM.