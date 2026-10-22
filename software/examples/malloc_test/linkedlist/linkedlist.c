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

#অন্তর্ভাৱ "uart.h"
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdlib.h>

সংরচনা গ্ৰন্থি {
	পূর্ণাঙ্ক অঙ্ক;
	সংরচনা গ্ৰন্থি *nptr;
}*head;

শূন্য create_list(পূর্ণাঙ্ক n);
শূন্য display_list();
শূন্য delete_গ্ৰন্থি(পূর্ণাঙ্ক position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
শূন্য main()
{
	পূর্ণাঙ্ক n,position,m;
	ৱর্ণ t[15];
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

	delete_গ্ৰন্থি(position);

	printf("\nLinked list after deletion\n");
	display_list();

	যেতিয়ালৈ(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
শূন্য create_list(পূর্ণাঙ্ক n)
{
	সংরচনা গ্ৰন্থি *গ্ৰন্থি, *tmp;
	পূর্ণাঙ্ক data,m;
	ৱর্ণ t[12];

	head = (সংরচনা গ্ৰন্থি*)malloc(পরিমাণ(সংরচনা গ্ৰন্থি));

	যদি(head == রিক্ত)
	{
		printf("\n Memory cannot be allocated");
	}
	অন্যথা
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->অঙ্ক = data;
		head->nptr = রিক্ত;
		tmp = head;

		বাবে(পূর্ণাঙ্ক i = 2;i <= n; i++)
		{
			গ্ৰন্থি = (সংরচনা গ্ৰন্থি*)malloc(পরিমাণ(সংরচনা গ্ৰন্থি));

			যদি(গ্ৰন্থি == রিক্ত)
			{
				printf("\n Memory Cannot be allocated");
			}
			অন্যথা 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				গ্ৰন্থি->অঙ্ক = data;
				গ্ৰন্থি->nptr = রিক্ত;

				tmp->nptr = গ্ৰন্থি;
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
	পূর্ণাঙ্ক i = 0;
	সংরচনা গ্ৰন্থি *tmp;

	যদি(head == রিক্ত)
	{
		printf(" List is empty.");
	}
	অন্যথা
	{
		tmp = head;
		যেতিয়ালৈ(tmp != রিক্ত) 
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
শূন্য delete_গ্ৰন্থি(পূর্ণাঙ্ক position)
{
	সংরচনা গ্ৰন্থি *temp;

	যদি(head == রিক্ত)
	{
		printf(" List is empty.");
	}
	অন্যথা 
	{
		temp = head;

		যদি (position == 0)//Delete head node
		{
			head = temp->nptr;
			মুক্ত(temp);
			ঘূৰাই;
		}

		বাবে (পূর্ণাঙ্ক i = 0; temp != রিক্ত && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		যদি (temp == রিক্ত || temp->nptr == রিক্ত)
			ঘূৰাই;

		//delete node at pos (next of position-1)
		সংরচনা গ্ৰন্থি *nptr = temp->nptr->nptr;

		মুক্ত(temp->nptr);
		temp->nptr = nptr; 
	}
}
