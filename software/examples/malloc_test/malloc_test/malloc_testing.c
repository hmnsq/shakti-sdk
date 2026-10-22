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

বাহ্যিক অক্ষর _free_space[];
বাহ্যিক অক্ষর স্তূপ_আকার[];
বাহ্যিক অক্ষর HEAP_আকার[];
বাহ্যিক অক্ষর স্তূপ_end[];
বাহ্যিক অক্ষর স্তূপ[];
বাহ্যিক অক্ষর _heap[];
বাহ্যিক অক্ষর _heap_end[];
বাহ্যিক অক্ষর __bss_end[];
বাহ্যিক অক্ষর __bss_start[];
বাহ্যিক অক্ষর __sbss_end[];
বাহ্যিক অক্ষর __sbss_start[];


অক্ষর *test1=(অক্ষর *)&_free_space;
অক্ষর *test3=(অক্ষর *)&স্তূপ_আকার;
অক্ষর *test4=(অক্ষর *)&HEAP_আকার;
অক্ষর *test5=(অক্ষর *)&স্তূপ_end;
অক্ষর *test6=(অক্ষর *)&স্তূপ;
অক্ষর *test7=(অক্ষর *)&_heap;
অক্ষর *test8=(অক্ষর *)&_heap_end;
অক্ষর *test9=(অক্ষর *)&__bss_end;
অক্ষর *test10=(অক্ষর *)&__bss_start;
অক্ষর *test11=(অক্ষর *)&__sbss_end;
অক্ষর *test12=(অক্ষর *)&__sbss_start;

পূর্ণসংখ্যা c1,c2,c3,c4,c5;
পূর্ণসংখ্যা *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
পূর্ণসংখ্যা প্রধান()
{

  printf("\n\n\n\n\n\nTest Running");
  printf("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  printf("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  স্থির পূর্ণসংখ্যা b1,b2,b3,b4,b5;
  printf("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  পূর্ণসংখ্যা a1,a2,a3,a4,a5;
  printf("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

পূর্ণসংখ্যা **a;
পূর্ণসংখ্যা *b,*c,*d;
পূর্ণসংখ্যা i=0;পূর্ণসংখ্যা n;

//Enter Size of Array;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*আকার(পূর্ণসংখ্যা))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

printf("\n B's address %x %x",b,&b);
জন্য(i=0;i<n;i++)
{
  b[i]=i+1;
}

জন্য(i=0;i<n;i++)
{
    printf("\n b[%d]'s address is : %x",i,&b[i]);
    printf("\n b[%d]'s value is : %d",i,b[i]);
}

মুক্ত(b);

printf("\nArray B is freed");
printf("\nb=%x",b);
printf("\n size of array %d",n);

c=malloc(n*আকার(পূর্ণসংখ্যা))	;
printf("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

printf("\n C's address %x",c);

জন্য(i=0;i<n;i++)
{
    c[i]=i+1;
}

জন্য(i=0;i<n;i++)
{
    printf("\n c[%d]'s address is : %x",i,&c[i]);
    printf("\n c[%d]'s value is : %d",i,c[i]);
}
মুক্ত(c);

printf("\nc=%x",c);

পূর্ণসংখ্যা x;
x=30;

printf("\n\n\nx address is %x",&x);
d=malloc(x*আকার(পূর্ণসংখ্যা));

printf("\n D's address %x",d);
জন্য(i=0;i<x;i++)
{
    printf("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

জন্য(i=0;i<x;i++)
{
    printf("\n d[%d]'s address is : %x",i,&d[i]);
    printf("\n d[%d]'s value is : %d",i,d[i]);
}

মুক্ত(d);

printf("\nd=%x",d);

}
