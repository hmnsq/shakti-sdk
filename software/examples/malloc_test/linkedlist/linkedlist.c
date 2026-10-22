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

بنية گرہ {
	صحيح عدد;
	بنية گرہ *nptr;
}*سر;

فراغ create_list(صحيح n);
فراغ display_list();
فراغ delete_گرہ(صحيح position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
فراغ مکھ()
{
	صحيح n,position,m;
	حرف t[15];
	لکھو("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = atoi(t);

	create_list(n);

	لکھو("\n\n\nData entered in the list\n");

	display_list();

	لکھو("\n\n Deletion\n");
	لکھو("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = atoi(t);

	delete_گرہ(position);

	لکھو("\nLinked list after deletion\n");
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
	بنية گرہ *گرہ, *tmp;
	صحيح انکڑے_2,m;
	حرف t[12];

	سر = (بنية گرہ*)حافظہ_دیو(حجم(بنية گرہ));

	إذا(سر == عدم)
	{
		لکھو("\n Memory cannot be allocated");
	}
	وإلا
	{
		لکھو("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		انکڑے_2 = atoi(t);

		سر->عدد = انکڑے_2;
		سر->nptr = عدم;
		tmp = سر;

		لكل(صحيح i = 2;i <= n; i++)
		{
			گرہ = (بنية گرہ*)حافظہ_دیو(حجم(بنية گرہ));

			إذا(گرہ == عدم)
			{
				لکھو("\n Memory Cannot be allocated");
			}
			وإلا 
			{
				لکھو("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				انکڑے_2 = atoi(t);
				گرہ->عدد = انکڑے_2;
				گرہ->nptr = عدم;

				tmp->nptr = گرہ;
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
	بنية گرہ *tmp;

	إذا(سر == عدم)
	{
		لکھو(" List is empty.");
	}
	وإلا
	{
		tmp = سر;
		طالما(tmp != عدم) 
		{
			لکھو(" Node%d = %d",i,tmp->عدد);
			لکھو("->");
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
فراغ delete_گرہ(صحيح position)
{
	بنية گرہ *عارضی;

	إذا(سر == عدم)
	{
		لکھو(" List is empty.");
	}
	وإلا 
	{
		عارضی = سر;

		إذا (position == 0)//Delete head node
		{
			سر = عارضی->nptr;
			حرر(عارضی);
			أرجع;
		}

		لكل (صحيح i = 0; عارضی != عدم && i < position-1; i++)//store previous of to be deleted node
		{
			عارضی = عارضی->nptr;
		}

		إذا (عارضی == عدم || عارضی->nptr == عدم)
			أرجع;

		//delete node at pos (next of position-1)
		بنية گرہ *nptr = عارضی->nptr->nptr;

		حرر(عارضی->nptr);
		عارضی->nptr = nptr; 
	}
}
