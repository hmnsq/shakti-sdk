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

#अन्तर्भाव<unistd.h>
#अन्तर्भाव<sys/types.h>
#अन्तर्भाव "platform.h"
#अन्तर्भाव "defines.h"
#अन्तर्भाव "log.h"

बाह्य अक्षर* _HEAP_SIZE[];
अक्षर* HEAP_SIZE = (अक्षर *)&_HEAP_SIZE;

//Header block denotes start of the segment
संरचना Header
{
	माप_प्रकार size;
	पूर्णांक मुक्त;
	संरचना Header* next;
};

संरचना Header* global_base=रिक्त;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
संरचना Header* allocate_block(संरचना Header* last, माप_प्रकार size)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	जर(last->size > size)
	{
		संरचना Header* newblock;
		शून्य *p = last;

		p += size + आकार(संरचना Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->size = last->size - size - आकार(संरचना Header);

		last->size = size;
		last->मुक्त = 0;
		last->next = newblock;

		newblock->मुक्त = 1;
		newblock->next = रिक्त;

		परत last;
	}
	अन्यथा
		परत रिक्त;
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
संरचना Header *find_free_block(संरचना Header **last, माप_प्रकार size)
{
	log_trace("\nfind free entered");

	संरचना Header *current = global_base;

	पर्यंत (current && !(current->मुक्त && current->size >= size))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->size,size,current,*last);
		*last = current;
		current = current->next;
	}

	log_debug("\n After Loop %d %d %x %x",current->size,size,current,*last);

	जर(current && current->size>=size)
	{
		*last=current;
		परत current;
	}
	अन्यथा
		परत रिक्त;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
संरचना Header* request_heap()
{
	संरचना Header *block;

	block = m_sbrk(0);

	शून्य *request = m_sbrk(HEAP_SIZE);

	जर((शून्य*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	जर (request == (शून्य*) -1) {
		log_error("\nNo space left to allocate memory");
		परत रिक्त; // sbrk failed.
	}

	block->size = HEAP_SIZE;
	block->next = रिक्त;
	block->मुक्त = 1;

	log_debug("\nBlock Assigned");

	परत block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
शून्य *दो_स्मृति(माप_प्रकार size)
{
	संरचना Header *block;

	जर (size <= 0) {
               परत रिक्त;
	}

	log_info("\n global_base: %x",global_base);

	जर(global_base==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		block = request_heap();

		log_debug("\n block=%x",block);

		जर (!block)
		{
			परत रिक्त;
		}
		global_base = block;
	}

	संरचना Header *last = global_base;

	block = find_free_block(&last, size);

	जर(!block)
	{
		log_error("\n No free blocks");
		परत रिक्त;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->size,size);

	जर (block->size>size)
	{
		// Failed to find free block.
		block = allocate_block(last,size);

		जर (!block)
		{
			परत रिक्त;
		}
	}
	अन्यथा जर(block->size==size)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->मुक्त = 0;
	}

  परत(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
संरचना Header *get_block_ptr(शून्य *ptr)
{
  परत (संरचना Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
शून्य मुक्त(शून्य *ptr)
{
	जर (!ptr)
	{
		log_error("\n Wrong value passed to free");
		परत;
	}

	संरचना Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	जर(block_ptr->मुक्त==0)
		block_ptr->मुक्त = 1;
}
