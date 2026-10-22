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

#ಅನ್ತರ್ಭಾವ "uart.h"
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>

ರಚನೆ ಗಂಟು {
	ಪೂರ್ಣಾಂಕ ಅಂಕೆ;
	ರಚನೆ ಗಂಟು *nptr;
}*ತಲೆ;

ಶೂನ್ಯ create_list(ಪೂರ್ಣಾಂಕ n);
ಶೂನ್ಯ display_list();
ಶೂನ್ಯ delete_ಗಂಟು(ಪೂರ್ಣಾಂಕ position);

/** @fn void main()
 * @brief Get the user input for the linked list creation and deletion. Also displays the linked list.
 * @param[in] int
 * @param[Out] No output parameter
 */
ಶೂನ್ಯ ಮುಖ್ಯ()
{
	ಪೂರ್ಣಾಂಕ n,position,m;
	ಅಕ್ಷರ t[15];
	ಬರೆ("\n Enter the number of nodes on the linked list:\n");

	read_uart_string(uart_instance[0],t);

	n = atoi(t);

	create_list(n);

	ಬರೆ("\n\n\nData entered in the list\n");

	display_list();

	ಬರೆ("\n\n Deletion\n");
	ಬರೆ("\nEnter the Node Position to be Deleted:\n");

	read_uart_string(uart_instance[0],t);

	position = atoi(t);

	delete_ಗಂಟು(position);

	ಬರೆ("\nLinked list after deletion\n");
	display_list();

	ಆಗ(1);
}

/** @fn void create_list(int n) 
 * @brief Creates a linked list with the nodes entered by the user.
 * @param[in] int
 * @param[Out] No output parameter
 */
ಶೂನ್ಯ create_list(ಪೂರ್ಣಾಂಕ n)
{
	ರಚನೆ ಗಂಟು *ಗಂಟು, *tmp;
	ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_2,m;
	ಅಕ್ಷರ t[12];

	ತಲೆ = (ರಚನೆ ಗಂಟು*)ಸ್ಮರಣೆ_ಕೊಡು(ಗಾತ್ರ(ರಚನೆ ಗಂಟು));

	ಆದರೆ(ತಲೆ == ಖಾಲಿ)
	{
		ಬರೆ("\n Memory cannot be allocated");
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
		ಬರೆ("\n\nInput data for node 1:");

		read_uart_string(uart_instance[0],t);

		ದತ್ತಾಂಶ_2 = atoi(t);

		ತಲೆ->ಅಂಕೆ = ದತ್ತಾಂಶ_2;
		ತಲೆ->nptr = ಖಾಲಿ;
		tmp = ತಲೆ;

		ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 2;i <= n; i++)
		{
			ಗಂಟು = (ರಚನೆ ಗಂಟು*)ಸ್ಮರಣೆ_ಕೊಡು(ಗಾತ್ರ(ರಚನೆ ಗಂಟು));

			ಆದರೆ(ಗಂಟು == ಖಾಲಿ)
			{
				ಬರೆ("\n Memory Cannot be allocated");
			}
			ಇಲ್ಲದಿದ್ದರೆ 
			{
				ಬರೆ("\n\nInput Data for node %d :",i);
				read_uart_string(uart_instance[0],t);

				ದತ್ತಾಂಶ_2 = atoi(t);
				ಗಂಟು->ಅಂಕೆ = ದತ್ತಾಂಶ_2;
				ಗಂಟು->nptr = ಖಾಲಿ;

				tmp->nptr = ಗಂಟು;
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
ಶೂನ್ಯ display_list()
{
	ಪೂರ್ಣಾಂಕ i = 0;
	ರಚನೆ ಗಂಟು *tmp;

	ಆದರೆ(ತಲೆ == ಖಾಲಿ)
	{
		ಬರೆ(" List is empty.");
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
		tmp = ತಲೆ;
		ಆಗ(tmp != ಖಾಲಿ) 
		{
			ಬರೆ(" Node%d = %d",i,tmp->ಅಂಕೆ);
			ಬರೆ("->");
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
ಶೂನ್ಯ delete_ಗಂಟು(ಪೂರ್ಣಾಂಕ position)
{
	ರಚನೆ ಗಂಟು *ತಾತ್ಕಾಲಿಕ;

	ಆದರೆ(ತಲೆ == ಖಾಲಿ)
	{
		ಬರೆ(" List is empty.");
	}
	ಇಲ್ಲದಿದ್ದರೆ 
	{
		ತಾತ್ಕಾಲಿಕ = ತಲೆ;

		ಆದರೆ (position == 0)//Delete head node
		{
			ತಲೆ = ತಾತ್ಕಾಲಿಕ->nptr;
			ಬಿಡುಗಡೆ(ತಾತ್ಕಾಲಿಕ);
			ಹಿಂತಿರುಗಿ;
		}

		ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; ತಾತ್ಕಾಲಿಕ != ಖಾಲಿ && i < position-1; i++)//store previous of to be deleted node
		{
			ತಾತ್ಕಾಲಿಕ = ತಾತ್ಕಾಲಿಕ->nptr;
		}

		ಆದರೆ (ತಾತ್ಕಾಲಿಕ == ಖಾಲಿ || ತಾತ್ಕಾಲಿಕ->nptr == ಖಾಲಿ)
			ಹಿಂತಿರುಗಿ;

		//delete node at pos (next of position-1)
		ರಚನೆ ಗಂಟು *nptr = ತಾತ್ಕಾಲಿಕ->nptr->nptr;

		ಬಿಡುಗಡೆ(ತಾತ್ಕಾಲಿಕ->nptr);
		ತಾತ್ಕಾಲಿಕ->nptr = nptr; 
	}
}
