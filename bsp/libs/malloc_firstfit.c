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

#அந்தர்பாவ<unistd.h>
#அந்தர்பாவ<sys/types.h>
#அந்தர்பாவ "platform.h"
#அந்தர்பாவ "defines.h"
#அந்தர்பாவ "log.h"

வெளி எழுத்து* _HEAP_SIZE[];
எழுத்து* HEAP_SIZE = (எழுத்து *)&_HEAP_SIZE;

//Header block denotes start of the segment
கட்டமைப்பு Header
{
	size_t size;
	முழு விடுவி;
	கட்டமைப்பு Header* next;
};

கட்டமைப்பு Header* global_base=வெற்று;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
கட்டமைப்பு Header* allocate_block(கட்டமைப்பு Header* last, size_t size)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	எனில்(last->size > size)
	{
		கட்டமைப்பு Header* newblock;
		வெறுமை *p = last;

		p += size + அளவு(கட்டமைப்பு Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->size = last->size - size - அளவு(கட்டமைப்பு Header);

		last->size = size;
		last->விடுவி = 0;
		last->next = newblock;

		newblock->விடுவி = 1;
		newblock->next = வெற்று;

		திரும்பு last;
	}
	இல்லையெனில்
		திரும்பு வெற்று;
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
கட்டமைப்பு Header *find_free_block(கட்டமைப்பு Header **last, size_t size)
{
	log_trace("\nfind free entered");

	கட்டமைப்பு Header *current = global_base;

	போது (current && !(current->விடுவி && current->size >= size))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->size,size,current,*last);
		*last = current;
		current = current->next;
	}

	log_debug("\n After Loop %d %d %x %x",current->size,size,current,*last);

	எனில்(current && current->size>=size)
	{
		*last=current;
		திரும்பு current;
	}
	இல்லையெனில்
		திரும்பு வெற்று;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
கட்டமைப்பு Header* request_heap()
{
	கட்டமைப்பு Header *block;

	block = m_sbrk(0);

	வெறுமை *request = m_sbrk(HEAP_SIZE);

	எனில்((வெறுமை*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	எனில் (request == (வெறுமை*) -1) {
		log_error("\nNo space left to allocate memory");
		திரும்பு வெற்று; // sbrk failed.
	}

	block->size = HEAP_SIZE;
	block->next = வெற்று;
	block->விடுவி = 1;

	log_debug("\nBlock Assigned");

	திரும்பு block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
வெறுமை *malloc(size_t size)
{
	கட்டமைப்பு Header *block;

	எனில் (size <= 0) {
               திரும்பு வெற்று;
	}

	log_info("\n global_base: %x",global_base);

	எனில்(global_base==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		block = request_heap();

		log_debug("\n block=%x",block);

		எனில் (!block)
		{
			திரும்பு வெற்று;
		}
		global_base = block;
	}

	கட்டமைப்பு Header *last = global_base;

	block = find_free_block(&last, size);

	எனில்(!block)
	{
		log_error("\n No free blocks");
		திரும்பு வெற்று;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->size,size);

	எனில் (block->size>size)
	{
		// Failed to find free block.
		block = allocate_block(last,size);

		எனில் (!block)
		{
			திரும்பு வெற்று;
		}
	}
	இல்லையெனில் எனில்(block->size==size)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->விடுவி = 0;
	}

  திரும்பு(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
கட்டமைப்பு Header *get_block_ptr(வெறுமை *ptr)
{
  திரும்பு (கட்டமைப்பு Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
வெறுமை விடுவி(வெறுமை *ptr)
{
	எனில் (!ptr)
	{
		log_error("\n Wrong value passed to free");
		திரும்பு;
	}

	கட்டமைப்பு Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	எனில்(block_ptr->விடுவி==0)
		block_ptr->விடுவி = 1;
}
