# C++ Custom Memory Allocator with FreeRTOS Heap
C++ Custom Memory Allocator using FreeRTOS Heap

If you are working on an embedded project which utilizes FreeRTOS with C++ then this would be interesting to you.

It is a Custom Memory Allocator which uses FreeRTOS Heap internally for Dynamic Memory Allocation/Usage.

You can use it with C++ STL functionalities such as; vector, set, shared pointer, map etc..

An example is given for vectors in main source file [main.cpp].


### Usage of Custom Memory Allocator
I have used FreeRTOS Heap5 for this project and for this i am initializing dynamic memory using malloc and using that memory region.
If you are working on Micro-Controller then you can define a particular RAM Memory region which FreeRTOS Heap shall use.
[I tested it using mingw64 Compiler on Windows system].





Explore it, you will definitely find it useful. Happy to help & Share.

Cheers :-)!
