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

#ಅನ್ತರ್ಭಾವ "uart.h"
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>

ಸಂರಚನಾ ಗಂಟು {
	ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ;
	ಸಂರಚನಾ ಗಂಟು *nptr;
}*head;

ಶೂನ್ಯ create_list(ಪೂರ್ಣಾಙ್ಕ n);
ಶೂನ್ಯ display_list();
ಶೂನ್ಯ delete_ಗಂಟು(ಪೂರ್ಣಾಙ್ಕ position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
ಶೂನ್ಯ main()
{
	ಪೂರ್ಣಾಙ್ಕ n,position,m;
	ವರ್ಣ t[15];
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

	delete_ಗಂಟು(position);

	printf("\nLinked list after deletion\n");
	display_list();

	ಯಾವತ್(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
ಶೂನ್ಯ create_list(ಪೂರ್ಣಾಙ್ಕ n)
{
	ಸಂರಚನಾ ಗಂಟು *ಗಂಟು, *tmp;
	ಪೂರ್ಣಾಙ್ಕ data,m;
	ವರ್ಣ t[12];

	head = (ಸಂರಚನಾ ಗಂಟು*)malloc(ಪರಿಮಾಣ(ಸಂರಚನಾ ಗಂಟು));

	ಯದಿ(head == ರಿಕ್ತ)
	{
		printf("\n Memory cannot be allocated");
	}
	ಅನ್ಯಥಾ
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->ಅಂಕೆ = data;
		head->nptr = ರಿಕ್ತ;
		tmp = head;

		ಪ್ರತಿ(ಪೂರ್ಣಾಙ್ಕ i = 2;i <= n; i++)
		{
			ಗಂಟು = (ಸಂರಚನಾ ಗಂಟು*)malloc(ಪರಿಮಾಣ(ಸಂರಚನಾ ಗಂಟು));

			ಯದಿ(ಗಂಟು == ರಿಕ್ತ)
			{
				printf("\n Memory Cannot be allocated");
			}
			ಅನ್ಯಥಾ 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				ಗಂಟು->ಅಂಕೆ = data;
				ಗಂಟು->nptr = ರಿಕ್ತ;

				tmp->nptr = ಗಂಟು;
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
ಶೂನ್ಯ display_list()
{
	ಪೂರ್ಣಾಙ್ಕ i = 0;
	ಸಂರಚನಾ ಗಂಟು *tmp;

	ಯದಿ(head == ರಿಕ್ತ)
	{
		printf(" List is empty.");
	}
	ಅನ್ಯಥಾ
	{
		tmp = head;
		ಯಾವತ್(tmp != ರಿಕ್ತ) 
		{
			printf(" Node%d = %d",i,tmp->ಅಂಕೆ);
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
ಶೂನ್ಯ delete_ಗಂಟು(ಪೂರ್ಣಾಙ್ಕ position)
{
	ಸಂರಚನಾ ಗಂಟು *temp;

	ಯದಿ(head == ರಿಕ್ತ)
	{
		printf(" List is empty.");
	}
	ಅನ್ಯಥಾ 
	{
		temp = head;

		ಯದಿ (position == 0)//Delete head node
		{
			head = temp->nptr;
			ಮುಕ್ತ(temp);
			ಪ್ರತ್ಯಾಗಮ;
		}

		ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; temp != ರಿಕ್ತ && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		ಯದಿ (temp == ರಿಕ್ತ || temp->nptr == ರಿಕ್ತ)
			ಪ್ರತ್ಯಾಗಮ;

		//delete node at pos (next of position-1)
		ಸಂರಚನಾ ಗಂಟು *nptr = temp->nptr->nptr;

		ಮುಕ್ತ(temp->nptr);
		temp->nptr = nptr; 
	}
}
