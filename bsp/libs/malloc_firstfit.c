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

#ಅನ್ತರ್ಭಾವ<unistd.h>
#ಅನ್ತರ್ಭಾವ<sys/types.h>
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "defines.h"
#ಅನ್ತರ್ಭಾವ "log.h"

ಬಾಹ್ಯ ವರ್ಣ* _HEAP_SIZE[];
ವರ್ಣ* HEAP_SIZE = (ವರ್ಣ *)&_HEAP_SIZE;

//Header block denotes start of the segment
ಸಂರಚನಾ Header
{
	size_t size;
	ಪೂರ್ಣಾಙ್ಕ ಮುಕ್ತ;
	ಸಂರಚನಾ Header* next;
};

ಸಂರಚನಾ Header* global_base=ರಿಕ್ತ;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
ಸಂರಚನಾ Header* allocate_block(ಸಂರಚನಾ Header* last, size_t size)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	ಯದಿ(last->size > size)
	{
		ಸಂರಚನಾ Header* newblock;
		ಶೂನ್ಯ *p = last;

		p += size + ಪರಿಮಾಣ(ಸಂರಚನಾ Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->size = last->size - size - ಪರಿಮಾಣ(ಸಂರಚನಾ Header);

		last->size = size;
		last->ಮುಕ್ತ = 0;
		last->next = newblock;

		newblock->ಮುಕ್ತ = 1;
		newblock->next = ರಿಕ್ತ;

		ಪ್ರತ್ಯಾಗಮ last;
	}
	ಅನ್ಯಥಾ
		ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
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
ಸಂರಚನಾ Header *find_free_block(ಸಂರಚನಾ Header **last, size_t size)
{
	log_trace("\nfind free entered");

	ಸಂರಚನಾ Header *current = global_base;

	ಯಾವತ್ (current && !(current->ಮುಕ್ತ && current->size >= size))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->size,size,current,*last);
		*last = current;
		current = current->next;
	}

	log_debug("\n After Loop %d %d %x %x",current->size,size,current,*last);

	ಯದಿ(current && current->size>=size)
	{
		*last=current;
		ಪ್ರತ್ಯಾಗಮ current;
	}
	ಅನ್ಯಥಾ
		ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
ಸಂರಚನಾ Header* request_heap()
{
	ಸಂರಚನಾ Header *block;

	block = m_sbrk(0);

	ಶೂನ್ಯ *request = m_sbrk(HEAP_SIZE);

	ಯದಿ((ಶೂನ್ಯ*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	ಯದಿ (request == (ಶೂನ್ಯ*) -1) {
		log_error("\nNo space left to allocate memory");
		ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ; // sbrk failed.
	}

	block->size = HEAP_SIZE;
	block->next = ರಿಕ್ತ;
	block->ಮುಕ್ತ = 1;

	log_debug("\nBlock Assigned");

	ಪ್ರತ್ಯಾಗಮ block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
ಶೂನ್ಯ *malloc(size_t size)
{
	ಸಂರಚನಾ Header *block;

	ಯದಿ (size <= 0) {
               ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	}

	log_info("\n global_base: %x",global_base);

	ಯದಿ(global_base==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		block = request_heap();

		log_debug("\n block=%x",block);

		ಯದಿ (!block)
		{
			ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
		}
		global_base = block;
	}

	ಸಂರಚನಾ Header *last = global_base;

	block = find_free_block(&last, size);

	ಯದಿ(!block)
	{
		log_error("\n No free blocks");
		ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->size,size);

	ಯದಿ (block->size>size)
	{
		// Failed to find free block.
		block = allocate_block(last,size);

		ಯದಿ (!block)
		{
			ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
		}
	}
	ಅನ್ಯಥಾ ಯದಿ(block->size==size)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->ಮುಕ್ತ = 0;
	}

  ಪ್ರತ್ಯಾಗಮ(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
ಸಂರಚನಾ Header *get_block_ptr(ಶೂನ್ಯ *ptr)
{
  ಪ್ರತ್ಯಾಗಮ (ಸಂರಚನಾ Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
ಶೂನ್ಯ ಮುಕ್ತ(ಶೂನ್ಯ *ptr)
{
	ಯದಿ (!ptr)
	{
		log_error("\n Wrong value passed to free");
		ಪ್ರತ್ಯಾಗಮ;
	}

	ಸಂರಚನಾ Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	ಯದಿ(block_ptr->ಮುಕ್ತ==0)
		block_ptr->ಮುಕ್ತ = 1;
}
