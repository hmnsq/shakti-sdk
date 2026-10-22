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

#অন্তর্ভাব<unistd.h>
#অন্তর্ভাব<sys/types.h>
#অন্তর্ভাব "platform.h"
#অন্তর্ভাব "defines.h"
#অন্তর্ভাব "log.h"

বাহ্য বর্ণ* _HEAP_SIZE[];
বর্ণ* HEAP_SIZE = (বর্ণ *)&_HEAP_SIZE;

//Header block denotes start of the segment
সংরচনা Header
{
	size_t size;
	পূর্ণাঙ্ক মুক্ত;
	সংরচনা Header* next;
};

সংরচনা Header* global_base=রিক্ত;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
সংরচনা Header* allocate_block(সংরচনা Header* last, size_t size)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	যদি(last->size > size)
	{
		সংরচনা Header* newblock;
		শূন্য *p = last;

		p += size + পরিমাণ(সংরচনা Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->size = last->size - size - পরিমাণ(সংরচনা Header);

		last->size = size;
		last->মুক্ত = 0;
		last->next = newblock;

		newblock->মুক্ত = 1;
		newblock->next = রিক্ত;

		প্রত্যাগম last;
	}
	অন্যথা
		প্রত্যাগম রিক্ত;
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
সংরচনা Header *find_free_block(সংরচনা Header **last, size_t size)
{
	log_trace("\nfind free entered");

	সংরচনা Header *current = global_base;

	যাবত্ (current && !(current->মুক্ত && current->size >= size))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->size,size,current,*last);
		*last = current;
		current = current->next;
	}

	log_debug("\n After Loop %d %d %x %x",current->size,size,current,*last);

	যদি(current && current->size>=size)
	{
		*last=current;
		প্রত্যাগম current;
	}
	অন্যথা
		প্রত্যাগম রিক্ত;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
সংরচনা Header* request_heap()
{
	সংরচনা Header *block;

	block = m_sbrk(0);

	শূন্য *request = m_sbrk(HEAP_SIZE);

	যদি((শূন্য*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	যদি (request == (শূন্য*) -1) {
		log_error("\nNo space left to allocate memory");
		প্রত্যাগম রিক্ত; // sbrk failed.
	}

	block->size = HEAP_SIZE;
	block->next = রিক্ত;
	block->মুক্ত = 1;

	log_debug("\nBlock Assigned");

	প্রত্যাগম block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
শূন্য *malloc(size_t size)
{
	সংরচনা Header *block;

	যদি (size <= 0) {
               প্রত্যাগম রিক্ত;
	}

	log_info("\n global_base: %x",global_base);

	যদি(global_base==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		block = request_heap();

		log_debug("\n block=%x",block);

		যদি (!block)
		{
			প্রত্যাগম রিক্ত;
		}
		global_base = block;
	}

	সংরচনা Header *last = global_base;

	block = find_free_block(&last, size);

	যদি(!block)
	{
		log_error("\n No free blocks");
		প্রত্যাগম রিক্ত;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->size,size);

	যদি (block->size>size)
	{
		// Failed to find free block.
		block = allocate_block(last,size);

		যদি (!block)
		{
			প্রত্যাগম রিক্ত;
		}
	}
	অন্যথা যদি(block->size==size)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->মুক্ত = 0;
	}

  প্রত্যাগম(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
সংরচনা Header *get_block_ptr(শূন্য *ptr)
{
  প্রত্যাগম (সংরচনা Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
শূন্য মুক্ত(শূন্য *ptr)
{
	যদি (!ptr)
	{
		log_error("\n Wrong value passed to free");
		প্রত্যাগম;
	}

	সংরচনা Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	যদি(block_ptr->মুক্ত==0)
		block_ptr->মুক্ত = 1;
}
