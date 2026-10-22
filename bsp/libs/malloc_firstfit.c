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

خارجي حرف* ڈھیر_ناپ[];
حرف* ڈھیر_ناپ_2 = (حرف *)&ڈھیر_ناپ;

//Header block denotes start of the segment
بنية سرخی
{
	size_t ناپ;
	صحيح حرر;
	بنية سرخی* اگلا;
};

بنية سرخی* global_ادھار=عدم;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
بنية سرخی* allocate_بلاک(بنية سرخی* آخری, size_t ناپ)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	إذا(آخری->ناپ > ناپ)
	{
		بنية سرخی* newblock;
		فراغ *p = آخری;

		p += ناپ + حجم(بنية سرخی);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->ناپ = آخری->ناپ - ناپ - حجم(بنية سرخی);

		آخری->ناپ = ناپ;
		آخری->حرر = 0;
		آخری->اگلا = newblock;

		newblock->حرر = 1;
		newblock->اگلا = عدم;

		أرجع آخری;
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
بنية سرخی *لبھو_free_بلاک(بنية سرخی **آخری, size_t ناپ)
{
	log_trace("\nfind free entered");

	بنية سرخی *current = global_ادھار;

	طالما (current && !(current->حرر && current->ناپ >= ناپ))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->ناپ,ناپ,current,*آخری);
		*آخری = current;
		current = current->اگلا;
	}

	log_debug("\n After Loop %d %d %x %x",current->ناپ,ناپ,current,*آخری);

	إذا(current && current->ناپ>=ناپ)
	{
		*آخری=current;
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
بنية سرخی* request_ڈھیر()
{
	بنية سرخی *بلاک;

	بلاک = m_sbrk(0);

	فراغ *request = m_sbrk(ڈھیر_ناپ_2);

	إذا((فراغ*)بلاک == request); // Not thread safe.
	بلاک=request;

	log_debug("\nInitial Heap start address =%x",بلاک);

	إذا (request == (فراغ*) -1) {
		log_error("\nNo space left to allocate memory");
		أرجع عدم; // sbrk failed.
	}

	بلاک->ناپ = ڈھیر_ناپ_2;
	بلاک->اگلا = عدم;
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
فراغ *حافظہ_دیو(size_t ناپ)
{
	بنية سرخی *بلاک;

	إذا (ناپ <= 0) {
               أرجع عدم;
	}

	log_info("\n global_base: %x",global_ادھار);

	إذا(global_ادھار==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		بلاک = request_ڈھیر();

		log_debug("\n block=%x",بلاک);

		إذا (!بلاک)
		{
			أرجع عدم;
		}
		global_ادھار = بلاک;
	}

	بنية سرخی *آخری = global_ادھار;

	بلاک = لبھو_free_بلاک(&آخری, ناپ);

	إذا(!بلاک)
	{
		log_error("\n No free blocks");
		أرجع عدم;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",بلاک,بلاک->ناپ,ناپ);

	إذا (بلاک->ناپ>ناپ)
	{
		// Failed to find free block.
		بلاک = allocate_بلاک(آخری,ناپ);

		إذا (!بلاک)
		{
			أرجع عدم;
		}
	}
	وإلا إذا(بلاک->ناپ==ناپ)
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
بنية سرخی *get_بلاک_ptr(فراغ *ptr)
{
  أرجع (بنية سرخی*)ptr - 1;
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

	بنية سرخی* بلاک_ptr = get_بلاک_ptr(ptr);

	log_debug("\n %x is freed",بلاک_ptr);

	إذا(بلاک_ptr->حرر==0)
		بلاک_ptr->حرر = 1;
}
