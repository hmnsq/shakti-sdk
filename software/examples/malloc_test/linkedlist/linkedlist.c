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

#شامل "uart.h"
#شامل <stdio.h>
#شامل <stdlib.h>

ساختار گره {
	صحیح رقم;
	ساختار گره *nptr;
}*head;

تهی create_list(صحیح n);
تهی display_list();
تهی delete_گره(صحیح position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
تهی اصلی()
{
	صحیح n,position,m;
	نویسه t[15];
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

	delete_گره(position);

	printf("\nLinked list after deletion\n");
	display_list();

	وقتی(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
تهی create_list(صحیح n)
{
	ساختار گره *گره, *tmp;
	صحیح data,m;
	نویسه t[12];

	head = (ساختار گره*)malloc(اندازه(ساختار گره));

	اگر(head == پوچ)
	{
		printf("\n Memory cannot be allocated");
	}
	وگرنه
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->رقم = data;
		head->nptr = پوچ;
		tmp = head;

		برای(صحیح i = 2;i <= n; i++)
		{
			گره = (ساختار گره*)malloc(اندازه(ساختار گره));

			اگر(گره == پوچ)
			{
				printf("\n Memory Cannot be allocated");
			}
			وگرنه 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				گره->رقم = data;
				گره->nptr = پوچ;

				tmp->nptr = گره;
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
تهی display_list()
{
	صحیح i = 0;
	ساختار گره *tmp;

	اگر(head == پوچ)
	{
		printf(" List is empty.");
	}
	وگرنه
	{
		tmp = head;
		وقتی(tmp != پوچ) 
		{
			printf(" Node%d = %d",i,tmp->رقم);
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
تهی delete_گره(صحیح position)
{
	ساختار گره *temp;

	اگر(head == پوچ)
	{
		printf(" List is empty.");
	}
	وگرنه 
	{
		temp = head;

		اگر (position == 0)//Delete head node
		{
			head = temp->nptr;
			آزاد(temp);
			بازگشت;
		}

		برای (صحیح i = 0; temp != پوچ && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		اگر (temp == پوچ || temp->nptr == پوچ)
			بازگشت;

		//delete node at pos (next of position-1)
		ساختار گره *nptr = temp->nptr->nptr;

		آزاد(temp->nptr);
		temp->nptr = nptr; 
	}
}
