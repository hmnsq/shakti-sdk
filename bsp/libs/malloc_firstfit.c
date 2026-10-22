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

#समावेश<unistd.h>
#समावेश<sys/types.h>
#समावेश "platform.h"
#समावेश "defines.h"
#समावेश "log.h"

बाह्य अक्षर* HEAP_आकार[];
अक्षर* HEAP_आकार_2 = (अक्षर *)&HEAP_आकार;

//Header block denotes start of the segment
काष्ठा Header
{
	माप_प्रकार आकार;
	पूर्णांक मुक्त;
	काष्ठा Header* अग्र;
};

काष्ठा Header* global_base=शून्य;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
काष्ठा Header* allocate_block(काष्ठा Header* last, माप_प्रकार आकार)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	अगर(last->आकार > आकार)
	{
		काष्ठा Header* newblock;
		व्योम *p = last;

		p += आकार + माप(काष्ठा Header);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->आकार = last->आकार - आकार - माप(काष्ठा Header);

		last->आकार = आकार;
		last->मुक्त = 0;
		last->अग्र = newblock;

		newblock->मुक्त = 1;
		newblock->अग्र = शून्य;

		वापस last;
	}
	अन्यथा
		वापस शून्य;
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
काष्ठा Header *find_free_block(काष्ठा Header **last, माप_प्रकार आकार)
{
	log_trace("\nfind free entered");

	काष्ठा Header *current = global_base;

	जबतक (current && !(current->मुक्त && current->आकार >= आकार))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->आकार,आकार,current,*last);
		*last = current;
		current = current->अग्र;
	}

	log_debug("\n After Loop %d %d %x %x",current->आकार,आकार,current,*last);

	अगर(current && current->आकार>=आकार)
	{
		*last=current;
		वापस current;
	}
	अन्यथा
		वापस शून्य;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
काष्ठा Header* request_heap()
{
	काष्ठा Header *block;

	block = m_sbrk(0);

	व्योम *request = m_sbrk(HEAP_आकार_2);

	अगर((व्योम*)block == request); // Not thread safe.
	block=request;

	log_debug("\nInitial Heap start address =%x",block);

	अगर (request == (व्योम*) -1) {
		log_error("\nNo space left to allocate memory");
		वापस शून्य; // sbrk failed.
	}

	block->आकार = HEAP_आकार_2;
	block->अग्र = शून्य;
	block->मुक्त = 1;

	log_debug("\nBlock Assigned");

	वापस block;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
व्योम *दो_स्मृति(माप_प्रकार आकार)
{
	काष्ठा Header *block;

	अगर (आकार <= 0) {
               वापस शून्य;
	}

	log_info("\n global_base: %x",global_base);

	अगर(global_base==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		block = request_heap();

		log_debug("\n block=%x",block);

		अगर (!block)
		{
			वापस शून्य;
		}
		global_base = block;
	}

	काष्ठा Header *last = global_base;

	block = find_free_block(&last, आकार);

	अगर(!block)
	{
		log_error("\n No free blocks");
		वापस शून्य;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",block,block->आकार,आकार);

	अगर (block->आकार>आकार)
	{
		// Failed to find free block.
		block = allocate_block(last,आकार);

		अगर (!block)
		{
			वापस शून्य;
		}
	}
	अन्यथा अगर(block->आकार==आकार)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		block->मुक्त = 0;
	}

  वापस(block+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
काष्ठा Header *get_block_ptr(व्योम *ptr)
{
  वापस (काष्ठा Header*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
व्योम मुक्त(व्योम *ptr)
{
	अगर (!ptr)
	{
		log_error("\n Wrong value passed to free");
		वापस;
	}

	काष्ठा Header* block_ptr = get_block_ptr(ptr);

	log_debug("\n %x is freed",block_ptr);

	अगर(block_ptr->मुक्त==0)
		block_ptr->मुक्त = 1;
}
