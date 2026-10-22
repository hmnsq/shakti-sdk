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

#અન્તર્ભાવ<unistd.h>
#અન્તર્ભાવ<sys/types.h>
#અન્તર્ભાવ "platform.h"
#અન્તર્ભાવ "defines.h"
#અન્તર્ભાવ "log.h"

બાહ્ય અક્ષર* _HEAP_SIZE[];
અક્ષર* HEAP_SIZE = (અક્ષર *)&_HEAP_SIZE;

//Header block denotes start of the segment
સંરચના Header
{
	size_t size;
	પૂર્ણાંક મુક્ત;
	સંરચના Header* next;
};

સંરચના Header* global_base=ખાલી;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
સંરચના Header* allocate_block(સંરચના Header* last, size_t size)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	જો(last->size > size)
	{
		સંરચના Header* newblock;
		શૂન્ય *p = last;

		p += size + કદ(સંરચના Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->size = last->size - size - કદ(સંરચના Header);

		last->size = size;
		last->મુક્ત = 0;
		last->next = newblock;

		newblock->મુક્ત = 1;
		newblock->next = ખાલી;

		પાછા last;
	}
	નહીંતર
		પાછા ખાલી;
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
સંરચના Header *find_free_block(સંરચના Header **last, size_t size)
{
	log_trace("\nfind free entered");

	સંરચના Header *current = global_base;

	જ્યારે (current && !(current->મુક્ત && current->size >= size))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->size,size,current,*last);
		*last = current;
		current = current->next;
	}

	log_debug("\n After Loop %d %d %x %x",current->size,size,current,*last);

	જો(current && current->size>=size)
	{
		*last=current;
		પાછા current;
	}
	નહીંતર
		પાછા ખાલી;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
સંરચના Header* request_heap()
{
	સંરચના Header *block;

	block = m_sbrk(0);

	શૂન્ય *request = m_sbrk(HEAP_SIZE);

	જો((શૂન્ય*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	જો (request == (શૂન્ય*) -1) {
		log_error("\nNo space left to allocate memory");
		પાછા ખાલી; // sbrk failed.
	}

	block->size = HEAP_SIZE;
	block->next = ખાલી;
	block->મુક્ત = 1;

	log_debug("\nBlock Assigned");

	પાછા block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
શૂન્ય *malloc(size_t size)
{
	સંરચના Header *block;

	જો (size <= 0) {
               પાછા ખાલી;
	}

	log_info("\n global_base: %x",global_base);

	જો(global_base==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		block = request_heap();

		log_debug("\n block=%x",block);

		જો (!block)
		{
			પાછા ખાલી;
		}
		global_base = block;
	}

	સંરચના Header *last = global_base;

	block = find_free_block(&last, size);

	જો(!block)
	{
		log_error("\n No free blocks");
		પાછા ખાલી;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->size,size);

	જો (block->size>size)
	{
		// Failed to find free block.
		block = allocate_block(last,size);

		જો (!block)
		{
			પાછા ખાલી;
		}
	}
	નહીંતર જો(block->size==size)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->મુક્ત = 0;
	}

  પાછા(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
સંરચના Header *get_block_ptr(શૂન્ય *ptr)
{
  પાછા (સંરચના Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
શૂન્ય મુક્ત(શૂન્ય *ptr)
{
	જો (!ptr)
	{
		log_error("\n Wrong value passed to free");
		પાછા;
	}

	સંરચના Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	જો(block_ptr->મુક્ત==0)
		block_ptr->મુક્ત = 1;
}
