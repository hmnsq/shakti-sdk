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

#شامل<unistd.h>
#شامل<sys/types.h>
#شامل "platform.h"
#شامل "defines.h"
#شامل "log.h"

خارجی حرف* ڈھیر_سائز[];
حرف* ڈھیر_سائز_2 = (حرف *)&ڈھیر_سائز;

//Header block denotes start of the segment
ساخت سرخی
{
	size_t سائز;
	صحیح آزاد;
	ساخت سرخی* اگلا;
};

ساخت سرخی* global_بنیاد=تہی;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
ساخت سرخی* allocate_بلاک(ساخت سرخی* آخری, size_t سائز)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	اگر(آخری->سائز > سائز)
	{
		ساخت سرخی* newblock;
		خالی *p = آخری;

		p += سائز + حجم(ساخت سرخی);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->سائز = آخری->سائز - سائز - حجم(ساخت سرخی);

		آخری->سائز = سائز;
		آخری->آزاد = 0;
		آخری->اگلا = newblock;

		newblock->آزاد = 1;
		newblock->اگلا = تہی;

		واپس آخری;
	}
	ورنہ
		واپس تہی;
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
ساخت سرخی *ڈھونڈو_free_بلاک(ساخت سرخی **آخری, size_t سائز)
{
	log_trace("\nfind free entered");

	ساخت سرخی *current = global_بنیاد;

	جب (current && !(current->آزاد && current->سائز >= سائز))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->سائز,سائز,current,*آخری);
		*آخری = current;
		current = current->اگلا;
	}

	log_debug("\n After Loop %d %d %x %x",current->سائز,سائز,current,*آخری);

	اگر(current && current->سائز>=سائز)
	{
		*آخری=current;
		واپس current;
	}
	ورنہ
		واپس تہی;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
ساخت سرخی* request_ڈھیر()
{
	ساخت سرخی *بلاک;

	بلاک = m_sbrk(0);

	خالی *request = m_sbrk(ڈھیر_سائز_2);

	اگر((خالی*)بلاک == request); // Not thread safe.
	بلاک=request;

	log_debug("\nInitial Heap start address =%x",بلاک);

	اگر (request == (خالی*) -1) {
		log_error("\nNo space left to allocate memory");
		واپس تہی; // sbrk failed.
	}

	بلاک->سائز = ڈھیر_سائز_2;
	بلاک->اگلا = تہی;
	بلاک->آزاد = 1;

	log_debug("\nBlock Assigned");

	واپس بلاک;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
خالی *حافظہ_دو(size_t سائز)
{
	ساخت سرخی *بلاک;

	اگر (سائز <= 0) {
               واپس تہی;
	}

	log_info("\n global_base: %x",global_بنیاد);

	اگر(global_بنیاد==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		بلاک = request_ڈھیر();

		log_debug("\n block=%x",بلاک);

		اگر (!بلاک)
		{
			واپس تہی;
		}
		global_بنیاد = بلاک;
	}

	ساخت سرخی *آخری = global_بنیاد;

	بلاک = ڈھونڈو_free_بلاک(&آخری, سائز);

	اگر(!بلاک)
	{
		log_error("\n No free blocks");
		واپس تہی;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",بلاک,بلاک->سائز,سائز);

	اگر (بلاک->سائز>سائز)
	{
		// Failed to find free block.
		بلاک = allocate_بلاک(آخری,سائز);

		اگر (!بلاک)
		{
			واپس تہی;
		}
	}
	ورنہ اگر(بلاک->سائز==سائز)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		بلاک->آزاد = 0;
	}

  واپس(بلاک+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
ساخت سرخی *get_بلاک_ptr(خالی *ptr)
{
  واپس (ساخت سرخی*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
خالی آزاد(خالی *ptr)
{
	اگر (!ptr)
	{
		log_error("\n Wrong value passed to free");
		واپس;
	}

	ساخت سرخی* بلاک_ptr = get_بلاک_ptr(ptr);

	log_debug("\n %x is freed",بلاک_ptr);

	اگر(بلاک_ptr->آزاد==0)
		بلاک_ptr->آزاد = 1;
}
