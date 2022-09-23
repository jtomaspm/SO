# Ex 1

## A)

The support data structures are declared in the .cpp file since the header file is only an interface meant to let the compiler know what methods its implementation needs to implement and has access to.  

Nodehead being static mean it can only be linked to (accessed) from references inside the same file, with means that even if it is declared inside the global scope only the instance that owns it can use it, aka only the list that owns the head can interact with the head.

Namespace help us separate our code. In this exercise we are implementing very common functions known as CRUD operations, namespaces help us ensure we  are actually calling the right function and not one with the same name.


## B)


