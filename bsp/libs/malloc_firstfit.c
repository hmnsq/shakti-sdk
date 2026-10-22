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

خارجي حرف* ڍير_سائيز[];
حرف* ڍير_سائيز_2 = (حرف *)&ڍير_سائيز;

//Header block denotes start of the segment
بنية سرو
{
	size_t سائيز;
	صحيح حرر;
	بنية سرو* ايندڙ;
};

بنية سرو* global_بنياد=عدم;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
بنية سرو* allocate_بلاڪ(بنية سرو* آخري, size_t سائيز)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	إذا(آخري->سائيز > سائيز)
	{
		بنية سرو* newblock;
		فراغ *p = آخري;

		p += سائيز + حجم(بنية سرو);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->سائيز = آخري->سائيز - سائيز - حجم(بنية سرو);

		آخري->سائيز = سائيز;
		آخري->حرر = 0;
		آخري->ايندڙ = newblock;

		newblock->حرر = 1;
		newblock->ايندڙ = عدم;

		أرجع آخري;
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
بنية سرو *ڳوليو_free_بلاڪ(بنية سرو **آخري, size_t سائيز)
{
	log_trace("\nfind free entered");

	بنية سرو *current = global_بنياد;

	طالما (current && !(current->حرر && current->سائيز >= سائيز))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->سائيز,سائيز,current,*آخري);
		*آخري = current;
		current = current->ايندڙ;
	}

	log_debug("\n After Loop %d %d %x %x",current->سائيز,سائيز,current,*آخري);

	إذا(current && current->سائيز>=سائيز)
	{
		*آخري=current;
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
بنية سرو* request_ڍير()
{
	بنية سرو *بلاڪ;

	بلاڪ = m_sbrk(0);

	فراغ *request = m_sbrk(ڍير_سائيز_2);

	إذا((فراغ*)بلاڪ == request); // Not thread safe.
	بلاڪ=request;

	log_debug("\nInitial Heap start address =%x",بلاڪ);

	إذا (request == (فراغ*) -1) {
		log_error("\nNo space left to allocate memory");
		أرجع عدم; // sbrk failed.
	}

	بلاڪ->سائيز = ڍير_سائيز_2;
	بلاڪ->ايندڙ = عدم;
	بلاڪ->حرر = 1;

	log_debug("\nBlock Assigned");

	أرجع بلاڪ;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
فراغ *يادگيري_ڏيو(size_t سائيز)
{
	بنية سرو *بلاڪ;

	إذا (سائيز <= 0) {
               أرجع عدم;
	}

	log_info("\n global_base: %x",global_بنياد);

	إذا(global_بنياد==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		بلاڪ = request_ڍير();

		log_debug("\n block=%x",بلاڪ);

		إذا (!بلاڪ)
		{
			أرجع عدم;
		}
		global_بنياد = بلاڪ;
	}

	بنية سرو *آخري = global_بنياد;

	بلاڪ = ڳوليو_free_بلاڪ(&آخري, سائيز);

	إذا(!بلاڪ)
	{
		log_error("\n No free blocks");
		أرجع عدم;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",بلاڪ,بلاڪ->سائيز,سائيز);

	إذا (بلاڪ->سائيز>سائيز)
	{
		// Failed to find free block.
		بلاڪ = allocate_بلاڪ(آخري,سائيز);

		إذا (!بلاڪ)
		{
			أرجع عدم;
		}
	}
	وإلا إذا(بلاڪ->سائيز==سائيز)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		بلاڪ->حرر = 0;
	}

  أرجع(بلاڪ+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
بنية سرو *get_بلاڪ_ptr(فراغ *ptr)
{
  أرجع (بنية سرو*)ptr - 1;
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

	بنية سرو* بلاڪ_ptr = get_بلاڪ_ptr(ptr);

	log_debug("\n %x is freed",بلاڪ_ptr);

	إذا(بلاڪ_ptr->حرر==0)
		بلاڪ_ptr->حرر = 1;
}
