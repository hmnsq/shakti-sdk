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
}*शीर्ष;

शून्य create_list(पूर्णाङ्क n);
शून्य display_list();
शून्य delete_ग्रन्थिः(पूर्णाङ्क position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
शून्य मुख्यम्()
{
	पूर्णाङ्क n,position,m;
	वर्ण t[15];
	प्रारूप_लिख("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = atoi(t);

	create_list(n);

	प्रारूप_लिख("\n\n\nData entered in the list\n");

	display_list();

	प्रारूप_लिख("\n\n Deletion\n");
	प्रारूप_लिख("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = atoi(t);

	delete_ग्रन्थिः(position);

	प्रारूप_लिख("\nLinked list after deletion\n");
	display_list();

	यावत्(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
शून्य create_list(पूर्णाङ्क n)
{
	संरचना ग्रन्थिः *ग्रन्थिः, *tmp;
	पूर्णाङ्क दत्त_2,m;
	वर्ण t[12];

	शीर्ष = (संरचना ग्रन्थिः*)स्मृतिं_देहि(परिमाण(संरचना ग्रन्थिः));

	यदि(शीर्ष == रिक्त)
	{
		प्रारूप_लिख("\n Memory cannot be allocated");
	}
	अन्यथा
	{
		प्रारूप_लिख("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		दत्त_2 = atoi(t);

		शीर्ष->अङ्कः = दत्त_2;
		शीर्ष->nptr = रिक्त;
		tmp = शीर्ष;

		प्रति(पूर्णाङ्क i = 2;i <= n; i++)
		{
			ग्रन्थिः = (संरचना ग्रन्थिः*)स्मृतिं_देहि(परिमाण(संरचना ग्रन्थिः));

			यदि(ग्रन्थिः == रिक्त)
			{
				प्रारूप_लिख("\n Memory Cannot be allocated");
			}
			अन्यथा 
			{
				प्रारूप_लिख("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				दत्त_2 = atoi(t);
				ग्रन्थिः->अङ्कः = दत्त_2;
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

	यदि(शीर्ष == रिक्त)
	{
		प्रारूप_लिख(" List is empty.");
	}
	अन्यथा
	{
		tmp = शीर्ष;
		यावत्(tmp != रिक्त) 
		{
			प्रारूप_लिख(" Node%d = %d",i,tmp->अङ्कः);
			प्रारूप_लिख("->");
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
	संरचना ग्रन्थिः *अस्थायी;

	यदि(शीर्ष == रिक्त)
	{
		प्रारूप_लिख(" List is empty.");
	}
	अन्यथा 
	{
		अस्थायी = शीर्ष;

		यदि (position == 0)//Delete head node
		{
			शीर्ष = अस्थायी->nptr;
			मुक्त(अस्थायी);
			प्रत्यागम;
		}

		प्रति (पूर्णाङ्क i = 0; अस्थायी != रिक्त && i < position-1; i++)//store previous of to be deleted node
		{
			अस्थायी = अस्थायी->nptr;
		}

		यदि (अस्थायी == रिक्त || अस्थायी->nptr == रिक्त)
			प्रत्यागम;

		//delete node at pos (next of position-1)
		संरचना ग्रन्थिः *nptr = अस्थायी->nptr->nptr;

		मुक्त(अस्थायी->nptr);
		अस्थायी->nptr = nptr; 
	}
}
