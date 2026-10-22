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

#شامل "uart.h"
#شامل <stdio.h>
#شامل <stdlib.h>

ساخت گرہ {
	صحیح عدد;
	ساخت گرہ *nptr;
}*سر;

خالی create_list(صحیح n);
خالی display_list();
خالی delete_گرہ(صحیح position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
خالی مین()
{
	صحیح n,position,m;
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

	جب(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
خالی create_list(صحیح n)
{
	ساخت گرہ *گرہ, *tmp;
	صحیح ڈیٹا_2,m;
	حرف t[12];

	سر = (ساخت گرہ*)حافظہ_دو(حجم(ساخت گرہ));

	اگر(سر == تہی)
	{
		لکھو("\n Memory cannot be allocated");
	}
	ورنہ
	{
		لکھو("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		ڈیٹا_2 = atoi(t);

		سر->عدد = ڈیٹا_2;
		سر->nptr = تہی;
		tmp = سر;

		برائے(صحیح i = 2;i <= n; i++)
		{
			گرہ = (ساخت گرہ*)حافظہ_دو(حجم(ساخت گرہ));

			اگر(گرہ == تہی)
			{
				لکھو("\n Memory Cannot be allocated");
			}
			ورنہ 
			{
				لکھو("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				ڈیٹا_2 = atoi(t);
				گرہ->عدد = ڈیٹا_2;
				گرہ->nptr = تہی;

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
خالی display_list()
{
	صحیح i = 0;
	ساخت گرہ *tmp;

	اگر(سر == تہی)
	{
		لکھو(" List is empty.");
	}
	ورنہ
	{
		tmp = سر;
		جب(tmp != تہی) 
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
خالی delete_گرہ(صحیح position)
{
	ساخت گرہ *عارضی;

	اگر(سر == تہی)
	{
		لکھو(" List is empty.");
	}
	ورنہ 
	{
		عارضی = سر;

		اگر (position == 0)//Delete head node
		{
			سر = عارضی->nptr;
			آزاد(عارضی);
			واپس;
		}

		برائے (صحیح i = 0; عارضی != تہی && i < position-1; i++)//store previous of to be deleted node
		{
			عارضی = عارضی->nptr;
		}

		اگر (عارضی == تہی || عارضی->nptr == تہی)
			واپس;

		//delete node at pos (next of position-1)
		ساخت گرہ *nptr = عارضی->nptr->nptr;

		آزاد(عارضی->nptr);
		عارضی->nptr = nptr; 
	}
}
