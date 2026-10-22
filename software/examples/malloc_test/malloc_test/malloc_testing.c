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

বাহ্য বর্ণ _free_space[];
বাহ্য বর্ণ স্তূপ_SIZE[];
বাহ্য বর্ণ _HEAP_SIZE[];
বাহ্য বর্ণ স্তূপ_end[];
বাহ্য বর্ণ স্তূপ[];
বাহ্য বর্ণ _heap[];
বাহ্য বর্ণ _heap_end[];
বাহ্য বর্ণ __bss_end[];
বাহ্য বর্ণ __bss_start[];
বাহ্য বর্ণ __sbss_end[];
বাহ্য বর্ণ __sbss_start[];


বর্ণ *test1=(বর্ণ *)&_free_space;
বর্ণ *test3=(বর্ণ *)&স্তূপ_SIZE;
বর্ণ *test4=(বর্ণ *)&_HEAP_SIZE;
বর্ণ *test5=(বর্ণ *)&স্তূপ_end;
বর্ণ *test6=(বর্ণ *)&স্তূপ;
বর্ণ *test7=(বর্ণ *)&_heap;
বর্ণ *test8=(বর্ণ *)&_heap_end;
বর্ণ *test9=(বর্ণ *)&__bss_end;
বর্ণ *test10=(বর্ণ *)&__bss_start;
বর্ণ *test11=(বর্ণ *)&__sbss_end;
বর্ণ *test12=(বর্ণ *)&__sbss_start;

পূর্ণাঙ্ক c1,c2,c3,c4,c5;
পূর্ণাঙ্ক *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
পূর্ণাঙ্ক main()
{

  printf("\n\n\n\n\n\nTest Running");
  printf("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  printf("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  স্থির পূর্ণাঙ্ক b1,b2,b3,b4,b5;
  printf("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  পূর্ণাঙ্ক a1,a2,a3,a4,a5;
  printf("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

পূর্ণাঙ্ক **a;
পূর্ণাঙ্ক *b,*c,*d;
পূর্ণাঙ্ক i=0;পূর্ণাঙ্ক n;

//Enter Size of Array;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*পরিমাণ(পূর্ণাঙ্ক))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

printf("\n B's address %x %x",b,&b);
প্রতি(i=0;i<n;i++)
{
  b[i]=i+1;
}

প্রতি(i=0;i<n;i++)
{
    printf("\n b[%d]'s address is : %x",i,&b[i]);
    printf("\n b[%d]'s value is : %d",i,b[i]);
}

মুক্ত(b);

printf("\nArray B is freed");
printf("\nb=%x",b);
printf("\n size of array %d",n);

c=malloc(n*পরিমাণ(পূর্ণাঙ্ক))	;
printf("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

printf("\n C's address %x",c);

প্রতি(i=0;i<n;i++)
{
    c[i]=i+1;
}

প্রতি(i=0;i<n;i++)
{
    printf("\n c[%d]'s address is : %x",i,&c[i]);
    printf("\n c[%d]'s value is : %d",i,c[i]);
}
মুক্ত(c);

printf("\nc=%x",c);

পূর্ণাঙ্ক x;
x=30;

printf("\n\n\nx address is %x",&x);
d=malloc(x*পরিমাণ(পূর্ণাঙ্ক));

printf("\n D's address %x",d);
প্রতি(i=0;i<x;i++)
{
    printf("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

প্রতি(i=0;i<x;i++)
{
    printf("\n d[%d]'s address is : %x",i,&d[i]);
    printf("\n d[%d]'s value is : %d",i,d[i]);
}

মুক্ত(d);

printf("\nd=%x",d);

}
