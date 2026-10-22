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

ಬಾಹ್ಯ ಅಕ್ಷರ* ರಾಶಿ_ಗಾತ್ರ[];
ಅಕ್ಷರ* ರಾಶಿ_ಗಾತ್ರ_2 = (ಅಕ್ಷರ *)&ರಾಶಿ_ಗಾತ್ರ;

//Header block denotes start of the segment
ರಚನೆ ಶೀರ್ಷಿಕೆ
{
	size_t ಗಾತ್ರ_2;
	ಪೂರ್ಣಾಂಕ ಬಿಡುಗಡೆ;
	ರಚನೆ ಶೀರ್ಷಿಕೆ* ಮುಂದಿನ;
};

ರಚನೆ ಶೀರ್ಷಿಕೆ* global_ತಳ=ಖಾಲಿ;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
ರಚನೆ ಶೀರ್ಷಿಕೆ* allocate_ಖಂಡ(ರಚನೆ ಶೀರ್ಷಿಕೆ* ಕೊನೆಯ, size_t ಗಾತ್ರ_2)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	ಆದರೆ(ಕೊನೆಯ->ಗಾತ್ರ_2 > ಗಾತ್ರ_2)
	{
		ರಚನೆ ಶೀರ್ಷಿಕೆ* newblock;
		ಶೂನ್ಯ *p = ಕೊನೆಯ;

		p += ಗಾತ್ರ_2 + ಗಾತ್ರ(ರಚನೆ ಶೀರ್ಷಿಕೆ);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->ಗಾತ್ರ_2 = ಕೊನೆಯ->ಗಾತ್ರ_2 - ಗಾತ್ರ_2 - ಗಾತ್ರ(ರಚನೆ ಶೀರ್ಷಿಕೆ);

		ಕೊನೆಯ->ಗಾತ್ರ_2 = ಗಾತ್ರ_2;
		ಕೊನೆಯ->ಬಿಡುಗಡೆ = 0;
		ಕೊನೆಯ->ಮುಂದಿನ = newblock;

		newblock->ಬಿಡುಗಡೆ = 1;
		newblock->ಮುಂದಿನ = ಖಾಲಿ;

		ಹಿಂತಿರುಗಿ ಕೊನೆಯ;
	}
	ಇಲ್ಲದಿದ್ದರೆ
		ಹಿಂತಿರುಗಿ ಖಾಲಿ;
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
ರಚನೆ ಶೀರ್ಷಿಕೆ *ಕಂಡುಹಿಡಿ_free_ಖಂಡ(ರಚನೆ ಶೀರ್ಷಿಕೆ **ಕೊನೆಯ, size_t ಗಾತ್ರ_2)
{
	log_trace("\nfind free entered");

	ರಚನೆ ಶೀರ್ಷಿಕೆ *current = global_ತಳ;

	ಆಗ (current && !(current->ಬಿಡುಗಡೆ && current->ಗಾತ್ರ_2 >= ಗಾತ್ರ_2))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->ಗಾತ್ರ_2,ಗಾತ್ರ_2,current,*ಕೊನೆಯ);
		*ಕೊನೆಯ = current;
		current = current->ಮುಂದಿನ;
	}

	log_debug("\n After Loop %d %d %x %x",current->ಗಾತ್ರ_2,ಗಾತ್ರ_2,current,*ಕೊನೆಯ);

	ಆದರೆ(current && current->ಗಾತ್ರ_2>=ಗಾತ್ರ_2)
	{
		*ಕೊನೆಯ=current;
		ಹಿಂತಿರುಗಿ current;
	}
	ಇಲ್ಲದಿದ್ದರೆ
		ಹಿಂತಿರುಗಿ ಖಾಲಿ;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
