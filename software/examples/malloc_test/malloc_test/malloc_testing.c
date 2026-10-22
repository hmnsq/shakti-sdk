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

வெளி எழுத்து _free_space[];
வெளி எழுத்து அடுக்கு_SIZE[];
வெளி எழுத்து _HEAP_SIZE[];
வெளி எழுத்து அடுக்கு_end[];
வெளி எழுத்து அடுக்கு[];
வெளி எழுத்து _heap[];
வெளி எழுத்து _heap_end[];
வெளி எழுத்து __bss_end[];
வெளி எழுத்து __bss_start[];
வெளி எழுத்து __sbss_end[];
வெளி எழுத்து __sbss_start[];


எழுத்து *test1=(எழுத்து *)&_free_space;
எழுத்து *test3=(எழுத்து *)&அடுக்கு_SIZE;
எழுத்து *test4=(எழுத்து *)&_HEAP_SIZE;
எழுத்து *test5=(எழுத்து *)&அடுக்கு_end;
எழுத்து *test6=(எழுத்து *)&அடுக்கு;
எழுத்து *test7=(எழுத்து *)&_heap;
எழுத்து *test8=(எழுத்து *)&_heap_end;
எழுத்து *test9=(எழுத்து *)&__bss_end;
எழுத்து *test10=(எழுத்து *)&__bss_start;
எழுத்து *test11=(எழுத்து *)&__sbss_end;
எழுத்து *test12=(எழுத்து *)&__sbss_start;

முழு c1,c2,c3,c4,c5;
முழு *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
முழு முதன்மை()
{

  printf("\n\n\n\n\n\nTest Running");
  printf("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  printf("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  நிலையான முழு b1,b2,b3,b4,b5;
  printf("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  முழு a1,a2,a3,a4,a5;
  printf("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

முழு **a;
முழு *b,*c,*d;
முழு i=0;முழு n;

//Enter Size of Array;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*அளவு(முழு))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

printf("\n B's address %x %x",b,&b);
க்கு(i=0;i<n;i++)
{
  b[i]=i+1;
}

க்கு(i=0;i<n;i++)
{
    printf("\n b[%d]'s address is : %x",i,&b[i]);
    printf("\n b[%d]'s value is : %d",i,b[i]);
}

விடுவி(b);

printf("\nArray B is freed");
printf("\nb=%x",b);
printf("\n size of array %d",n);

c=malloc(n*அளவு(முழு))	;
printf("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

printf("\n C's address %x",c);

க்கு(i=0;i<n;i++)
{
    c[i]=i+1;
}

க்கு(i=0;i<n;i++)
{
    printf("\n c[%d]'s address is : %x",i,&c[i]);
    printf("\n c[%d]'s value is : %d",i,c[i]);
}
விடுவி(c);

printf("\nc=%x",c);

முழு x;
x=30;

printf("\n\n\nx address is %x",&x);
d=malloc(x*அளவு(முழு));

printf("\n D's address %x",d);
க்கு(i=0;i<x;i++)
{
    printf("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

க்கு(i=0;i<x;i++)
{
    printf("\n d[%d]'s address is : %x",i,&d[i]);
    printf("\n d[%d]'s value is : %d",i,d[i]);
}

விடுவி(d);

printf("\nd=%x",d);

}
