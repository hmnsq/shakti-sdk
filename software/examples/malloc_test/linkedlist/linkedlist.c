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

بنية گره {
	صحيح رقم;
	بنية گره *nptr;
}*سر;

فراغ create_list(صحيح n);
فراغ display_list();
فراغ delete_گره(صحيح position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
فراغ اصلی()
{
	صحيح n,position,m;
	حرف t[15];
	چاپ_کن("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = atoi(t);

	create_list(n);

	چاپ_کن("\n\n\nData entered in the list\n");

	display_list();

	چاپ_کن("\n\n Deletion\n");
	چاپ_کن("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = atoi(t);

	delete_گره(position);

	چاپ_کن("\nLinked list after deletion\n");
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
	بنية گره *گره, *tmp;
	صحيح داده_2,m;
	حرف t[12];

	سر = (بنية گره*)حافظه_بده(حجم(بنية گره));

	إذا(سر == عدم)
	{
		چاپ_کن("\n Memory cannot be allocated");
	}
	وإلا
	{
		چاپ_کن("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		داده_2 = atoi(t);

		سر->رقم = داده_2;
		سر->nptr = عدم;
		tmp = سر;

		لكل(صحيح i = 2;i <= n; i++)
		{
			گره = (بنية گره*)حافظه_بده(حجم(بنية گره));

			إذا(گره == عدم)
			{
				چاپ_کن("\n Memory Cannot be allocated");
			}
			وإلا 
			{
				چاپ_کن("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				داده_2 = atoi(t);
				گره->رقم = داده_2;
				گره->nptr = عدم;

				tmp->nptr = گره;
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
	بنية گره *tmp;

	إذا(سر == عدم)
	{
		چاپ_کن(" List is empty.");
	}
	وإلا
	{
		tmp = سر;
		طالما(tmp != عدم) 
		{
			چاپ_کن(" Node%d = %d",i,tmp->رقم);
			چاپ_کن("->");
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
فراغ delete_گره(صحيح position)
{
	بنية گره *موقت;

	إذا(سر == عدم)
	{
		چاپ_کن(" List is empty.");
	}
	وإلا 
	{
		موقت = سر;

		إذا (position == 0)//Delete head node
		{
			سر = موقت->nptr;
			حرر(موقت);
			أرجع;
		}

		لكل (صحيح i = 0; موقت != عدم && i < position-1; i++)//store previous of to be deleted node
		{
			موقت = موقت->nptr;
		}

		إذا (موقت == عدم || موقت->nptr == عدم)
			أرجع;

		//delete node at pos (next of position-1)
		بنية گره *nptr = موقت->nptr->nptr;

		حرر(موقت->nptr);
		موقت->nptr = nptr; 
	}
}
