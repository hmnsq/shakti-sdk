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

संरचना ग्रन्थिः {
	पूर्णाङ्क अङ्कः;
	संरचना ग्रन्थिः *nptr;
}*head;

शून्य create_list(पूर्णाङ्क n);
शून्य display_list();
शून्य delete_ग्रन्थिः(पूर्णाङ्क position);

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

	delete_ग्रन्थिः(position);

	printf("\nLinked list after deletion\n");
	display_list();

	जाव(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
शून्य create_list(पूर्णाङ्क n)
{
	संरचना ग्रन्थिः *ग्रन्थिः, *tmp;
	पूर्णाङ्क data,m;
	वर्ण t[12];

	head = (संरचना ग्रन्थिः*)malloc(परिमाण(संरचना ग्रन्थिः));

	जइ(head == रिक्त)
	{
		printf("\n Memory cannot be allocated");
	}
	अण्णहा
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->अङ्कः = data;
		head->nptr = रिक्त;
		tmp = head;

		प्रति(पूर्णाङ्क i = 2;i <= n; i++)
		{
			ग्रन्थिः = (संरचना ग्रन्थिः*)malloc(परिमाण(संरचना ग्रन्थिः));

			जइ(ग्रन्थिः == रिक्त)
			{
				printf("\n Memory Cannot be allocated");
			}
			अण्णहा 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				ग्रन्थिः->अङ्कः = data;
				ग्रन्थिः->nptr = रिक्त;

				tmp->nptr = ग्रन्थिः;
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
	संरचना ग्रन्थिः *tmp;

	जइ(head == रिक्त)
	{
		printf(" List is empty.");
	}
	अण्णहा
	{
		tmp = head;
		जाव(tmp != रिक्त) 
		{
			printf(" Node%d = %d",i,tmp->अङ्कः);
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
शून्य delete_ग्रन्थिः(पूर्णाङ्क position)
{
	संरचना ग्रन्थिः *temp;

	जइ(head == रिक्त)
	{
		printf(" List is empty.");
	}
	अण्णहा 
	{
		temp = head;

		जइ (position == 0)//Delete head node
		{
			head = temp->nptr;
			मुक्त(temp);
			प्रत्यागम;
		}

		प्रति (पूर्णाङ्क i = 0; temp != रिक्त && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		जइ (temp == रिक्त || temp->nptr == रिक्त)
			प्रत्यागम;

		//delete node at pos (next of position-1)
		संरचना ग्रन्थिः *nptr = temp->nptr->nptr;

		मुक्त(temp->nptr);
		temp->nptr = nptr; 
	}
}
