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

#include "uart.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
	ціле num;
	struct node *nptr;
}*head;

void create_list(ціле n);
void display_list();
void delete_node(ціле position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
void main()
{
	ціле n,position,m;
	char t[15];
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

	delete_node(position);

	printf("\nLinked list after deletion\n");
	display_list();

	поки(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
void create_list(ціле n)
{
	struct node *node, *tmp;
	ціле data,m;
	char t[12];

	head = (struct node*)malloc(sizeof(struct node));

	якщо(head == NULL)
	{
		printf("\n Memory cannot be allocated");
	}
	інакше
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->num = data;
		head->nptr = NULL;
		tmp = head;

		для(ціле i = 2;i <= n; i++)
		{
			node = (struct node*)malloc(sizeof(struct node));

			якщо(node == NULL)
			{
				printf("\n Memory Cannot be allocated");
			}
			інакше 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				node->num = data;
				node->nptr = NULL;

				tmp->nptr = node;
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
void display_list()
{
	ціле i = 0;
	struct node *tmp;

	якщо(head == NULL)
	{
		printf(" List is empty.");
	}
	інакше
	{
		tmp = head;
		поки(tmp != NULL) 
		{
			printf(" Node%d = %d",i,tmp->num);
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
void delete_node(ціле position)
{
	struct node *temp;

	якщо(head == NULL)
	{
		printf(" List is empty.");
	}
	інакше 
	{
		temp = head;

		якщо (position == 0)//Delete head node
		{
			head = temp->nptr;
			free(temp);
			повернути;
		}

		для (ціле i = 0; temp != NULL && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		якщо (temp == NULL || temp->nptr == NULL)
			повернути;

		//delete node at pos (next of position-1)
		struct node *nptr = temp->nptr->nptr;

		free(temp->nptr);
		temp->nptr = nptr; 
	}
}
