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

#include <stdio.h>

/** @fn void convert_hex_array()
 * @brief Converts the hex code to an array of hex code
 * @details reads code.mem file and coverts the hex code into an array of hex
 *     codes in the flashdata.h, first entry in the array tells the size of file.
 */
void convert_hex_array(long int lines_count)
{
	unsigned int  i= 0;
	int write_data;
	int count=0;

	FILE *myFile;
	FILE *Cypress;
	printf("\n Convert code.mem to hex array");
	myFile = fopen("code.mem", "r");
	Cypress = fopen("flashdata.h","w");

	if(!myFile) {
		printf(" unable to read code.mem\n");
		return;
	}

	if(!Cypress) {
		printf(" unable to open flashdata.h\n");
		return;
	}

	while (fscanf(myFile, "%x", &write_data) != EOF) {
		if(0 != lines_count && count == lines_count )
			break;
		count++;
	}
	rewind(myFile);

	fprintf(Cypress,"unsigned int write_data[%d] = { 0x%x", count + 1, count); 
	count = 0;
	while (fscanf(myFile, "%x", &write_data) != EOF)
	{
		fprintf(Cypress,"\n ,0x%x", write_data);
		if(0 != lines_count && count == lines_count )
			break;
		count++;
	}

	fprintf(Cypress,"};\n\n");

	if(0 == lines_count)
		fprintf(Cypress,"#define SIZE %d", count);
	else
		fprintf(Cypress,"#define SIZE %d", lines_count);

	fclose(Cypress);
	fclose(myFile);
	printf("\n Converted codemem to array\n");
}
/** @fn void main()
 * @brief Initiates conversion by calling convert_hex_array
 */
void main(int argc, char *argv[])
{
	int i = 0;	
	long int lines_count = 0;
//	printf(" Converting codemem to array\n");
//	printf("\n no of args: %x", argc);
//	for(i = 0; i < argc; i++)
//		printf("\n argv[%x]: %s", i, argv[i]);
	if(argc == 2)
	{
		lines_count = atol(argv[1]);
		printf("\n No. of Lines: %lx", lines_count);
		convert_hex_array(lines_count);
	}
	else if (argc == 1)
		convert_hex_array(0);
	else
	{
		printf("\n Invalid format");
		printf("\n the format should be ./elf_to_loader or ./elf_to_header lines_count");
	}

}

