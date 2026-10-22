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

বাহ্যিক অক্ষর* HEAP_আকার[];
অক্ষর* HEAP_আকার_2 = (অক্ষর *)&HEAP_আকার;

//Header block denotes start of the segment
কাঠামো Header
{
	size_t আকার_2;
	পূর্ণসংখ্যা মুক্ত;
	কাঠামো Header* পরবর্তী;
};

কাঠামো Header* global_base=ফাঁকা;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
কাঠামো Header* allocate_block(কাঠামো Header* last, size_t আকার_2)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	যদি(last->আকার_2 > আকার_2)
	{
		কাঠামো Header* newblock;
		শূন্য *p = last;

		p += আকার_2 + আকার(কাঠামো Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->আকার_2 = last->আকার_2 - আকার_2 - আকার(কাঠামো Header);

		last->আকার_2 = আকার_2;
		last->মুক্ত = 0;
		last->পরবর্তী = newblock;

		newblock->মুক্ত = 1;
		newblock->পরবর্তী = ফাঁকা;

		ফেরত last;
	}
	অন্যথা
		ফেরত ফাঁকা;
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
কাঠামো Header *find_free_block(কাঠামো Header **last, size_t আকার_2)
{
	log_trace("\nfind free entered");

	কাঠামো Header *current = global_base;

	যখন (current && !(current->মুক্ত && current->আকার_2 >= আকার_2))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->আকার_2,আকার_2,current,*last);
		*last = current;
		current = current->পরবর্তী;
	}

	log_debug("\n After Loop %d %d %x %x",current->আকার_2,আকার_2,current,*last);

	যদি(current && current->আকার_2>=আকার_2)
	{
		*last=current;
		ফেরত current;
	}
	অন্যথা
		ফেরত ফাঁকা;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
কাঠামো Header* request_heap()
{
	কাঠামো Header *block;

	block = m_sbrk(0);

	শূন্য *request = m_sbrk(HEAP_আকার_2);

	যদি((শূন্য*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	যদি (request == (শূন্য*) -1) {
		log_error("\nNo space left to allocate memory");
		ফেরত ফাঁকা; // sbrk failed.
	}

	block->আকার_2 = HEAP_আকার_2;
	block->পরবর্তী = ফাঁকা;
	block->মুক্ত = 1;

	log_debug("\nBlock Assigned");

	ফেরত block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
শূন্য *malloc(size_t আকার_2)
{
	কাঠামো Header *block;

	যদি (আকার_2 <= 0) {
               ফেরত ফাঁকা;
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
			ফেরত ফাঁকা;
		}
		global_base = block;
	}

	কাঠামো Header *last = global_base;

	block = find_free_block(&last, আকার_2);

	যদি(!block)
	{
		log_error("\n No free blocks");
		ফেরত ফাঁকা;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->আকার_2,আকার_2);

	যদি (block->আকার_2>আকার_2)
	{
		// Failed to find free block.
		block = allocate_block(last,আকার_2);

		যদি (!block)
		{
			ফেরত ফাঁকা;
		}
	}
	অন্যথা যদি(block->আকার_2==আকার_2)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->মুক্ত = 0;
	}

  ফেরত(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
কাঠামো Header *get_block_ptr(শূন্য *ptr)
{
  ফেরত (কাঠামো Header*)ptr - 1;
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
		ফেরত;
	}

	কাঠামো Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	যদি(block_ptr->মুক্ত==0)
		block_ptr->মুক্ত = 1;
}
