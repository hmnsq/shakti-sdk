/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  elf_to_header.c
* Brief Description of file             :  Create hex array of the contents in elf.
* Name of Author    	                :  Sathya Narayanan N & & Anand Kumar S
* Email ID                              :  sathya281@gmail.com

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
/**
@file elf_to_header.c
@brief Create hex array of the contents in elf.
*/

#अन्तर्भाव <stdio.h>

/** @fn void convert_hex_array()
 * @brief Converts the hex code to an array of hex code
 * @details reads code.mem file and coverts the hex code into an array of hex
 *     codes in the flashdata.h, first entry in the array tells the size of file.
 */
शून्य convert_hex_array()
{
	अचिन्हित पूर्णाङ्क  i= 0;
	पूर्णाङ्क write_data;
	पूर्णाङ्क गिनती=0;

	खाता *myFile;
	खाता *Cypress;

	myFile = ख_खोलो(FILEPATH "/output/code.mem", "r");
	Cypress = ख_खोलो(FILEPATH "/output/flashdata.h","w");

	यदि(!myFile) {
		म_लिखो(" unable to read code.mem\n");
		प्रत्यागम;
	}

	यदि(!Cypress) {
		म_लिखो(" unable to open flashdata.h\n");
		प्रत्यागम;
	}
	
	यावत् (ख_पूछो(myFile, "%x", &write_data) != खातापूर्ण) {
		गिनती++;
	}

	शुरुआत(myFile);

	ख_लिखो(Cypress,"unsigned int write_data[%d] = { 0x%x", गिनती + 1, गिनती); 

	यावत् (ख_पूछो(myFile, "%x", &write_data) != खातापूर्ण)
	{
		ख_लिखो(Cypress,"\n ,0x%x", write_data);
	}

	ख_लिखो(Cypress,"};\n\n");

	ख_लिखो(Cypress,"#define SIZE %d", गिनती);

	ख_बंद(Cypress);
	ख_बंद(myFile);
	म_लिखो("\n Converted codemem to array\n");
}
/** @fn void main()
 * @brief Initiates conversion by calling convert_hex_array
 */
शून्य main()
{
	म_लिखो(" Converting codemem to array\n");
	convert_hex_array();
}

