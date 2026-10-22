/***************************************************************************
 * Project                   : shakti devt board
 * Name of the file	     : linkedlist.c
 * Brief Description of file : Singly linked list creation and deletion with malloc.
 * Name of Author    	     : Akshaya B
 * Email ID                  : akshayabarat@gmail.com

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

#অন্তর্ভাব "uart.h"
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>

কাঠামো গ্রন্থি {
	পূর্ণসংখ্যা অঙ্ক;
	কাঠামো গ্রন্থি *nptr;
}*শীর্ষ;

শূন্য create_list(পূর্ণসংখ্যা n);
শূন্য display_list();
শূন্য delete_গ্রন্থি(পূর্ণসংখ্যা position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
শূন্য প্রধান()
{
	পূর্ণসংখ্যা n,position,m;
	অক্ষর t[15];
	printf("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = atoi(t);

	create_list(n);

	printf("\n\n\nData entered in the list\n");

	display_list();

	printf("\n\n Deletion\n");
	printf("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = atoi(t);

	delete_গ্রন্থি(position);

	printf("\nLinked list after deletion\n");
	display_list();

	যখন(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
শূন্য create_list(পূর্ণসংখ্যা n)
{
	কাঠামো গ্রন্থি *গ্রন্থি, *tmp;
	পূর্ণসংখ্যা তথ্য_2,m;
	অক্ষর t[12];

	শীর্ষ = (কাঠামো গ্রন্থি*)malloc(আকার(কাঠামো গ্রন্থি));

	যদি(শীর্ষ == ফাঁকা)
	{
		printf("\n Memory cannot be allocated");
	}
	অন্যথা
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		তথ্য_2 = atoi(t);

		শীর্ষ->অঙ্ক = তথ্য_2;
		শীর্ষ->nptr = ফাঁকা;
		tmp = শীর্ষ;

		জন্য(পূর্ণসংখ্যা i = 2;i <= n; i++)
		{
			গ্রন্থি = (কাঠামো গ্রন্থি*)malloc(আকার(কাঠামো গ্রন্থি));

			যদি(গ্রন্থি == ফাঁকা)
			{
				printf("\n Memory Cannot be allocated");
			}
			অন্যথা 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				তথ্য_2 = atoi(t);
				গ্রন্থি->অঙ্ক = তথ্য_2;
				গ্রন্থি->nptr = ফাঁকা;

				tmp->nptr = গ্রন্থি;
				tmp = tmp->nptr;
			}
		}
	}
}

/** @fn void display_list() 
 * @brief Displays the linked list
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
শূন্য display_list()
{
	পূর্ণসংখ্যা i = 0;
	কাঠামো গ্রন্থি *tmp;

	যদি(শীর্ষ == ফাঁকা)
	{
		printf(" List is empty.");
	}
	অন্যথা
	{
		tmp = শীর্ষ;
		যখন(tmp != ফাঁকা) 
		{
			printf(" Node%d = %d",i,tmp->অঙ্ক);
			printf("->");
			tmp = tmp->nptr;
			i++;
		}
	}
}

/** @fn void delete_node(int position)
 * @brief Deletes the node entered by the user.
 * @param[in] int
 * @param[Out] No output parameter

 */
শূন্য delete_গ্রন্থি(পূর্ণসংখ্যা position)
{
	কাঠামো গ্রন্থি *অস্থায়ী;

	যদি(শীর্ষ == ফাঁকা)
	{
		printf(" List is empty.");
	}
	অন্যথা 
	{
		অস্থায়ী = শীর্ষ;

		যদি (position == 0)//Delete head node
		{
			শীর্ষ = অস্থায়ী->nptr;
			মুক্ত(অস্থায়ী);
			ফেরত;
		}

		জন্য (পূর্ণসংখ্যা i = 0; অস্থায়ী != ফাঁকা && i < position-1; i++)//store previous of to be deleted node
		{
			অস্থায়ী = অস্থায়ী->nptr;
		}

		যদি (অস্থায়ী == ফাঁকা || অস্থায়ী->nptr == ফাঁকা)
			ফেরত;

		//delete node at pos (next of position-1)
		কাঠামো গ্রন্থি *nptr = অস্থায়ী->nptr->nptr;

		মুক্ত(অস্থায়ী->nptr);
		অস্থায়ী->nptr = nptr; 
	}
}
