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

ବାହ୍ୟ ଅକ୍ଷର _free_space[];
ବାହ୍ୟ ଅକ୍ଷର ଗଦା_SIZE[];
ବାହ୍ୟ ଅକ୍ଷର _HEAP_SIZE[];
ବାହ୍ୟ ଅକ୍ଷର ଗଦା_end[];
ବାହ୍ୟ ଅକ୍ଷର ଗଦା[];
ବାହ୍ୟ ଅକ୍ଷର _heap[];
ବାହ୍ୟ ଅକ୍ଷର _heap_end[];
ବାହ୍ୟ ଅକ୍ଷର __bss_end[];
ବାହ୍ୟ ଅକ୍ଷର __bss_start[];
ବାହ୍ୟ ଅକ୍ଷର __sbss_end[];
ବାହ୍ୟ ଅକ୍ଷର __sbss_start[];


ଅକ୍ଷର *test1=(ଅକ୍ଷର *)&_free_space;
ଅକ୍ଷର *test3=(ଅକ୍ଷର *)&ଗଦା_SIZE;
ଅକ୍ଷର *test4=(ଅକ୍ଷର *)&_HEAP_SIZE;
ଅକ୍ଷର *test5=(ଅକ୍ଷର *)&ଗଦା_end;
ଅକ୍ଷର *test6=(ଅକ୍ଷର *)&ଗଦା;
ଅକ୍ଷର *test7=(ଅକ୍ଷର *)&_heap;
ଅକ୍ଷର *test8=(ଅକ୍ଷର *)&_heap_end;
ଅକ୍ଷର *test9=(ଅକ୍ଷର *)&__bss_end;
ଅକ୍ଷର *test10=(ଅକ୍ଷର *)&__bss_start;
ଅକ୍ଷର *test11=(ଅକ୍ଷର *)&__sbss_end;
ଅକ୍ଷର *test12=(ଅକ୍ଷର *)&__sbss_start;

ପୂର୍ଣ୍ଣସଂଖ୍ୟା c1,c2,c3,c4,c5;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ()
{

  printf("\n\n\n\n\n\nTest Running");
  printf("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  printf("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା b1,b2,b3,b4,b5;
  printf("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା a1,a2,a3,a4,a5;
  printf("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

ପୂର୍ଣ୍ଣସଂଖ୍ୟା **a;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା *b,*c,*d;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା i=0;ପୂର୍ଣ୍ଣସଂଖ୍ୟା n;

//Enter Size of Array;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

printf("\n B's address %x %x",b,&b);
ପାଇଁ(i=0;i<n;i++)
{
  b[i]=i+1;
}

ପାଇଁ(i=0;i<n;i++)
{
    printf("\n b[%d]'s address is : %x",i,&b[i]);
    printf("\n b[%d]'s value is : %d",i,b[i]);
}

ମୁକ୍ତ(b);

printf("\nArray B is freed");
printf("\nb=%x",b);
printf("\n size of array %d",n);

c=malloc(n*ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା))	;
printf("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

printf("\n C's address %x",c);

ପାଇଁ(i=0;i<n;i++)
{
    c[i]=i+1;
}

ପାଇଁ(i=0;i<n;i++)
{
    printf("\n c[%d]'s address is : %x",i,&c[i]);
    printf("\n c[%d]'s value is : %d",i,c[i]);
}
ମୁକ୍ତ(c);

printf("\nc=%x",c);

ପୂର୍ଣ୍ଣସଂଖ୍ୟା x;
x=30;

printf("\n\n\nx address is %x",&x);
d=malloc(x*ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା));

printf("\n D's address %x",d);
ପାଇଁ(i=0;i<x;i++)
{
    printf("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

ପାଇଁ(i=0;i<x;i++)
{
    printf("\n d[%d]'s address is : %x",i,&d[i]);
    printf("\n d[%d]'s value is : %d",i,d[i]);
}

ମୁକ୍ତ(d);

printf("\nd=%x",d);

}
