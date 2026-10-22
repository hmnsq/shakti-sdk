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

sa_nracanaa node {
	puur_naa_nka num;
	sa_nracanaa node *nptr;
}*head;

void create_list(puur_naa_nka n);
void display_list();
void delete_node(puur_naa_nka position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
void main()
{
	puur_naa_nka n,position,m;
	var_na t[15];
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

	ꦱꦼꦢꦼꦭ(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
void create_list(puur_naa_nka n)
{
	sa_nracanaa node *node, *tmp;
	puur_naa_nka data,m;
	var_na t[12];

	head = (sa_nracanaa node*)malloc(parimaa_na(sa_nracanaa node));

	ꦪꦼꦤ꧀(head == NULL)
	{
		printf("\n Memory cannot be allocated");
	}
	ꦭꦶꦪ
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->num = data;
		head->nptr = NULL;
		tmp = head;

		ꦏꦁꦒꦺꦴ(puur_naa_nka i = 2;i <= n; i++)
		{
			node = (sa_nracanaa node*)malloc(parimaa_na(sa_nracanaa node));

			ꦪꦼꦤ꧀(node == NULL)
			{
				printf("\n Memory Cannot be allocated");
			}
			ꦭꦶꦪ 
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
	puur_naa_nka i = 0;
	sa_nracanaa node *tmp;

	ꦪꦼꦤ꧀(head == NULL)
	{
		printf(" List is empty.");
	}
	ꦭꦶꦪ
	{
		tmp = head;
		ꦱꦼꦢꦼꦭ(tmp != NULL) 
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
void delete_node(puur_naa_nka position)
{
	sa_nracanaa node *temp;

	ꦪꦼꦤ꧀(head == NULL)
	{
		printf(" List is empty.");
	}
	ꦭꦶꦪ 
	{
		temp = head;

		ꦪꦼꦤ꧀ (position == 0)//Delete head node
		{
			head = temp->nptr;
			free(temp);
			ꦮꦭꦶ;
		}

		ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; temp != NULL && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		ꦪꦼꦤ꧀ (temp == NULL || temp->nptr == NULL)
			ꦮꦭꦶ;

		//delete node at pos (next of position-1)
		sa_nracanaa node *nptr = temp->nptr->nptr;

		free(temp->nptr);
		temp->nptr = nptr; 
	}
}
