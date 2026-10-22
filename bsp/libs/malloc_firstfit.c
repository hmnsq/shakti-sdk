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

#ਅਨ੍ਤਰ੍ਭਾਵ<unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ<sys/types.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "defines.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"

ਬਾਹਰੀ ਅੱਖਰ* ਢੇਰ_ਮਾਪ[];
ਅੱਖਰ* ਢੇਰ_ਮਾਪ_2 = (ਅੱਖਰ *)&ਢੇਰ_ਮਾਪ;

//Header block denotes start of the segment
ਬਣਤਰ ਸਿਰਲੇਖ
{
	size_t ਮਾਪ;
	ਪੂਰਨ ਮੁਕਤ;
	ਬਣਤਰ ਸਿਰਲੇਖ* ਅਗਲਾ;
};

ਬਣਤਰ ਸਿਰਲੇਖ* global_ਅਧਾਰ=ਨਿਰਾ;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
ਬਣਤਰ ਸਿਰਲੇਖ* allocate_ਖੰਡ(ਬਣਤਰ ਸਿਰਲੇਖ* ਆਖਰੀ, size_t ਮਾਪ)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	ਜੇ(ਆਖਰੀ->ਮਾਪ > ਮਾਪ)
	{
		ਬਣਤਰ ਸਿਰਲੇਖ* newblock;
		ਖਾਲੀ *p = ਆਖਰੀ;

		p += ਮਾਪ + ਆਕਾਰ(ਬਣਤਰ ਸਿਰਲੇਖ);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->ਮਾਪ = ਆਖਰੀ->ਮਾਪ - ਮਾਪ - ਆਕਾਰ(ਬਣਤਰ ਸਿਰਲੇਖ);

		ਆਖਰੀ->ਮਾਪ = ਮਾਪ;
		ਆਖਰੀ->ਮੁਕਤ = 0;
		ਆਖਰੀ->ਅਗਲਾ = newblock;

		newblock->ਮੁਕਤ = 1;
		newblock->ਅਗਲਾ = ਨਿਰਾ;

		ਵਾਪਸ ਆਖਰੀ;
	}
	ਨਹੀਂਤਾਂ
		ਵਾਪਸ ਨਿਰਾ;
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
ਬਣਤਰ ਸਿਰਲੇਖ *ਲੱਭੋ_free_ਖੰਡ(ਬਣਤਰ ਸਿਰਲੇਖ **ਆਖਰੀ, size_t ਮਾਪ)
{
	log_trace("\nfind free entered");

	ਬਣਤਰ ਸਿਰਲੇਖ *current = global_ਅਧਾਰ;

	ਜਦੋਂ (current && !(current->ਮੁਕਤ && current->ਮਾਪ >= ਮਾਪ))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->ਮਾਪ,ਮਾਪ,current,*ਆਖਰੀ);
		*ਆਖਰੀ = current;
		current = current->ਅਗਲਾ;
	}

	log_debug("\n After Loop %d %d %x %x",current->ਮਾਪ,ਮਾਪ,current,*ਆਖਰੀ);

	ਜੇ(current && current->ਮਾਪ>=ਮਾਪ)
	{
		*ਆਖਰੀ=current;
		ਵਾਪਸ current;
	}
	ਨਹੀਂਤਾਂ
		ਵਾਪਸ ਨਿਰਾ;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
ਬਣਤਰ ਸਿਰਲੇਖ* request_ਢੇਰ()
{
	ਬਣਤਰ ਸਿਰਲੇਖ *ਖੰਡ;

	ਖੰਡ = m_sbrk(0);

	ਖਾਲੀ *request = m_sbrk(ਢੇਰ_ਮਾਪ_2);

	ਜੇ((ਖਾਲੀ*)ਖੰਡ == request); // Not thread safe.
	ਖੰਡ=request;

	log_debug("\nInitial Heap start address =%x",ਖੰਡ);

	ਜੇ (request == (ਖਾਲੀ*) -1) {
		log_error("\nNo space left to allocate memory");
		ਵਾਪਸ ਨਿਰਾ; // sbrk failed.
	}

	ਖੰਡ->ਮਾਪ = ਢੇਰ_ਮਾਪ_2;
	ਖੰਡ->ਅਗਲਾ = ਨਿਰਾ;
	ਖੰਡ->ਮੁਕਤ = 1;

	log_debug("\nBlock Assigned");

	ਵਾਪਸ ਖੰਡ;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
ਖਾਲੀ *ਸਮ੍ਰਿਤੀ_ਦਿਓ(size_t ਮਾਪ)
{
	ਬਣਤਰ ਸਿਰਲੇਖ *ਖੰਡ;

	ਜੇ (ਮਾਪ <= 0) {
               ਵਾਪਸ ਨਿਰਾ;
	}

	log_info("\n global_base: %x",global_ਅਧਾਰ);

	ਜੇ(global_ਅਧਾਰ==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		ਖੰਡ = request_ਢੇਰ();

		log_debug("\n block=%x",ਖੰਡ);

		ਜੇ (!ਖੰਡ)
		{
			ਵਾਪਸ ਨਿਰਾ;
		}
		global_ਅਧਾਰ = ਖੰਡ;
	}

	ਬਣਤਰ ਸਿਰਲੇਖ *ਆਖਰੀ = global_ਅਧਾਰ;

	ਖੰਡ = ਲੱਭੋ_free_ਖੰਡ(&ਆਖਰੀ, ਮਾਪ);

	ਜੇ(!ਖੰਡ)
	{
		log_error("\n No free blocks");
		ਵਾਪਸ ਨਿਰਾ;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",ਖੰਡ,ਖੰਡ->ਮਾਪ,ਮਾਪ);

	ਜੇ (ਖੰਡ->ਮਾਪ>ਮਾਪ)
	{
		// Failed to find free block.
		ਖੰਡ = allocate_ਖੰਡ(ਆਖਰੀ,ਮਾਪ);

		ਜੇ (!ਖੰਡ)
		{
			ਵਾਪਸ ਨਿਰਾ;
		}
	}
	ਨਹੀਂਤਾਂ ਜੇ(ਖੰਡ->ਮਾਪ==ਮਾਪ)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		ਖੰਡ->ਮੁਕਤ = 0;
	}

  ਵਾਪਸ(ਖੰਡ+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
ਬਣਤਰ ਸਿਰਲੇਖ *get_ਖੰਡ_ptr(ਖਾਲੀ *ptr)
{
  ਵਾਪਸ (ਬਣਤਰ ਸਿਰਲੇਖ*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
ਖਾਲੀ ਮੁਕਤ(ਖਾਲੀ *ptr)
{
	ਜੇ (!ptr)
	{
		log_error("\n Wrong value passed to free");
		ਵਾਪਸ;
	}

	ਬਣਤਰ ਸਿਰਲੇਖ* ਖੰਡ_ptr = get_ਖੰਡ_ptr(ptr);

	log_debug("\n %x is freed",ਖੰਡ_ptr);

	ਜੇ(ਖੰਡ_ptr->ਮੁਕਤ==0)
		ਖੰਡ_ptr->ਮੁਕਤ = 1;
}
