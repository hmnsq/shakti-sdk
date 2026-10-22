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

#अन्तर्भाव "uart.h"
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>

संरचना गाठ {
	पूर्णाङ्क अंक;
	संरचना गाठ *nptr;
}*head;

शून्य create_list(पूर्णाङ्क n);
शून्य display_list();
शून्य delete_गाठ(पूर्णाङ्क position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
शून्य main()
{
	पूर्णाङ्क n,position,m;
	वर्ण t[15];
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

	delete_गाठ(position);

	printf("\nLinked list after deletion\n");
	display_list();

	यावत्(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
शून्य create_list(पूर्णाङ्क n)
{
	संरचना गाठ *गाठ, *tmp;
	पूर्णाङ्क data,m;
	वर्ण t[12];

	head = (संरचना गाठ*)malloc(परिमाण(संरचना गाठ));

	यदि(head == रिक्त)
	{
		printf("\n Memory cannot be allocated");
	}
	अन्यथा
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->अंक = data;
		head->nptr = रिक्त;
		tmp = head;

		प्रति(पूर्णाङ्क i = 2;i <= n; i++)
		{
			गाठ = (संरचना गाठ*)malloc(परिमाण(संरचना गाठ));

			यदि(गाठ == रिक्त)
			{
				printf("\n Memory Cannot be allocated");
			}
			अन्यथा 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				गाठ->अंक = data;
				गाठ->nptr = रिक्त;

				tmp->nptr = गाठ;
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
शून्य display_list()
{
	पूर्णाङ्क i = 0;
	संरचना गाठ *tmp;

	यदि(head == रिक्त)
	{
		printf(" List is empty.");
	}
	अन्यथा
	{
		tmp = head;
		यावत्(tmp != रिक्त) 
		{
			printf(" Node%d = %d",i,tmp->अंक);
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
शून्य delete_गाठ(पूर्णाङ्क position)
{
	संरचना गाठ *temp;

	यदि(head == रिक्त)
	{
		printf(" List is empty.");
	}
	अन्यथा 
	{
		temp = head;

		यदि (position == 0)//Delete head node
		{
			head = temp->nptr;
			मुक्त(temp);
			प्रत्यागम;
		}

		प्रति (पूर्णाङ्क i = 0; temp != रिक्त && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		यदि (temp == रिक्त || temp->nptr == रिक्त)
			प्रत्यागम;

		//delete node at pos (next of position-1)
		संरचना गाठ *nptr = temp->nptr->nptr;

		मुक्त(temp->nptr);
		temp->nptr = nptr; 
	}
}
