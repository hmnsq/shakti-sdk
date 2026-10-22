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

#ضمن<unistd.h>
#ضمن<sys/types.h>
#ضمن "platform.h"
#ضمن "defines.h"
#ضمن "log.h"

خارجي حرف* _HEAP_SIZE[];
حرف* HEAP_SIZE = (حرف *)&_HEAP_SIZE;

//Header block denotes start of the segment
بنية Header
{
	size_t size;
	صحيح حرر;
	بنية Header* next;
};

بنية Header* global_base=عدم;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
بنية Header* allocate_block(بنية Header* last, size_t size)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	إذا(last->size > size)
	{
		بنية Header* newblock;
		فراغ *p = last;

		p += size + حجم(بنية Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->size = last->size - size - حجم(بنية Header);

		last->size = size;
		last->حرر = 0;
		last->next = newblock;

		newblock->حرر = 1;
		newblock->next = عدم;

		أرجع last;
	}
	وإلا
		أرجع عدم;
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
بنية Header *find_free_block(بنية Header **last, size_t size)
{
	log_trace("\nfind free entered");

	بنية Header *current = global_base;

	طالما (current && !(current->حرر && current->size >= size))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->size,size,current,*last);
		*last = current;
		current = current->next;
	}

	log_debug("\n After Loop %d %d %x %x",current->size,size,current,*last);

	إذا(current && current->size>=size)
	{
		*last=current;
		أرجع current;
	}
	وإلا
		أرجع عدم;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
بنية Header* request_heap()
{
	بنية Header *block;

	block = m_sbrk(0);

	فراغ *request = m_sbrk(HEAP_SIZE);

	إذا((فراغ*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	إذا (request == (فراغ*) -1) {
		log_error("\nNo space left to allocate memory");
		أرجع عدم; // sbrk failed.
	}

	block->size = HEAP_SIZE;
	block->next = عدم;
	block->حرر = 1;

	log_debug("\nBlock Assigned");

	أرجع block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
فراغ *malloc(size_t size)
{
	بنية Header *block;

	إذا (size <= 0) {
               أرجع عدم;
	}

	log_info("\n global_base: %x",global_base);

	إذا(global_base==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		block = request_heap();

		log_debug("\n block=%x",block);

		إذا (!block)
		{
			أرجع عدم;
		}
		global_base = block;
	}

	بنية Header *last = global_base;

	block = find_free_block(&last, size);

	إذا(!block)
	{
		log_error("\n No free blocks");
		أرجع عدم;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->size,size);

	إذا (block->size>size)
	{
		// Failed to find free block.
		block = allocate_block(last,size);

		إذا (!block)
		{
			أرجع عدم;
		}
	}
	وإلا إذا(block->size==size)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->حرر = 0;
	}

  أرجع(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
بنية Header *get_block_ptr(فراغ *ptr)
{
  أرجع (بنية Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
فراغ حرر(فراغ *ptr)
{
	إذا (!ptr)
	{
		log_error("\n Wrong value passed to free");
		أرجع;
	}

	بنية Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	إذا(block_ptr->حرر==0)
		block_ptr->حرر = 1;
}
