# cust_mem_alloc_freertos_cpp
C++ Custom Memory Allocator using FreeRTOS Heap

If you are working on an embedded project which utilizes FreeRTOS with C++ then this would be interesting to you.

It is a Custom Memory Allocator which uses FreeRTOS Heap internally for Dynamic Memory Allocation and Usage.

You can use it with C++ STL functionalities such as; vector, set, shared pointer, map etc..

An example is given for vectors in main source file [main.cpp].


### Usage of Custom Memory Allocator
I have used FreeRTOS Heap5 for this project and for this i am initializing dynamic memory using malloc and using that memory region.
If you are working on Micro-Controller then you can define a particular RAM Memory region which FreeRTOS Heap shall use.
[I tested it using mingw64 Compiler on Windows system].


Folder Structure:
inc
	-	allocator.h	[Memory Allocator]
	-	heap.h	[FreeRTOS Heap Header]
	-	mem.h	[Wrapper header]
src
	-	heap.cpp	[FreeRTOS Heap SOurce File]

main.cpp	[Main Source file, containing example]



Explore it, you will definitely find it useful. Happy to help & Share.

Cheers :-)!
