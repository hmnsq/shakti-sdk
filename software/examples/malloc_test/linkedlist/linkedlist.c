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

#അന്തര്ഭാവ "uart.h"
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>

ഘടന കണ്ണി {
	പൂർണ്ണസംഖ്യ അക്കം;
	ഘടന കണ്ണി *nptr;
}*head;

ശൂന്യം create_list(പൂർണ്ണസംഖ്യ n);
ശൂന്യം display_list();
ശൂന്യം delete_കണ്ണി(പൂർണ്ണസംഖ്യ position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
ശൂന്യം പ്രധാന()
{
	പൂർണ്ണസംഖ്യ n,position,m;
	അക്ഷരം t[15];
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

	delete_കണ്ണി(position);

	printf("\nLinked list after deletion\n");
	display_list();

	ആകുമ്പോൾ(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
ശൂന്യം create_list(പൂർണ്ണസംഖ്യ n)
{
	ഘടന കണ്ണി *കണ്ണി, *tmp;
	പൂർണ്ണസംഖ്യ data,m;
	അക്ഷരം t[12];

	head = (ഘടന കണ്ണി*)malloc(വലുപ്പം(ഘടന കണ്ണി));

	എങ്കിൽ(head == ശൂന്യ)
	{
		printf("\n Memory cannot be allocated");
	}
	അല്ലെങ്കിൽ
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->അക്കം = data;
		head->nptr = ശൂന്യ;
		tmp = head;

		വേണ്ടി(പൂർണ്ണസംഖ്യ i = 2;i <= n; i++)
		{
			കണ്ണി = (ഘടന കണ്ണി*)malloc(വലുപ്പം(ഘടന കണ്ണി));

			എങ്കിൽ(കണ്ണി == ശൂന്യ)
			{
				printf("\n Memory Cannot be allocated");
			}
			അല്ലെങ്കിൽ 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				കണ്ണി->അക്കം = data;
				കണ്ണി->nptr = ശൂന്യ;

				tmp->nptr = കണ്ണി;
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
ശൂന്യം display_list()
{
	പൂർണ്ണസംഖ്യ i = 0;
	ഘടന കണ്ണി *tmp;

	എങ്കിൽ(head == ശൂന്യ)
	{
		printf(" List is empty.");
	}
	അല്ലെങ്കിൽ
	{
		tmp = head;
		ആകുമ്പോൾ(tmp != ശൂന്യ) 
		{
			printf(" Node%d = %d",i,tmp->അക്കം);
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
ശൂന്യം delete_കണ്ണി(പൂർണ്ണസംഖ്യ position)
{
	ഘടന കണ്ണി *temp;

	എങ്കിൽ(head == ശൂന്യ)
	{
		printf(" List is empty.");
	}
	അല്ലെങ്കിൽ 
	{
		temp = head;

		എങ്കിൽ (position == 0)//Delete head node
		{
			head = temp->nptr;
			സ്വതന്ത്രം(temp);
			തിരികെ;
		}

		വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; temp != ശൂന്യ && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		എങ്കിൽ (temp == ശൂന്യ || temp->nptr == ശൂന്യ)
			തിരികെ;

		//delete node at pos (next of position-1)
		ഘടന കണ്ണി *nptr = temp->nptr->nptr;

		സ്വതന്ത്രം(temp->nptr);
		temp->nptr = nptr; 
	}
}
