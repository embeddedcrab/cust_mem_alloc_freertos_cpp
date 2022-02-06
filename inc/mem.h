/*********************************************************************************************************************
 * @file     mem.h
 * @brief    Custom Memory Allocation API header
 * @version  1.0.0
 * @date     06/02/2022
 *
 */
/******************************************************************************
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/
#ifndef _MEM_H_
#define _MEM_H_

#include "heap.h"


void *Malloc( size_t size )
{
	return ( 0 ==size ? NULL : pvPortMalloc( size ) );
}

void Free( void * p_arg )
{
	vPortFree( p_arg );
}

void *Realloc( void * p_arg, size_t size )
{
	/* Local variables */
    (void) p_arg;
    (void) size;

    return NULL;
}

void *Calloc( size_t nmemb , size_t size )
{
	/* Local Variables */
	void * p_mem = NULL;
	size_t length = 0;

	/* Check for memory allocation */
	p_mem = (0 == nmemb || 0 ==size) ? NULL : pvPortMalloc( nmemb * size );

	/* Check memory validity and set it to Zero */
	if( p_mem != NULL )
	{
		char * p_mem_l = (char *) p_mem;
		for( length = 0; length < nmemb; ++length )
		{
			*p_mem_l = 0;
			++p_mem_l;
		}
	}

	/* Return allocated memory */
	return p_mem;
}


#endif	/* mem.h */

/********************************** End of File ******************************/
