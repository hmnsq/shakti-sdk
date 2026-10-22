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

#समावेश "uart.h"
#समावेश <stdio.h>
#समावेश <stdlib.h>

काष्ठा गाँठ {
	पूर्णांक अंक;
	काष्ठा गाँठ *nptr;
}*शीर्ष;

व्योम create_list(पूर्णांक n);
व्योम display_list();
व्योम delete_गाँठ(पूर्णांक position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
व्योम मुख्य()
{
	पूर्णांक n,position,m;
	अक्षर t[15];
	म_लिखो("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = म_से_प(t);

	create_list(n);

	म_लिखो("\n\n\nData entered in the list\n");

	display_list();

	म_लिखो("\n\n Deletion\n");
	म_लिखो("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = म_से_प(t);

	delete_गाँठ(position);

	म_लिखो("\nLinked list after deletion\n");
	display_list();

	जबतक(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
व्योम create_list(पूर्णांक n)
{
	काष्ठा गाँठ *गाँठ, *tmp;
	पूर्णांक तथ्य_2,m;
	अक्षर t[12];

	शीर्ष = (काष्ठा गाँठ*)दो_स्मृति(माप(काष्ठा गाँठ));

	अगर(शीर्ष == शून्य)
	{
		म_लिखो("\n Memory cannot be allocated");
	}
	अन्यथा
	{
		म_लिखो("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		तथ्य_2 = म_से_प(t);

		शीर्ष->अंक = तथ्य_2;
		शीर्ष->nptr = शून्य;
		tmp = शीर्ष;

		क्रम(पूर्णांक i = 2;i <= n; i++)
		{
			गाँठ = (काष्ठा गाँठ*)दो_स्मृति(माप(काष्ठा गाँठ));

			अगर(गाँठ == शून्य)
			{
				म_लिखो("\n Memory Cannot be allocated");
			}
			अन्यथा 
			{
				म_लिखो("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				तथ्य_2 = म_से_प(t);
				गाँठ->अंक = तथ्य_2;
				गाँठ->nptr = शून्य;

				tmp->nptr = गाँठ;
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
व्योम display_list()
{
	पूर्णांक i = 0;
	काष्ठा गाँठ *tmp;

	अगर(शीर्ष == शून्य)
	{
		म_लिखो(" List is empty.");
	}
	अन्यथा
	{
		tmp = शीर्ष;
		जबतक(tmp != शून्य) 
		{
			म_लिखो(" Node%d = %d",i,tmp->अंक);
			म_लिखो("->");
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
व्योम delete_गाँठ(पूर्णांक position)
{
	काष्ठा गाँठ *अस्थायी;

	अगर(शीर्ष == शून्य)
	{
		म_लिखो(" List is empty.");
	}
	अन्यथा 
	{
		अस्थायी = शीर्ष;

		अगर (position == 0)//Delete head node
		{
			शीर्ष = अस्थायी->nptr;
			मुक्त(अस्थायी);
			वापस;
		}

		क्रम (पूर्णांक i = 0; अस्थायी != शून्य && i < position-1; i++)//store previous of to be deleted node
		{
			अस्थायी = अस्थायी->nptr;
		}

		अगर (अस्थायी == शून्य || अस्थायी->nptr == शून्य)
			वापस;

		//delete node at pos (next of position-1)
		काष्ठा गाँठ *nptr = अस्थायी->nptr->nptr;

		मुक्त(अस्थायी->nptr);
		अस्थायी->nptr = nptr; 
	}
}
