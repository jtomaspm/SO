# Exercise 1

### a)
only the code after the fork gets executed by the child process, since the program counter begins at the same location even if the two processes are clones.  
if the parent process dies before the child, the init process becomes the parent(PID=1)  


### b) 
the child process fork returns its PID, the parent return value is 0  
this can be used in an if statement to validate the parent and child.  

### c)
if the execl call is sucessfull the process is replaced with the provided one. This means that all the code after that execl call woun't run.  
the first 2 arguments for the exec call are the same since the first one is the path to the program and the second one is equivelent to args[0] of the main function, which is also the name of the program
as the parent process dies first the init process(PID=1) get owenership of the child process  

### d)
waits for the child process to finish then the code after that gets executed  

# Exercise 2

### a)
flushes stdout, meaning it will display what's on buffer to stdout
Ctrl+c ends the program
When you press CRTL+c, you are actually sending the SIGINT signal to the process.

### b)
Just need to map another sig to sigaction


# Challenge

O programa deve lançar um filho, o filho deve contar até 10, o pai deve esperar e só depois pode terminar.  

