/***************************************************************************
 * Project               	   : shakti devt board
 * Name of the file	           : malloc_firstfit.c
 * Brief Description of file       : Malloc using First-fit algorithm code.
 * Name of Author    	           : Abhinav Ramnath
 * Email ID                        : abhinavramnath13@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ***************************************************************************/
/**
@file malloc_firstfit.c
@brief Malloc using First-fit algorithm code.
@detail This algorithm implements the malloc function using the first-fit algorithm. It allocates and frees blocks of memory for usage.
*/ 

#അന്തര്ഭാവ<unistd.h>
#അന്തര്ഭാവ<sys/types.h>
#അന്തര്ഭാവ "platform.h"
#അന്തര്ഭാവ "defines.h"
#അന്തര്ഭാവ "log.h"

ബാഹ്യ അക്ഷരം* _HEAP_SIZE[];
അക്ഷരം* HEAP_SIZE = (അക്ഷരം *)&_HEAP_SIZE;

//Header block denotes start of the segment
ഘടന Header
{
	size_t size;
	പൂർണ്ണസംഖ്യ സ്വതന്ത്രം;
	ഘടന Header* next;
};

ഘടന Header* global_base=ശൂന്യ;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
ഘടന Header* allocate_block(ഘടന Header* last, size_t size)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	എങ്കിൽ(last->size > size)
	{
		ഘടന Header* newblock;
		ശൂന്യം *p = last;

		p += size + വലുപ്പം(ഘടന Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->size = last->size - size - വലുപ്പം(ഘടന Header);

		last->size = size;
		last->സ്വതന്ത്രം = 0;
		last->next = newblock;

		newblock->സ്വതന്ത്രം = 1;
		newblock->next = ശൂന്യ;

		തിരികെ last;
	}
	അല്ലെങ്കിൽ
		തിരികെ ശൂന്യ;
	log_trace("\nFunction allocate_block entered");
}

//We search for free blocks
/** @fn  struct Header *find_free_block(struct Header **last, size_t size)
 * @brief finds free blocks from the linked list of blocks in the memory
 * @detail  iterates through the linked list to find a block of required size that is free
 * @param  struct Header **last - pointer to the heap
 * @param  size_t size - size of the block 
 * @return returns a free block if available
 *         returns null if unavailable
 */
ഘടന Header *find_free_block(ഘടന Header **last, size_t size)
{
	log_trace("\nfind free entered");

	ഘടന Header *current = global_base;

	ആകുമ്പോൾ (current && !(current->സ്വതന്ത്രം && current->size >= size))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->size,size,current,*last);
		*last = current;
		current = current->next;
	}

	log_debug("\n After Loop %d %d %x %x",current->size,size,current,*last);

	എങ്കിൽ(current && current->size>=size)
	{
		*last=current;
		തിരികെ current;
	}
	അല്ലെങ്കിൽ
		തിരികെ ശൂന്യ;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
ഘടന Header* request_heap()
{
	ഘടന Header *block;

	block = m_sbrk(0);

	ശൂന്യം *request = m_sbrk(HEAP_SIZE);

	എങ്കിൽ((ശൂന്യം*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	എങ്കിൽ (request == (ശൂന്യം*) -1) {
		log_error("\nNo space left to allocate memory");
		തിരികെ ശൂന്യ; // sbrk failed.
	}

	block->size = HEAP_SIZE;
	block->next = ശൂന്യ;
	block->സ്വതന്ത്രം = 1;

	log_debug("\nBlock Assigned");

	തിരികെ block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
ശൂന്യം *malloc(size_t size)
{
	ഘടന Header *block;

	എങ്കിൽ (size <= 0) {
               തിരികെ ശൂന്യ;
	}

	log_info("\n global_base: %x",global_base);

	എങ്കിൽ(global_base==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		block = request_heap();

		log_debug("\n block=%x",block);

		എങ്കിൽ (!block)
		{
			തിരികെ ശൂന്യ;
		}
		global_base = block;
	}

	ഘടന Header *last = global_base;

	block = find_free_block(&last, size);

	എങ്കിൽ(!block)
	{
		log_error("\n No free blocks");
		തിരികെ ശൂന്യ;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->size,size);

	എങ്കിൽ (block->size>size)
	{
		// Failed to find free block.
		block = allocate_block(last,size);

		എങ്കിൽ (!block)
		{
			തിരികെ ശൂന്യ;
		}
	}
	അല്ലെങ്കിൽ എങ്കിൽ(block->size==size)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->സ്വതന്ത്രം = 0;
	}

  തിരികെ(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
ഘടന Header *get_block_ptr(ശൂന്യം *ptr)
{
  തിരികെ (ഘടന Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
ശൂന്യം സ്വതന്ത്രം(ശൂന്യം *ptr)
{
	എങ്കിൽ (!ptr)
	{
		log_error("\n Wrong value passed to free");
		തിരികെ;
	}

	ഘടന Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	എങ്കിൽ(block_ptr->സ്വതന്ത്രം==0)
		block_ptr->സ്വതന്ത്രം = 1;
}
