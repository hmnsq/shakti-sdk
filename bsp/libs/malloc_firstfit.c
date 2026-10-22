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

#అన్తర్భావ<unistd.h>
#అన్తర్భావ<sys/types.h>
#అన్తర్భావ "platform.h"
#అన్తర్భావ "defines.h"
#అన్తర్భావ "log.h"

బాహ్య అక్షరం* కుప్ప_కొలత[];
అక్షరం* కుప్ప_కొలత_2 = (అక్షరం *)&కుప్ప_కొలత;

//Header block denotes start of the segment
నిర్మాణం శీర్షిక
{
	size_t కొలత;
	పూర్ణాంకం విడుదల;
	నిర్మాణం శీర్షిక* తదుపరి;
};

నిర్మాణం శీర్షిక* global_పునాది=ఖాళీ;

/** @fn  struct Header* allocate_block(struct Header* last, size_t size)
 * @brief it allocates a block of given size 
 * @detail it allocates a block of the given size after receiving the parameter of the last allocated block
 * @param struct Header* last -  pointer to the last allocated memory or the end of the heap
 * @param size_t size - specifes the size of the block to be allocated
 * @return returns a pointer to the newly allocated block
 *         returns null if mmemory allocated or block allocation fails
 */
నిర్మాణం శీర్షిక* allocate_ఖండం(నిర్మాణం శీర్షిక* చివరి, size_t కొలత)
{
	uintptr_t x=0;

	log_trace("\nFunction allocate_block entered");

	ఒకవేళ(చివరి->కొలత > కొలత)
	{
		నిర్మాణం శీర్షిక* newblock;
		శూన్య *p = చివరి;

		p += కొలత + పరిమాణం(నిర్మాణం శీర్షిక);
		x = p;

		x = ((( x) + ((REGSIZE) - 1)) & ~((REGSIZE) - 1));

		p = x;

		newblock = p;

		newblock->కొలత = చివరి->కొలత - కొలత - పరిమాణం(నిర్మాణం శీర్షిక);

		చివరి->కొలత = కొలత;
		చివరి->విడుదల = 0;
		చివరి->తదుపరి = newblock;

		newblock->విడుదల = 1;
		newblock->తదుపరి = ఖాళీ;

		తిరిగి చివరి;
	}
	లేకపోతే
		తిరిగి ఖాళీ;
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
నిర్మాణం శీర్షిక *కనుగొను_free_ఖండం(నిర్మాణం శీర్షిక **చివరి, size_t కొలత)
{
	log_trace("\nfind free entered");

	నిర్మాణం శీర్షిక *current = global_పునాది;

	అయితే (current && !(current->విడుదల && current->కొలత >= కొలత))
	{

		log_debug("\n Inside Loop %d %d %x %x",current->కొలత,కొలత,current,*చివరి);
		*చివరి = current;
		current = current->తదుపరి;
	}

	log_debug("\n After Loop %d %d %x %x",current->కొలత,కొలత,current,*చివరి);

	ఒకవేళ(current && current->కొలత>=కొలత)
	{
		*చివరి=current;
		తిరిగి current;
	}
	లేకపోతే
		తిరిగి ఖాళీ;

	log_trace("\nfind free exited");
}

//Creating a new block
/** @fn struct Header* request_heap()
 * @brief  requests memory from the heap
 * @detail  this function requests memory from the heap using the brk function
 * @return returns a pointer to the allocated heap
 *         returns NULL if heap is unable to be allocated
 */
నిర్మాణం శీర్షిక* request_కుప్ప()
{
	నిర్మాణం శీర్షిక *ఖండం;

	ఖండం = m_sbrk(0);

	శూన్య *request = m_sbrk(కుప్ప_కొలత_2);

	ఒకవేళ((శూన్య*)ఖండం == request); // Not thread safe.
	ఖండం=request;

	log_debug("\nInitial Heap start address =%x",ఖండం);

	ఒకవేళ (request == (శూన్య*) -1) {
		log_error("\nNo space left to allocate memory");
		తిరిగి ఖాళీ; // sbrk failed.
	}

	ఖండం->కొలత = కుప్ప_కొలత_2;
	ఖండం->తదుపరి = ఖాళీ;
	ఖండం->విడుదల = 1;

	log_debug("\nBlock Assigned");

	తిరిగి ఖండం;
}

//malloc function to allocate space
/** @fn  void *malloc(size_t size)
 * @brief  this function is used to dynamically allocate memory
 * @detail  when this function is called memory is allocated in the heap during runtime
 * @param size_t size - size of the block to be allocated
 * @return  returns a pointer to the assigned block
 *          returns NULL if allocation fails
 */
శూన్య *జ్ఞాపకం_ఇవ్వు(size_t కొలత)
{
	నిర్మాణం శీర్షిక *ఖండం;

	ఒకవేళ (కొలత <= 0) {
               తిరిగి ఖాళీ;
	}

	log_info("\n global_base: %x",global_పునాది);

	ఒకవేళ(global_పునాది==0x00000000)
	{
		// First call. global_base is empty
		log_debug("\n Requesting block");

		ఖండం = request_కుప్ప();

		log_debug("\n block=%x",ఖండం);

		ఒకవేళ (!ఖండం)
		{
			తిరిగి ఖాళీ;
		}
		global_పునాది = ఖండం;
	}

	నిర్మాణం శీర్షిక *చివరి = global_పునాది;

	ఖండం = కనుగొను_free_ఖండం(&చివరి, కొలత);

	ఒకవేళ(!ఖండం)
	{
		log_error("\n No free blocks");
		తిరిగి ఖాళీ;
	}

	log_debug("\nBlock = %x Block Size = %d Size = %d",ఖండం,ఖండం->కొలత,కొలత);

	ఒకవేళ (ఖండం->కొలత>కొలత)
	{
		// Failed to find free block.
		ఖండం = allocate_ఖండం(చివరి,కొలత);

		ఒకవేళ (!ఖండం)
		{
			తిరిగి ఖాళీ;
		}
	}
	లేకపోతే ఒకవేళ(ఖండం->కొలత==కొలత)
	{
		// Found free block
		log_debug("\nFound free block of same size");
		ఖండం->విడుదల = 0;
	}

  తిరిగి(ఖండం+1);
}

/** @fn  struct Header *get_block_ptr(void *ptr)
 * @brief function to get block pointer
 * @detail  function returns the pointer to the block
 * @param void* ptr - pointer to the block
 * @return returns pointer to the block
 */
నిర్మాణం శీర్షిక *get_ఖండం_ptr(శూన్య *ptr)
{
  తిరిగి (నిర్మాణం శీర్షిక*)ptr - 1;
}

//free to free the memory allocated by malloc
/** @fn  void free(void *ptr)
 * @brief frees the memory assigned by malloc
 * @detail  frees the memory assigned by malloc and when freed this memory is added back to the list to be reused
 * @param void *ptr - pointer to the memory assigned by malloc
 */
శూన్య విడుదల(శూన్య *ptr)
{
	ఒకవేళ (!ptr)
	{
		log_error("\n Wrong value passed to free");
		తిరిగి;
	}

	నిర్మాణం శీర్షిక* ఖండం_ptr = get_ఖండం_ptr(ptr);

	log_debug("\n %x is freed",ఖండం_ptr);

	ఒకవేళ(ఖండం_ptr->విడుదల==0)
		ఖండం_ptr->విడుదల = 1;
}
