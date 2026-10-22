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

#અન્તર્ભાવ "uart.h"
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>

સંરચના ગાંઠ {
	પૂર્ણાંક અંક;
	સંરચના ગાંઠ *nptr;
}*head;

શૂન્ય create_list(પૂર્ણાંક n);
શૂન્ય display_list();
શૂન્ય delete_ગાંઠ(પૂર્ણાંક position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
શૂન્ય મુખ્ય()
{
	પૂર્ણાંક n,position,m;
	અક્ષર t[15];
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

	delete_ગાંઠ(position);

	printf("\nLinked list after deletion\n");
	display_list();

	જ્યારે(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
શૂન્ય create_list(પૂર્ણાંક n)
{
	સંરચના ગાંઠ *ગાંઠ, *tmp;
	પૂર્ણાંક data,m;
	અક્ષર t[12];

	head = (સંરચના ગાંઠ*)malloc(કદ(સંરચના ગાંઠ));

	જો(head == ખાલી)
	{
		printf("\n Memory cannot be allocated");
	}
	નહીંતર
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->અંક = data;
		head->nptr = ખાલી;
		tmp = head;

		માટે(પૂર્ણાંક i = 2;i <= n; i++)
		{
			ગાંઠ = (સંરચના ગાંઠ*)malloc(કદ(સંરચના ગાંઠ));

			જો(ગાંઠ == ખાલી)
			{
				printf("\n Memory Cannot be allocated");
			}
			નહીંતર 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				ગાંઠ->અંક = data;
				ગાંઠ->nptr = ખાલી;

				tmp->nptr = ગાંઠ;
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
શૂન્ય display_list()
{
	પૂર્ણાંક i = 0;
	સંરચના ગાંઠ *tmp;

	જો(head == ખાલી)
	{
		printf(" List is empty.");
	}
	નહીંતર
	{
		tmp = head;
		જ્યારે(tmp != ખાલી) 
		{
			printf(" Node%d = %d",i,tmp->અંક);
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
શૂન્ય delete_ગાંઠ(પૂર્ણાંક position)
{
	સંરચના ગાંઠ *temp;

	જો(head == ખાલી)
	{
		printf(" List is empty.");
	}
	નહીંતર 
	{
		temp = head;

		જો (position == 0)//Delete head node
		{
			head = temp->nptr;
			મુક્ત(temp);
			પાછા;
		}

		માટે (પૂર્ણાંક i = 0; temp != ખાલી && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		જો (temp == ખાલી || temp->nptr == ખાલી)
			પાછા;

		//delete node at pos (next of position-1)
		સંરચના ગાંઠ *nptr = temp->nptr->nptr;

		મુક્ત(temp->nptr);
		temp->nptr = nptr; 
	}
}
