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

#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

ਬਣਤਰ ਗੰਢ {
	ਪੂਰਨ ਅੰਕ;
	ਬਣਤਰ ਗੰਢ *nptr;
}*ਸਿਰ;

ਖਾਲੀ create_list(ਪੂਰਨ n);
ਖਾਲੀ display_list();
ਖਾਲੀ delete_ਗੰਢ(ਪੂਰਨ position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
ਖਾਲੀ ਮੁੱਖ()
{
	ਪੂਰਨ n,position,m;
	ਅੱਖਰ t[15];
	ਲਿਖੋ("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = atoi(t);

	create_list(n);

	ਲਿਖੋ("\n\n\nData entered in the list\n");

	display_list();

	ਲਿਖੋ("\n\n Deletion\n");
	ਲਿਖੋ("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = atoi(t);

	delete_ਗੰਢ(position);

	ਲਿਖੋ("\nLinked list after deletion\n");
	display_list();

	ਜਦੋਂ(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
ਖਾਲੀ create_list(ਪੂਰਨ n)
{
	ਬਣਤਰ ਗੰਢ *ਗੰਢ, *tmp;
	ਪੂਰਨ ਅੰਕੜੇ_2,m;
	ਅੱਖਰ t[12];

	ਸਿਰ = (ਬਣਤਰ ਗੰਢ*)ਸਮ੍ਰਿਤੀ_ਦਿਓ(ਆਕਾਰ(ਬਣਤਰ ਗੰਢ));

	ਜੇ(ਸਿਰ == ਨਿਰਾ)
	{
		ਲਿਖੋ("\n Memory cannot be allocated");
	}
	ਨਹੀਂਤਾਂ
	{
		ਲਿਖੋ("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		ਅੰਕੜੇ_2 = atoi(t);

		ਸਿਰ->ਅੰਕ = ਅੰਕੜੇ_2;
		ਸਿਰ->nptr = ਨਿਰਾ;
		tmp = ਸਿਰ;

		ਲਈ(ਪੂਰਨ i = 2;i <= n; i++)
		{
			ਗੰਢ = (ਬਣਤਰ ਗੰਢ*)ਸਮ੍ਰਿਤੀ_ਦਿਓ(ਆਕਾਰ(ਬਣਤਰ ਗੰਢ));

			ਜੇ(ਗੰਢ == ਨਿਰਾ)
			{
				ਲਿਖੋ("\n Memory Cannot be allocated");
			}
			ਨਹੀਂਤਾਂ 
			{
				ਲਿਖੋ("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				ਅੰਕੜੇ_2 = atoi(t);
				ਗੰਢ->ਅੰਕ = ਅੰਕੜੇ_2;
				ਗੰਢ->nptr = ਨਿਰਾ;

				tmp->nptr = ਗੰਢ;
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
ਖਾਲੀ display_list()
{
	ਪੂਰਨ i = 0;
	ਬਣਤਰ ਗੰਢ *tmp;

	ਜੇ(ਸਿਰ == ਨਿਰਾ)
	{
		ਲਿਖੋ(" List is empty.");
	}
	ਨਹੀਂਤਾਂ
	{
		tmp = ਸਿਰ;
		ਜਦੋਂ(tmp != ਨਿਰਾ) 
		{
			ਲਿਖੋ(" Node%d = %d",i,tmp->ਅੰਕ);
			ਲਿਖੋ("->");
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
ਖਾਲੀ delete_ਗੰਢ(ਪੂਰਨ position)
{
	ਬਣਤਰ ਗੰਢ *ਆਰਜ਼ੀ;

	ਜੇ(ਸਿਰ == ਨਿਰਾ)
	{
		ਲਿਖੋ(" List is empty.");
	}
	ਨਹੀਂਤਾਂ 
	{
		ਆਰਜ਼ੀ = ਸਿਰ;

		ਜੇ (position == 0)//Delete head node
		{
			ਸਿਰ = ਆਰਜ਼ੀ->nptr;
			ਮੁਕਤ(ਆਰਜ਼ੀ);
			ਵਾਪਸ;
		}

		ਲਈ (ਪੂਰਨ i = 0; ਆਰਜ਼ੀ != ਨਿਰਾ && i < position-1; i++)//store previous of to be deleted node
		{
			ਆਰਜ਼ੀ = ਆਰਜ਼ੀ->nptr;
		}

		ਜੇ (ਆਰਜ਼ੀ == ਨਿਰਾ || ਆਰਜ਼ੀ->nptr == ਨਿਰਾ)
			ਵਾਪਸ;

		//delete node at pos (next of position-1)
		ਬਣਤਰ ਗੰਢ *nptr = ਆਰਜ਼ੀ->nptr->nptr;

		ਮੁਕਤ(ਆਰਜ਼ੀ->nptr);
		ਆਰਜ਼ੀ->nptr = nptr; 
	}
}
