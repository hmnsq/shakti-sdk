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

#ଅନ୍ତର୍ଭାଵ <stdio.h>

/** @fn void convert_hex_array()
 * @brief Converts the hex code to an array of hex code
 * @details reads code.mem file and coverts the hex code into an array of hex
 *     codes in the flashdata.h, first entry in the array tells the size of file.
 */
ଶୂନ୍ୟ convert_hex_array()
{
	unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା  i= 0;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା write_data;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2=0;

	FILE *myFile;
	FILE *Cypress;

	myFile = fopen(FILEPATH "/output/code.mem", "r");
	Cypress = fopen(FILEPATH "/output/flashdata.h","w");

	ଯଦି(!myFile) {
		printf(" unable to read code.mem\n");
		ଫେରନ୍ତୁ;
	}

	ଯଦି(!Cypress) {
		printf(" unable to open flashdata.h\n");
		ଫେରନ୍ତୁ;
	}
	
	ଯେତେବେଳେ (fscanf(myFile, "%x", &write_data) != EOF) {
		ଗଣନା_2++;
	}

	rewind(myFile);

	fprintf(Cypress,"unsigned int write_data[%d] = { 0x%x", ଗଣନା_2 + 1, ଗଣନା_2); 

	ଯେତେବେଳେ (fscanf(myFile, "%x", &write_data) != EOF)
	{
		fprintf(Cypress,"\n ,0x%x", write_data);
	}

	fprintf(Cypress,"};\n\n");

	fprintf(Cypress,"#define SIZE %d", ଗଣନା_2);

	fclose(Cypress);
	fclose(myFile);
	printf("\n Converted codemem to array\n");
}
/** @fn void main()
 * @brief Initiates conversion by calling convert_hex_array
 */
ଶୂନ୍ୟ ମୁଖ୍ୟ()
{
	printf(" Converting codemem to array\n");
	convert_hex_array();
}

