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

خارجي حرف _free_space[];
خارجي حرف ڈھیر_SIZE[];
خارجي حرف _HEAP_SIZE[];
خارجي حرف ڈھیر_end[];
خارجي حرف ڈھیر[];
خارجي حرف _heap[];
خارجي حرف _heap_end[];
خارجي حرف __bss_end[];
خارجي حرف __bss_start[];
خارجي حرف __sbss_end[];
خارجي حرف __sbss_start[];


حرف *test1=(حرف *)&_free_space;
حرف *test3=(حرف *)&ڈھیر_SIZE;
حرف *test4=(حرف *)&_HEAP_SIZE;
حرف *test5=(حرف *)&ڈھیر_end;
حرف *test6=(حرف *)&ڈھیر;
حرف *test7=(حرف *)&_heap;
حرف *test8=(حرف *)&_heap_end;
حرف *test9=(حرف *)&__bss_end;
حرف *test10=(حرف *)&__bss_start;
حرف *test11=(حرف *)&__sbss_end;
حرف *test12=(حرف *)&__sbss_start;

صحيح c1,c2,c3,c4,c5;
صحيح *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
صحيح main()
{

  printf("\n\n\n\n\n\nTest Running");
  printf("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  printf("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  ساكن صحيح b1,b2,b3,b4,b5;
  printf("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  صحيح a1,a2,a3,a4,a5;
  printf("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

صحيح **a;
صحيح *b,*c,*d;
صحيح i=0;صحيح n;

//Enter Size of Array;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*حجم(صحيح))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

printf("\n B's address %x %x",b,&b);
لكل(i=0;i<n;i++)
{
  b[i]=i+1;
}

لكل(i=0;i<n;i++)
{
    printf("\n b[%d]'s address is : %x",i,&b[i]);
    printf("\n b[%d]'s value is : %d",i,b[i]);
}

حرر(b);

printf("\nArray B is freed");
printf("\nb=%x",b);
printf("\n size of array %d",n);

c=malloc(n*حجم(صحيح))	;
printf("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

printf("\n C's address %x",c);

لكل(i=0;i<n;i++)
{
    c[i]=i+1;
}

لكل(i=0;i<n;i++)
{
    printf("\n c[%d]'s address is : %x",i,&c[i]);
    printf("\n c[%d]'s value is : %d",i,c[i]);
}
حرر(c);

printf("\nc=%x",c);

صحيح x;
x=30;

printf("\n\n\nx address is %x",&x);
d=malloc(x*حجم(صحيح));

printf("\n D's address %x",d);
لكل(i=0;i<x;i++)
{
    printf("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

لكل(i=0;i<x;i++)
{
    printf("\n d[%d]'s address is : %x",i,&d[i]);
    printf("\n d[%d]'s value is : %d",i,d[i]);
}

حرر(d);

printf("\nd=%x",d);

}
