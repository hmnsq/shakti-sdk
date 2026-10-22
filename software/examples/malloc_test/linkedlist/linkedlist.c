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

#అన్తర్భావ "uart.h"
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>

నిర్మాణం కణుపు {
	పూర్ణాంకం అంకె;
	నిర్మాణం కణుపు *nptr;
}*తల;

శూన్య create_list(పూర్ణాంకం n);
శూన్య display_list();
శూన్య delete_కణుపు(పూర్ణాంకం position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
శూన్య ప్రధాన()
{
	పూర్ణాంకం n,position,m;
	అక్షరం t[15];
	రాయి("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = atoi(t);

	create_list(n);

	రాయి("\n\n\nData entered in the list\n");

	display_list();

	రాయి("\n\n Deletion\n");
	రాయి("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = atoi(t);

	delete_కణుపు(position);

	రాయి("\nLinked list after deletion\n");
	display_list();

	అయితే(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
శూన్య create_list(పూర్ణాంకం n)
{
	నిర్మాణం కణుపు *కణుపు, *tmp;
	పూర్ణాంకం దత్తాంశం_2,m;
	అక్షరం t[12];

	తల = (నిర్మాణం కణుపు*)జ్ఞాపకం_ఇవ్వు(పరిమాణం(నిర్మాణం కణుపు));

	ఒకవేళ(తల == ఖాళీ)
	{
		రాయి("\n Memory cannot be allocated");
	}
	లేకపోతే
	{
		రాయి("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		దత్తాంశం_2 = atoi(t);

		తల->అంకె = దత్తాంశం_2;
		తల->nptr = ఖాళీ;
		tmp = తల;

		కొరకు(పూర్ణాంకం i = 2;i <= n; i++)
		{
			కణుపు = (నిర్మాణం కణుపు*)జ్ఞాపకం_ఇవ్వు(పరిమాణం(నిర్మాణం కణుపు));

			ఒకవేళ(కణుపు == ఖాళీ)
			{
				రాయి("\n Memory Cannot be allocated");
			}
			లేకపోతే 
			{
				రాయి("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				దత్తాంశం_2 = atoi(t);
				కణుపు->అంకె = దత్తాంశం_2;
				కణుపు->nptr = ఖాళీ;

				tmp->nptr = కణుపు;
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
శూన్య display_list()
{
	పూర్ణాంకం i = 0;
	నిర్మాణం కణుపు *tmp;

	ఒకవేళ(తల == ఖాళీ)
	{
		రాయి(" List is empty.");
	}
	లేకపోతే
	{
		tmp = తల;
		అయితే(tmp != ఖాళీ) 
		{
			రాయి(" Node%d = %d",i,tmp->అంకె);
			రాయి("->");
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
శూన్య delete_కణుపు(పూర్ణాంకం position)
{
	నిర్మాణం కణుపు *తాత్కాలిక;

	ఒకవేళ(తల == ఖాళీ)
	{
		రాయి(" List is empty.");
	}
	లేకపోతే 
	{
		తాత్కాలిక = తల;

		ఒకవేళ (position == 0)//Delete head node
		{
			తల = తాత్కాలిక->nptr;
			విడుదల(తాత్కాలిక);
			తిరిగి;
		}

		కొరకు (పూర్ణాంకం i = 0; తాత్కాలిక != ఖాళీ && i < position-1; i++)//store previous of to be deleted node
		{
			తాత్కాలిక = తాత్కాలిక->nptr;
		}

		ఒకవేళ (తాత్కాలిక == ఖాళీ || తాత్కాలిక->nptr == ఖాళీ)
			తిరిగి;

		//delete node at pos (next of position-1)
		నిర్మాణం కణుపు *nptr = తాత్కాలిక->nptr->nptr;

		విడుదల(తాత్కాలిక->nptr);
		తాత్కాలిక->nptr = nptr; 
	}
}
