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

بنية ڳنڍ {
	صحيح انگ;
	بنية ڳنڍ *nptr;
}*سر;

فراغ create_list(صحيح n);
فراغ display_list();
فراغ delete_ڳنڍ(صحيح position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
فراغ مکيه()
{
	صحيح n,position,m;
	حرف t[15];
	لکو("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = atoi(t);

	create_list(n);

	لکو("\n\n\nData entered in the list\n");

	display_list();

	لکو("\n\n Deletion\n");
	لکو("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = atoi(t);

	delete_ڳنڍ(position);

	لکو("\nLinked list after deletion\n");
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
	بنية ڳنڍ *ڳنڍ, *tmp;
	صحيح معلومات_2,m;
	حرف t[12];

	سر = (بنية ڳنڍ*)يادگيري_ڏيو(حجم(بنية ڳنڍ));

	إذا(سر == عدم)
	{
		لکو("\n Memory cannot be allocated");
	}
	وإلا
	{
		لکو("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		معلومات_2 = atoi(t);

		سر->انگ = معلومات_2;
		سر->nptr = عدم;
		tmp = سر;

		لكل(صحيح i = 2;i <= n; i++)
		{
			ڳنڍ = (بنية ڳنڍ*)يادگيري_ڏيو(حجم(بنية ڳنڍ));

			إذا(ڳنڍ == عدم)
			{
				لکو("\n Memory Cannot be allocated");
			}
			وإلا 
			{
				لکو("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				معلومات_2 = atoi(t);
				ڳنڍ->انگ = معلومات_2;
				ڳنڍ->nptr = عدم;

				tmp->nptr = ڳنڍ;
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
	بنية ڳنڍ *tmp;

	إذا(سر == عدم)
	{
		لکو(" List is empty.");
	}
	وإلا
	{
		tmp = سر;
		طالما(tmp != عدم) 
		{
			لکو(" Node%d = %d",i,tmp->انگ);
			لکو("->");
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
فراغ delete_ڳنڍ(صحيح position)
{
	بنية ڳنڍ *عارضي;

	إذا(سر == عدم)
	{
		لکو(" List is empty.");
	}
	وإلا 
	{
		عارضي = سر;

		إذا (position == 0)//Delete head node
		{
			سر = عارضي->nptr;
			حرر(عارضي);
			أرجع;
		}

		لكل (صحيح i = 0; عارضي != عدم && i < position-1; i++)//store previous of to be deleted node
		{
			عارضي = عارضي->nptr;
		}

		إذا (عارضي == عدم || عارضي->nptr == عدم)
			أرجع;

		//delete node at pos (next of position-1)
		بنية ڳنڍ *nptr = عارضي->nptr->nptr;

		حرر(عارضي->nptr);
		عارضي->nptr = nptr; 
	}
}
