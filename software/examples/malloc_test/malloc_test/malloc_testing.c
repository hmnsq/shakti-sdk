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

بیرونی نویسه _free_space[];
بیرونی نویسه پشته_SIZE[];
بیرونی نویسه _HEAP_SIZE[];
بیرونی نویسه پشته_end[];
بیرونی نویسه پشته[];
بیرونی نویسه _heap[];
بیرونی نویسه _heap_end[];
بیرونی نویسه __bss_end[];
بیرونی نویسه __bss_start[];
بیرونی نویسه __sbss_end[];
بیرونی نویسه __sbss_start[];


نویسه *test1=(نویسه *)&_free_space;
نویسه *test3=(نویسه *)&پشته_SIZE;
نویسه *test4=(نویسه *)&_HEAP_SIZE;
نویسه *test5=(نویسه *)&پشته_end;
نویسه *test6=(نویسه *)&پشته;
نویسه *test7=(نویسه *)&_heap;
نویسه *test8=(نویسه *)&_heap_end;
نویسه *test9=(نویسه *)&__bss_end;
نویسه *test10=(نویسه *)&__bss_start;
نویسه *test11=(نویسه *)&__sbss_end;
نویسه *test12=(نویسه *)&__sbss_start;

صحیح c1,c2,c3,c4,c5;
صحیح *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
صحیح اصلی()
{

  printf("\n\n\n\n\n\nTest Running");
  printf("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  printf("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  ایستا صحیح b1,b2,b3,b4,b5;
  printf("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  صحیح a1,a2,a3,a4,a5;
  printf("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

صحیح **a;
صحیح *b,*c,*d;
صحیح i=0;صحیح n;

//Enter Size of Array;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*اندازه(صحیح))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

printf("\n B's address %x %x",b,&b);
برای(i=0;i<n;i++)
{
  b[i]=i+1;
}

برای(i=0;i<n;i++)
{
    printf("\n b[%d]'s address is : %x",i,&b[i]);
    printf("\n b[%d]'s value is : %d",i,b[i]);
}

آزاد(b);

printf("\nArray B is freed");
printf("\nb=%x",b);
printf("\n size of array %d",n);

c=malloc(n*اندازه(صحیح))	;
printf("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

printf("\n C's address %x",c);

برای(i=0;i<n;i++)
{
    c[i]=i+1;
}

برای(i=0;i<n;i++)
{
    printf("\n c[%d]'s address is : %x",i,&c[i]);
    printf("\n c[%d]'s value is : %d",i,c[i]);
}
آزاد(c);

printf("\nc=%x",c);

صحیح x;
x=30;

printf("\n\n\nx address is %x",&x);
d=malloc(x*اندازه(صحیح));

printf("\n D's address %x",d);
برای(i=0;i<x;i++)
{
    printf("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

برای(i=0;i<x;i++)
{
    printf("\n d[%d]'s address is : %x",i,&d[i]);
    printf("\n d[%d]'s value is : %d",i,d[i]);
}

آزاد(d);

printf("\nd=%x",d);

}
