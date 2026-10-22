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

#ଅନ୍ତର୍ଭାଵ "uart.h"
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>

ସଂରଚନା ଗଣ୍ଠି {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ;
	ସଂରଚନା ଗଣ୍ଠି *nptr;
}*head;

ଶୂନ୍ୟ create_list(ପୂର୍ଣ୍ଣସଂଖ୍ୟା n);
ଶୂନ୍ୟ display_list();
ଶୂନ୍ୟ delete_ଗଣ୍ଠି(ପୂର୍ଣ୍ଣସଂଖ୍ୟା position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
ଶୂନ୍ୟ ମୁଖ୍ୟ()
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା n,position,m;
	ଅକ୍ଷର t[15];
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

	delete_ଗଣ୍ଠି(position);

	printf("\nLinked list after deletion\n");
	display_list();

	ଯେତେବେଳେ(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
ଶୂନ୍ୟ create_list(ପୂର୍ଣ୍ଣସଂଖ୍ୟା n)
{
	ସଂରଚନା ଗଣ୍ଠି *ଗଣ୍ଠି, *tmp;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା data,m;
	ଅକ୍ଷର t[12];

	head = (ସଂରଚନା ଗଣ୍ଠି*)malloc(ଆକାର(ସଂରଚନା ଗଣ୍ଠି));

	ଯଦି(head == ଖାଲି)
	{
		printf("\n Memory cannot be allocated");
	}
	ଅନ୍ୟଥା
	{
		printf("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		data = atoi(t);

		head->ଅଙ୍କ = data;
		head->nptr = ଖାଲି;
		tmp = head;

		ପାଇଁ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 2;i <= n; i++)
		{
			ଗଣ୍ଠି = (ସଂରଚନା ଗଣ୍ଠି*)malloc(ଆକାର(ସଂରଚନା ଗଣ୍ଠି));

			ଯଦି(ଗଣ୍ଠି == ଖାଲି)
			{
				printf("\n Memory Cannot be allocated");
			}
			ଅନ୍ୟଥା 
			{
				printf("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				data = atoi(t);
				ଗଣ୍ଠି->ଅଙ୍କ = data;
				ଗଣ୍ଠି->nptr = ଖାଲି;

				tmp->nptr = ଗଣ୍ଠି;
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
ଶୂନ୍ୟ display_list()
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;
	ସଂରଚନା ଗଣ୍ଠି *tmp;

	ଯଦି(head == ଖାଲି)
	{
		printf(" List is empty.");
	}
	ଅନ୍ୟଥା
	{
		tmp = head;
		ଯେତେବେଳେ(tmp != ଖାଲି) 
		{
			printf(" Node%d = %d",i,tmp->ଅଙ୍କ);
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
ଶୂନ୍ୟ delete_ଗଣ୍ଠି(ପୂର୍ଣ୍ଣସଂଖ୍ୟା position)
{
	ସଂରଚନା ଗଣ୍ଠି *temp;

	ଯଦି(head == ଖାଲି)
	{
		printf(" List is empty.");
	}
	ଅନ୍ୟଥା 
	{
		temp = head;

		ଯଦି (position == 0)//Delete head node
		{
			head = temp->nptr;
			ମୁକ୍ତ(temp);
			ଫେରନ୍ତୁ;
		}

		ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; temp != ଖାଲି && i < position-1; i++)//store previous of to be deleted node
		{
			temp = temp->nptr;
		}

		ଯଦି (temp == ଖାଲି || temp->nptr == ଖାଲି)
			ଫେରନ୍ତୁ;

		//delete node at pos (next of position-1)
		ସଂରଚନା ଗଣ୍ଠି *nptr = temp->nptr->nptr;

		ମୁକ୍ତ(temp->nptr);
		temp->nptr = nptr; 
	}
}
