/*********************************************************************************************************************
 * @file     main.cpp
 * @brief    Main Source
 * @version  1.0.0
 * @date     06/02/2022
 *
 * @cond
 *********************************************************************************************************************
 * Copyright (c) 2022, Hemant Sharma - All Rights Reserved
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************************************************************
 *
 * *************************** Change history ********************************
 *
 * @endcond
 */
/******************************************************************************
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	main.cpp
 *  @brief:	This file contains main Source for Memory Allocation Example.
 */
#include <iostream>

#include "allocator.h"

#include <cstdlib>
#include <new>
#include <vector>
#include <set>
#include <memory>
#include <map>


extern "C"
{
void ConstructHeapMemory () __attribute__ ((constructor));
void DestructHeapMemory () __attribute__ ((destructor));

#ifdef USE_HEAP_4

#elif defined(USE_HEAP_5)
// Heap 5 specific memory allocation variables
#define HEAP_ARRAY_COUNTS   2
HeapRegion_t xHeapRegions[HEAP_ARRAY_COUNTS + 1] =
{
  { NULL, 0x10000 }, // Defines a block of 0x10000 bytes starting at address 0x80000000
  { NULL, 0xa0000 }, // Defines a block of 0xa0000 bytes starting at address of 0x90000000
  { NULL, 0 }
};
#endif

void ConstructHeapMemory( void )
{
#ifdef USE_HEAP_4

// Note: It is using statically allocated memory, but can be changed

#elif defined(USE_HEAP_5)
  uint8_t * memPtr = NULL;
  uint8_t * memPtr2 = NULL;

  memPtr = (uint8_t *) malloc(0x10000);
  if( memPtr != NULL )
  {
    // Fill Memory Address into array
    xHeapRegions[0].pucStartAddress = memPtr;
    uint8_t * memPtr2 = (uint8_t *) malloc(0xa0000);
    if( memPtr2 != NULL )
    {
      xHeapRegions[1].pucStartAddress = memPtr2;
    }
    else
    {
      free(memPtr);
      exit(-1);
    }
  }
  else
  {
    exit(-1);
  }

  // Initialize Memory for Heap Allocation
  vPortDefineHeapRegions( xHeapRegions );
#endif
  printf("%s", "\n heap Memory Construct\n\n");
}

void DestructHeapMemory( void )
{
#ifdef USE_HEAP_4

#elif defined(USE_HEAP_5)
  for( uint8_t count = 0; count < HEAP_ARRAY_COUNTS; ++count )
  {
    if( xHeapRegions[count].pucStartAddress != NULL )
    {
      free(xHeapRegions[count].pucStartAddress);
    }
  }
#endif
  printf("%s", "\n heap Memory Destructed\n\n");
}

}


void printHeapStats( HeapStats_t* pstats )
{
    std::cout<< "xAvailableHeapSpaceInBytes - " << pstats->xAvailableHeapSpaceInBytes << "\t"
        << "xSizeOfLargestFreeBlockInBytes - " << pstats->xSizeOfLargestFreeBlockInBytes << "\n"
        << "xSizeOfSmallestFreeBlockInBytes - " << pstats->xSizeOfSmallestFreeBlockInBytes << "\t"
        << "xNumberOfFreeBlocks - " << pstats->xNumberOfFreeBlocks << "\n"
        << "xMinimumEverFreeBytesRemaining - " << pstats->xMinimumEverFreeBytesRemaining << "\t"
        << "xNumberOfSuccessfulAllocations - " << pstats->xNumberOfSuccessfulAllocations << "\n"
        << "xNumberOfSuccessfulFrees - " << pstats->xNumberOfSuccessfulFrees << std::endl;
}


// struct Example
// {
//   int value;

//   Example(int v) :
//       value(v)
//   {}

//   bool operator<(Example const& other) const
//   {
//       return value < other.value;
//   }
// };


CustomMAllocator<int> intAlloc;


int main()
{

  HeapStats_t heapStats{};
  vPortGetHeapStats(&heapStats);
  printHeapStats(&heapStats);

  // {
  //   std::set<Example, std::less<Example>, allocator<Example, CustomMAllocator<Example>>> foo;
  //   foo.insert(Example(3));
  //   foo.insert(Example(1));
  //   foo.insert(Example(4));
  //   foo.insert(Example(2));
  // }

  {
    std::vector<int, CustomMAllocator<int>> myVect(8);
    myVect.at(0) = 1;
    myVect.push_back(42);
    myVect.push_back(2);

    for (auto v : myVect)
    {
      std::cout << v << "\n";
    }
  }

  // {
  //   std::shared_ptr<int> ptr = std::allocate_shared<int>(intAlloc, 5);

  //   std::map<int, std::string, std::less<int>, allocator<std::pair<const int, std::string>, CustomMAllocator<std::pair<int, std::string>>>> myMap;
  //   myMap.emplace(std::make_pair(5, "Hello"));
  // }

  // {
  //   std::map<int, Example, std::less<int>, allocator<std::pair<const int, Example>, CustomMAllocator<std::pair<int, Example>>>> myMap;
  //   myMap.emplace(std::make_pair(5, Example(1)));
  // }
  vPortGetHeapStats(&heapStats);
  printHeapStats(&heapStats);

  std::cout << "End\n";
  return 0;
}
