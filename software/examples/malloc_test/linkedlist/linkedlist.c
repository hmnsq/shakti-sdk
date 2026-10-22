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

بنية غوټه {
	صحيح عدد;
	بنية غوټه *nptr;
}*سر;

فراغ create_list(صحيح n);
فراغ display_list();
فراغ delete_غوټه(صحيح position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
فراغ اصلي()
{
	صحيح n,position,m;
	حرف t[15];
	چاپ_کړه("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = atoi(t);

	create_list(n);

	چاپ_کړه("\n\n\nData entered in the list\n");

	display_list();

	چاپ_کړه("\n\n Deletion\n");
	چاپ_کړه("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = atoi(t);

	delete_غوټه(position);

	چاپ_کړه("\nLinked list after deletion\n");
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
	بنية غوټه *غوټه, *tmp;
	صحيح معلومات_2,m;
	حرف t[12];

	سر = (بنية غوټه*)حافظه_ورکړه(حجم(بنية غوټه));

	إذا(سر == عدم)
	{
		چاپ_کړه("\n Memory cannot be allocated");
	}
	وإلا
	{
		چاپ_کړه("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		معلومات_2 = atoi(t);

		سر->عدد = معلومات_2;
		سر->nptr = عدم;
		tmp = سر;

		لكل(صحيح i = 2;i <= n; i++)
		{
			غوټه = (بنية غوټه*)حافظه_ورکړه(حجم(بنية غوټه));

			إذا(غوټه == عدم)
			{
				چاپ_کړه("\n Memory Cannot be allocated");
			}
			وإلا 
			{
				چاپ_کړه("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				معلومات_2 = atoi(t);
				غوټه->عدد = معلومات_2;
				غوټه->nptr = عدم;

				tmp->nptr = غوټه;
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
	بنية غوټه *tmp;

	إذا(سر == عدم)
	{
		چاپ_کړه(" List is empty.");
	}
	وإلا
	{
		tmp = سر;
		طالما(tmp != عدم) 
		{
			چاپ_کړه(" Node%d = %d",i,tmp->عدد);
			چاپ_کړه("->");
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
فراغ delete_غوټه(صحيح position)
{
	بنية غوټه *لنډمهاله;

	إذا(سر == عدم)
	{
		چاپ_کړه(" List is empty.");
	}
	وإلا 
	{
		لنډمهاله = سر;

		إذا (position == 0)//Delete head node
		{
			سر = لنډمهاله->nptr;
			حرر(لنډمهاله);
			أرجع;
		}

		لكل (صحيح i = 0; لنډمهاله != عدم && i < position-1; i++)//store previous of to be deleted node
		{
			لنډمهاله = لنډمهاله->nptr;
		}

		إذا (لنډمهاله == عدم || لنډمهاله->nptr == عدم)
			أرجع;

		//delete node at pos (next of position-1)
		بنية غوټه *nptr = لنډمهاله->nptr->nptr;

		حرر(لنډمهاله->nptr);
		لنډمهاله->nptr = nptr; 
	}
}
