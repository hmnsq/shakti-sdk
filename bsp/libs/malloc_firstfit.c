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

خارجي حرف* ډېرۍ_اندازه[];
حرف* ډېرۍ_اندازه_2 = (حرف *)&ډېرۍ_اندازه;

//Header block denotes start of the segment
بنية سرلیک
{
	size_t اندازه;
	صحيح حرر;
	بنية سرلیک* بل;
};

بنية سرلیک* global_بنسټ=عدم;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
بنية سرلیک* allocate_بلاک(بنية سرلیک* وروستی, size_t اندازه)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	إذا(وروستی->اندازه > اندازه)
	{
		بنية سرلیک* newblock;
		فراغ *p = وروستی;

		p += اندازه + حجم(بنية سرلیک);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->اندازه = وروستی->اندازه - اندازه - حجم(بنية سرلیک);

		وروستی->اندازه = اندازه;
		وروستی->حرر = 0;
		وروستی->بل = newblock;

		newblock->حرر = 1;
		newblock->بل = عدم;

		أرجع وروستی;
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
بنية سرلیک *پیدا_کړه_free_بلاک(بنية سرلیک **وروستی, size_t اندازه)
{
	log_trace("\nfind free entered");

	بنية سرلیک *current = global_بنسټ;

	طالما (current && !(current->حرر && current->اندازه >= اندازه))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->اندازه,اندازه,current,*وروستی);
		*وروستی = current;
		current = current->بل;
	}

	log_debug("\n After Loop %d %d %x %x",current->اندازه,اندازه,current,*وروستی);

	إذا(current && current->اندازه>=اندازه)
	{
		*وروستی=current;
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
بنية سرلیک* request_ډېرۍ()
{
	بنية سرلیک *بلاک;

	بلاک = m_sbrk(0);

	فراغ *request = m_sbrk(ډېرۍ_اندازه_2);

	إذا((فراغ*)بلاک == request); // Not thread safe.
	بلاک=request;

	log_debug("\nInitial Heap start address =%x",بلاک);

	إذا (request == (فراغ*) -1) {
		log_error("\nNo space left to allocate memory");
		أرجع عدم; // sbrk failed.
	}

	بلاک->اندازه = ډېرۍ_اندازه_2;
	بلاک->بل = عدم;
	بلاک->حرر = 1;

	log_debug("\nBlock Assigned");

	أرجع بلاک;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
فراغ *حافظه_ورکړه(size_t اندازه)
{
	بنية سرلیک *بلاک;

	إذا (اندازه <= 0) {
               أرجع عدم;
	}

	log_info("\n global_base: %x",global_بنسټ);

	إذا(global_بنسټ==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		بلاک = request_ډېرۍ();

		log_debug("\n block=%x",بلاک);

		إذا (!بلاک)
		{
			أرجع عدم;
		}
		global_بنسټ = بلاک;
	}

	بنية سرلیک *وروستی = global_بنسټ;

	بلاک = پیدا_کړه_free_بلاک(&وروستی, اندازه);

	إذا(!بلاک)
	{
		log_error("\n No free blocks");
		أرجع عدم;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",بلاک,بلاک->اندازه,اندازه);

	إذا (بلاک->اندازه>اندازه)
	{
		// Failed to find free block.
		بلاک = allocate_بلاک(وروستی,اندازه);

		إذا (!بلاک)
		{
			أرجع عدم;
		}
	}
	وإلا إذا(بلاک->اندازه==اندازه)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		بلاک->حرر = 0;
	}

  أرجع(بلاک+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
بنية سرلیک *get_بلاک_ptr(فراغ *ptr)
{
  أرجع (بنية سرلیک*)ptr - 1;
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

	بنية سرلیک* بلاک_ptr = get_بلاک_ptr(ptr);

	log_debug("\n %x is freed",بلاک_ptr);

	إذا(بلاک_ptr->حرر==0)
		بلاک_ptr->حرر = 1;
}