ರಚನೆ ಶೀರ್ಷಿಕೆ* request_ರಾಶಿ()
{
	ರಚನೆ ಶೀರ್ಷಿಕೆ *ಖಂಡ;

	ಖಂಡ = m_sbrk(0);

	ಶೂನ್ಯ *request = m_sbrk(ರಾಶಿ_ಗಾತ್ರ_2);

	ಆದರೆ((ಶೂನ್ಯ*)ಖಂಡ == request); // Not thread safe.
	ಖಂಡ=request;

	log_debug("\nInitial Heap start address =%x",ಖಂಡ);

	ಆದರೆ (request == (ಶೂನ್ಯ*) -1) {
		log_error("\nNo space left to allocate memory");
		ಹಿಂತಿರುಗಿ ಖಾಲಿ; // sbrk failed.
	}

	ಖಂಡ->ಗಾತ್ರ_2 = ರಾಶಿ_ಗಾತ್ರ_2;
	ಖಂಡ->ಮುಂದಿನ = ಖಾಲಿ;
	ಖಂಡ->ಬಿಡುಗಡೆ = 1;

	log_debug("\nBlock Assigned");

	ಹಿಂತಿರುಗಿ ಖಂಡ;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
ಶೂನ್ಯ *ಸ್ಮರಣೆ_ಕೊಡು(size_t ಗಾತ್ರ_2)
{
	ರಚನೆ ಶೀರ್ಷಿಕೆ *ಖಂಡ;

	ಆದರೆ (ಗಾತ್ರ_2 <= 0) {
               ಹಿಂತಿರುಗಿ ಖಾಲಿ;
	}

	log_info("\n global_base: %x",global_ತಳ);

	ಆದರೆ(global_ತಳ==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		ಖಂಡ = request_ರಾಶಿ();

		log_debug("\n block=%x",ಖಂಡ);

		ಆದರೆ (!ಖಂಡ)
		{
			ಹಿಂತಿರುಗಿ ಖಾಲಿ;
		}
		global_ತಳ = ಖಂಡ;
	}

	ರಚನೆ ಶೀರ್ಷಿಕೆ *ಕೊನೆಯ = global_ತಳ;

	ಖಂಡ = ಕಂಡುಹಿಡಿ_free_ಖಂಡ(&ಕೊನೆಯ, ಗಾತ್ರ_2);

	ಆದರೆ(!ಖಂಡ)
	{
		log_error("\n No free blocks");
		ಹಿಂತಿರುಗಿ ಖಾಲಿ;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",ಖಂಡ,ಖಂಡ->ಗಾತ್ರ_2,ಗಾತ್ರ_2);

	ಆದರೆ (ಖಂಡ->ಗಾತ್ರ_2>ಗಾತ್ರ_2)
	{
		// Failed to find free block.
		ಖಂಡ = allocate_ಖಂಡ(ಕೊನೆಯ,ಗಾತ್ರ_2);

		ಆದರೆ (!ಖಂಡ)
		{
			ಹಿಂತಿರುಗಿ ಖಾಲಿ;
		}
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(ಖಂಡ->ಗಾತ್ರ_2==ಗಾತ್ರ_2)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		ಖಂಡ->ಬಿಡುಗಡೆ = 0;
	}

  ಹಿಂತಿರುಗಿ(ಖಂಡ+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
ರಚನೆ ಶೀರ್ಷಿಕೆ *get_ಖಂಡ_ptr(ಶೂನ್ಯ *ptr)
{
  ಹಿಂತಿರುಗಿ (ರಚನೆ ಶೀರ್ಷಿಕೆ*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
ಶೂನ್ಯ ಬಿಡುಗಡೆ(ಶೂನ್ಯ *ptr)
{
	ಆದರೆ (!ptr)
	{
		log_error("\n Wrong value passed to free");
		ಹಿಂತಿರುಗಿ;
	}

	ರಚನೆ ಶೀರ್ಷಿಕೆ* ಖಂಡ_ptr = get_ಖಂಡ_ptr(ptr);

	log_debug("\n %x is freed",ಖಂಡ_ptr);

	ಆದರೆ(ಖಂಡ_ptr->ಬಿಡುಗಡೆ==0)
		ಖಂಡ_ptr->ಬಿಡುಗಡೆ = 1;
}
