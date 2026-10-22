/***************************************************************************
* Project                   	: shakti devt board
* Name of the file	        : malloc_testing.c
* Brief Description of file     : Test for malloc implementation
* Name of Author    	        : Abhinav Ramnath
* Email ID                      : abhinavramnath13@gmail.com

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
 * @file malloc_testing.c
 * @brief Test code for malloc testing
 * @detail This file contains the tests to verify the working of malloc
 */

ബാഹ്യ അക്ഷരം _free_space[];
ബാഹ്യ അക്ഷരം അട്ടി_SIZE[];
ബാഹ്യ അക്ഷരം _HEAP_SIZE[];
ബാഹ്യ അക്ഷരം അട്ടി_end[];
ബാഹ്യ അക്ഷരം അട്ടി[];
ബാഹ്യ അക്ഷരം _heap[];
ബാഹ്യ അക്ഷരം _heap_end[];
ബാഹ്യ അക്ഷരം __bss_end[];
ബാഹ്യ അക്ഷരം __bss_start[];
ബാഹ്യ അക്ഷരം __sbss_end[];
ബാഹ്യ അക്ഷരം __sbss_start[];


അക്ഷരം *test1=(അക്ഷരം *)&_free_space;
അക്ഷരം *test3=(അക്ഷരം *)&അട്ടി_SIZE;
അക്ഷരം *test4=(അക്ഷരം *)&_HEAP_SIZE;
അക്ഷരം *test5=(അക്ഷരം *)&അട്ടി_end;
അക്ഷരം *test6=(അക്ഷരം *)&അട്ടി;
അക്ഷരം *test7=(അക്ഷരം *)&_heap;
അക്ഷരം *test8=(അക്ഷരം *)&_heap_end;
അക്ഷരം *test9=(അക്ഷരം *)&__bss_end;
അക്ഷരം *test10=(അക്ഷരം *)&__bss_start;
അക്ഷരം *test11=(അക്ഷരം *)&__sbss_end;
അക്ഷരം *test12=(അക്ഷരം *)&__sbss_start;

പൂർണ്ണസംഖ്യ c1,c2,c3,c4,c5;
പൂർണ്ണസംഖ്യ *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
പൂർണ്ണസംഖ്യ പ്രധാന()
{

  printf("\n\n\n\n\n\nTest Running");
  printf("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  printf("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  സ്ഥിതം പൂർണ്ണസംഖ്യ b1,b2,b3,b4,b5;
  printf("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  പൂർണ്ണസംഖ്യ a1,a2,a3,a4,a5;
  printf("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

പൂർണ്ണസംഖ്യ **a;
പൂർണ്ണസംഖ്യ *b,*c,*d;
പൂർണ്ണസംഖ്യ i=0;പൂർണ്ണസംഖ്യ n;

//Enter Size of Array;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*വലുപ്പം(പൂർണ്ണസംഖ്യ))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

printf("\n B's address %x %x",b,&b);
വേണ്ടി(i=0;i<n;i++)
{
  b[i]=i+1;
}

വേണ്ടി(i=0;i<n;i++)
{
    printf("\n b[%d]'s address is : %x",i,&b[i]);
    printf("\n b[%d]'s value is : %d",i,b[i]);
}

സ്വതന്ത്രം(b);

printf("\nArray B is freed");
printf("\nb=%x",b);
printf("\n size of array %d",n);

c=malloc(n*വലുപ്പം(പൂർണ്ണസംഖ്യ))	;
printf("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

printf("\n C's address %x",c);

വേണ്ടി(i=0;i<n;i++)
{
    c[i]=i+1;
}

വേണ്ടി(i=0;i<n;i++)
{
    printf("\n c[%d]'s address is : %x",i,&c[i]);
    printf("\n c[%d]'s value is : %d",i,c[i]);
}
സ്വതന്ത്രം(c);

printf("\nc=%x",c);

പൂർണ്ണസംഖ്യ x;
x=30;

printf("\n\n\nx address is %x",&x);
d=malloc(x*വലുപ്പം(പൂർണ്ണസംഖ്യ));

printf("\n D's address %x",d);
വേണ്ടി(i=0;i<x;i++)
{
    printf("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

വേണ്ടി(i=0;i<x;i++)
{
    printf("\n d[%d]'s address is : %x",i,&d[i]);
    printf("\n d[%d]'s value is : %d",i,d[i]);
}

സ്വതന്ത്രം(d);

printf("\nd=%x",d);

}
