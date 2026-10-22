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

#அந்தர்பாவ "uart.h"
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>

கட்டமைப்பு முனை {
	முழு இலக்கம்;
	கட்டமைப்பு முனை *nptr;
}*head;

வெறுமை create_list(முழு n);
வெறுமை display_list();
வெறுமை delete_முனை(முழு position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
வெறுமை முதன்மை()
{
	முழு n,position,m;
	எழுத்து t[15];
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

	delete_முனை(position);

	printf("\nLinked list after deletion\n");
	display_list();

	போது(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
வெறுமை create_list(முழு n)
{
	கட்டமைப்பு முனை *முனை, *tmp;
	முழு data,m;
	எழுத்து t[12];

	head = (கட்டமைப்பு முனை*)malloc(அளவு(கட்டமைப்பு முனை));

	எனில்(head == வெற்று)
	{
		printf("\n Memory cannot be allocated");
	}
	இல்லையெனில்
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->இலக்கம் = data;
		head->nptr = வெற்று;
		tmp = head;

		க்கு(முழு i = 2;i <= n; i++)
		{
			முனை = (கட்டமைப்பு முனை*)malloc(அளவு(கட்டமைப்பு முனை));

			எனில்(முனை == வெற்று)
			{
				printf("\n Memory Cannot be allocated");
			}
			இல்லையெனில் 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				முனை->இலக்கம் = data;
				முனை->nptr = வெற்று;

				tmp->nptr = முனை;
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
வெறுமை display_list()
{
	முழு i = 0;
	கட்டமைப்பு முனை *tmp;

	எனில்(head == வெற்று)
	{
		printf(" List is empty.");
	}
	இல்லையெனில்
	{
		tmp = head;
		போது(tmp != வெற்று) 
		{
			printf(" Node%d = %d",i,tmp->இலக்கம்);
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
வெறுமை delete_முனை(முழு position)
{
	கட்டமைப்பு முனை *temp;

	எனில்(head == வெற்று)
	{
		printf(" List is empty.");
	}
	இல்லையெனில் 
	{
		temp = head;

		எனில் (position == 0)//Delete head node
		{
			head = temp->nptr;
			விடுவி(temp);
			திரும்பு;
		}

		க்கு (முழு i = 0; temp != வெற்று && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		எனில் (temp == வெற்று || temp->nptr == வெற்று)
			திரும்பு;

		//delete node at pos (next of position-1)
		கட்டமைப்பு முனை *nptr = temp->nptr->nptr;

		விடுவி(temp->nptr);
		temp->nptr = nptr; 
	}
}
