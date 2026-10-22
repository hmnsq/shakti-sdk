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

#ଅନ୍ତର୍ଭାଵ<unistd.h>
#ଅନ୍ତର୍ଭାଵ<sys/types.h>
#ଅନ୍ତର୍ଭାଵ "platform.h"
#ଅନ୍ତର୍ଭାଵ "defines.h"
#ଅନ୍ତର୍ଭାଵ "log.h"

ବାହ୍ୟ ଅକ୍ଷର* _HEAP_SIZE[];
ଅକ୍ଷର* HEAP_SIZE = (ଅକ୍ଷର *)&_HEAP_SIZE;

//Header block denotes start of the segment
ସଂରଚନା Header
{
	size_t size;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁକ୍ତ;
	ସଂରଚନା Header* next;
};

ସଂରଚନା Header* global_base=ଖାଲି;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
ସଂରଚନା Header* allocate_block(ସଂରଚନା Header* last, size_t size)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	ଯଦି(last->size > size)
	{
		ସଂରଚନା Header* newblock;
		ଶୂନ୍ୟ *p = last;

		p += size + ଆକାର(ସଂରଚନା Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->size = last->size - size - ଆକାର(ସଂରଚନା Header);

		last->size = size;
		last->ମୁକ୍ତ = 0;
		last->next = newblock;

		newblock->ମୁକ୍ତ = 1;
		newblock->next = ଖାଲି;

		ଫେରନ୍ତୁ last;
	}
	ଅନ୍ୟଥା
		ଫେରନ୍ତୁ ଖାଲି;
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
ସଂରଚନା Header *find_free_block(ସଂରଚନା Header **last, size_t size)
{
	log_trace("\nfind free entered");

	ସଂରଚନା Header *current = global_base;

	ଯେତେବେଳେ (current && !(current->ମୁକ୍ତ && current->size >= size))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->size,size,current,*last);
		*last = current;
		current = current->next;
	}

	log_debug("\n After Loop %d %d %x %x",current->size,size,current,*last);

	ଯଦି(current && current->size>=size)
	{
		*last=current;
		ଫେରନ୍ତୁ current;
	}
	ଅନ୍ୟଥା
		ଫେରନ୍ତୁ ଖାଲି;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
ସଂରଚନା Header* request_heap()
{
	ସଂରଚନା Header *block;

	block = m_sbrk(0);

	ଶୂନ୍ୟ *request = m_sbrk(HEAP_SIZE);

	ଯଦି((ଶୂନ୍ୟ*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	ଯଦି (request == (ଶୂନ୍ୟ*) -1) {
		log_error("\nNo space left to allocate memory");
		ଫେରନ୍ତୁ ଖାଲି; // sbrk failed.
	}

	block->size = HEAP_SIZE;
	block->next = ଖାଲି;
	block->ମୁକ୍ତ = 1;

	log_debug("\nBlock Assigned");

	ଫେରନ୍ତୁ block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
ଶୂନ୍ୟ *malloc(size_t size)
{
	ସଂରଚନା Header *block;

	ଯଦି (size <= 0) {
               ଫେରନ୍ତୁ ଖାଲି;
	}

	log_info("\n global_base: %x",global_base);

	ଯଦି(global_base==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		block = request_heap();

		log_debug("\n block=%x",block);

		ଯଦି (!block)
		{
			ଫେରନ୍ତୁ ଖାଲି;
		}
		global_base = block;
	}

	ସଂରଚନା Header *last = global_base;

	block = find_free_block(&last, size);

	ଯଦି(!block)
	{
		log_error("\n No free blocks");
		ଫେରନ୍ତୁ ଖାଲି;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->size,size);

	ଯଦି (block->size>size)
	{
		// Failed to find free block.
		block = allocate_block(last,size);

		ଯଦି (!block)
		{
			ଫେରନ୍ତୁ ଖାଲି;
		}
	}
	ଅନ୍ୟଥା ଯଦି(block->size==size)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->ମୁକ୍ତ = 0;
	}

  ଫେରନ୍ତୁ(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
ସଂରଚନା Header *get_block_ptr(ଶୂନ୍ୟ *ptr)
{
  ଫେରନ୍ତୁ (ସଂରଚନା Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
ଶୂନ୍ୟ ମୁକ୍ତ(ଶୂନ୍ୟ *ptr)
{
	ଯଦି (!ptr)
	{
		log_error("\n Wrong value passed to free");
		ଫେରନ୍ତୁ;
	}

	ସଂରଚନା Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	ଯଦି(block_ptr->ମୁକ୍ତ==0)
		block_ptr->ମୁକ୍ତ = 1;
}
