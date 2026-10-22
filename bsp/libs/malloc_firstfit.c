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

#अन्तर्भाव<unistd.h>
#अन्तर्भाव<sys/types.h>
#अन्तर्भाव "platform.h"
#अन्तर्भाव "defines.h"
#अन्तर्भाव "log.h"

बाह्य वर्ण* HEAP_आकार[];
वर्ण* HEAP_आकार_2 = (वर्ण *)&HEAP_आकार;

//Header block denotes start of the segment
संरचना शीर्षकम्
{
	size_t आकार;
	पूर्णाङ्क मुक्त;
	संरचना शीर्षकम्* अग्र;
};

संरचना शीर्षकम्* global_आधारः=रिक्त;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
संरचना शीर्षकम्* allocate_खण्डम्(संरचना शीर्षकम्* चरमः, size_t आकार)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	यदि(चरमः->आकार > आकार)
	{
		संरचना शीर्षकम्* newblock;
		शून्य *p = चरमः;

		p += आकार + परिमाण(संरचना शीर्षकम्);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->आकार = चरमः->आकार - आकार - परिमाण(संरचना शीर्षकम्);

		चरमः->आकार = आकार;
		चरमः->मुक्त = 0;
		चरमः->अग्र = newblock;

		newblock->मुक्त = 1;
		newblock->अग्र = रिक्त;

		प्रत्यागम चरमः;
	}
	अन्यथा
		प्रत्यागम रिक्त;
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
संरचना शीर्षकम् *find_free_खण्डम्(संरचना शीर्षकम् **चरमः, size_t आकार)
{
	log_trace("\nfind free entered");

	संरचना शीर्षकम् *current = global_आधारः;

	यावत् (current && !(current->मुक्त && current->आकार >= आकार))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->आकार,आकार,current,*चरमः);
		*चरमः = current;
		current = current->अग्र;
	}

	log_debug("\n After Loop %d %d %x %x",current->आकार,आकार,current,*चरमः);

	यदि(current && current->आकार>=आकार)
	{
		*चरमः=current;
		प्रत्यागम current;
	}
	अन्यथा
		प्रत्यागम रिक्त;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
संरचना शीर्षकम्* request_heap()
{
	संरचना शीर्षकम् *खण्डम्;

	खण्डम् = m_sbrk(0);

	शून्य *request = m_sbrk(HEAP_आकार_2);

	यदि((शून्य*)खण्डम् == request); // Not thread safe.
	खण्डम्=request;

	log_debug("\nInitial Heap start address =%x",खण्डम्);

	यदि (request == (शून्य*) -1) {
		log_error("\nNo space left to allocate memory");
		प्रत्यागम रिक्त; // sbrk failed.
	}

	खण्डम्->आकार = HEAP_आकार_2;
	खण्डम्->अग्र = रिक्त;
	खण्डम्->मुक्त = 1;

	log_debug("\nBlock Assigned");

	प्रत्यागम खण्डम्;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
शून्य *स्मृतिं_देहि(size_t आकार)
{
	संरचना शीर्षकम् *खण्डम्;

	यदि (आकार <= 0) {
               प्रत्यागम रिक्त;
	}

	log_info("\n global_base: %x",global_आधारः);

	यदि(global_आधारः==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		खण्डम् = request_heap();

		log_debug("\n block=%x",खण्डम्);

		यदि (!खण्डम्)
		{
			प्रत्यागम रिक्त;
		}
		global_आधारः = खण्डम्;
	}

	संरचना शीर्षकम् *चरमः = global_आधारः;

	खण्डम् = find_free_खण्डम्(&चरमः, आकार);

	यदि(!खण्डम्)
	{
		log_error("\n No free blocks");
		प्रत्यागम रिक्त;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",खण्डम्,खण्डम्->आकार,आकार);

	यदि (खण्डम्->आकार>आकार)
	{
		// Failed to find free block.
		खण्डम् = allocate_खण्डम्(चरमः,आकार);

		यदि (!खण्डम्)
		{
			प्रत्यागम रिक्त;
		}
	}
	अन्यथा यदि(खण्डम्->आकार==आकार)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		खण्डम्->मुक्त = 0;
	}

  प्रत्यागम(खण्डम्+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
संरचना शीर्षकम् *get_खण्डम्_ptr(शून्य *ptr)
{
  प्रत्यागम (संरचना शीर्षकम्*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
शून्य मुक्त(शून्य *ptr)
{
	यदि (!ptr)
	{
		log_error("\n Wrong value passed to free");
		प्रत्यागम;
	}

	संरचना शीर्षकम्* खण्डम्_ptr = get_खण्डम्_ptr(ptr);

	log_debug("\n %x is freed",खण्डम्_ptr);

	यदि(खण्डम्_ptr->मुक्त==0)
		खण्डम्_ptr->मुक्त = 1;
}
