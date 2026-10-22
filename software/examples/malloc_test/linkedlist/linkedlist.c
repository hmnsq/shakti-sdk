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

#ضمن "uart.h"
#ضمن <stdio.h>
#ضمن <stdlib.h>

بنية كلي {
	صحيح لمب;
	بنية كلي *nptr;
}*head;

فراغ create_list(صحيح n);
فراغ display_list();
فراغ delete_كلي(صحيح position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
فراغ main()
{
	صحيح n,position,m;
	حرف t[15];
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

	delete_كلي(position);

	printf("\nLinked list after deletion\n");
	display_list();

	طالما(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
فراغ create_list(صحيح n)
{
	بنية كلي *كلي, *tmp;
	صحيح data,m;
	حرف t[12];

	head = (بنية كلي*)malloc(حجم(بنية كلي));

	إذا(head == عدم)
	{
		printf("\n Memory cannot be allocated");
	}
	وإلا
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->لمب = data;
		head->nptr = عدم;
		tmp = head;

		لكل(صحيح i = 2;i <= n; i++)
		{
			كلي = (بنية كلي*)malloc(حجم(بنية كلي));

			إذا(كلي == عدم)
			{
				printf("\n Memory Cannot be allocated");
			}
			وإلا 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				كلي->لمب = data;
				كلي->nptr = عدم;

				tmp->nptr = كلي;
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
فراغ display_list()
{
	صحيح i = 0;
	بنية كلي *tmp;

	إذا(head == عدم)
	{
		printf(" List is empty.");
	}
	وإلا
	{
		tmp = head;
		طالما(tmp != عدم) 
		{
			printf(" Node%d = %d",i,tmp->لمب);
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
فراغ delete_كلي(صحيح position)
{
	بنية كلي *temp;

	إذا(head == عدم)
	{
		printf(" List is empty.");
	}
	وإلا 
	{
		temp = head;

		إذا (position == 0)//Delete head node
		{
			head = temp->nptr;
			حرر(temp);
			أرجع;
		}

		لكل (صحيح i = 0; temp != عدم && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		إذا (temp == عدم || temp->nptr == عدم)
			أرجع;

		//delete node at pos (next of position-1)
		بنية كلي *nptr = temp->nptr->nptr;

		حرر(temp->nptr);
		temp->nptr = nptr; 
	}
}
