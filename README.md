# threaded-tape
a program that will read different parts of a tape. The tape itself is represented as a 1 dimensional byte array of n size.The user will input commands that will allow the tape to move back and forth by k steps. Each step will output to a file the data being read.  Each head is placed at an offset from the base or starting point of the tape (index 0), this offset is specified by the user. You are tasked with writing the command handler that will invoke functions related to tape head creation. Each head will write to its own respective file. If it is thread 1, it will write out to ./head1, thread 2 will write out to ./head2 and so on.  The main thread needs to wait until all threads have finished reading and writing out to a file. If it attempts to run another command while it is still reading/writing, it could compromise this process, therefore the main thread needs to wait until all other threads have completed and all threads will need to wait until the main thread runs a command.