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

ಬಾಹ್ಯ ವರ್ಣ _free_space[];
ಬಾಹ್ಯ ವರ್ಣ ರಾಶಿ_SIZE[];
ಬಾಹ್ಯ ವರ್ಣ _HEAP_SIZE[];
ಬಾಹ್ಯ ವರ್ಣ ರಾಶಿ_end[];
ಬಾಹ್ಯ ವರ್ಣ ರಾಶಿ[];
ಬಾಹ್ಯ ವರ್ಣ _heap[];
ಬಾಹ್ಯ ವರ್ಣ _heap_end[];
ಬಾಹ್ಯ ವರ್ಣ __bss_end[];
ಬಾಹ್ಯ ವರ್ಣ __bss_start[];
ಬಾಹ್ಯ ವರ್ಣ __sbss_end[];
ಬಾಹ್ಯ ವರ್ಣ __sbss_start[];


ವರ್ಣ *test1=(ವರ್ಣ *)&_free_space;
ವರ್ಣ *test3=(ವರ್ಣ *)&ರಾಶಿ_SIZE;
ವರ್ಣ *test4=(ವರ್ಣ *)&_HEAP_SIZE;
ವರ್ಣ *test5=(ವರ್ಣ *)&ರಾಶಿ_end;
ವರ್ಣ *test6=(ವರ್ಣ *)&ರಾಶಿ;
ವರ್ಣ *test7=(ವರ್ಣ *)&_heap;
ವರ್ಣ *test8=(ವರ್ಣ *)&_heap_end;
ವರ್ಣ *test9=(ವರ್ಣ *)&__bss_end;
ವರ್ಣ *test10=(ವರ್ಣ *)&__bss_start;
ವರ್ಣ *test11=(ವರ್ಣ *)&__sbss_end;
ವರ್ಣ *test12=(ವರ್ಣ *)&__sbss_start;

ಪೂರ್ಣಾಙ್ಕ c1,c2,c3,c4,c5;
ಪೂರ್ಣಾಙ್ಕ *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
ಪೂರ್ಣಾಙ್ಕ main()
{

  printf("\n\n\n\n\n\nTest Running");
  printf("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  printf("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ b1,b2,b3,b4,b5;
  printf("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  ಪೂರ್ಣಾಙ್ಕ a1,a2,a3,a4,a5;
  printf("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

ಪೂರ್ಣಾಙ್ಕ **a;
ಪೂರ್ಣಾಙ್ಕ *b,*c,*d;
ಪೂರ್ಣಾಙ್ಕ i=0;ಪೂರ್ಣಾಙ್ಕ n;

//Enter Size of Array;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

printf("\n B's address %x %x",b,&b);
ಪ್ರತಿ(i=0;i<n;i++)
{
  b[i]=i+1;
}

ಪ್ರತಿ(i=0;i<n;i++)
{
    printf("\n b[%d]'s address is : %x",i,&b[i]);
    printf("\n b[%d]'s value is : %d",i,b[i]);
}

ಮುಕ್ತ(b);

printf("\nArray B is freed");
printf("\nb=%x",b);
printf("\n size of array %d",n);

c=malloc(n*ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ))	;
printf("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

printf("\n C's address %x",c);

ಪ್ರತಿ(i=0;i<n;i++)
{
    c[i]=i+1;
}

ಪ್ರತಿ(i=0;i<n;i++)
{
    printf("\n c[%d]'s address is : %x",i,&c[i]);
    printf("\n c[%d]'s value is : %d",i,c[i]);
}
ಮುಕ್ತ(c);

printf("\nc=%x",c);

ಪೂರ್ಣಾಙ್ಕ x;
x=30;

printf("\n\n\nx address is %x",&x);
d=malloc(x*ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ));

printf("\n D's address %x",d);
ಪ್ರತಿ(i=0;i<x;i++)
{
    printf("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

ಪ್ರತಿ(i=0;i<x;i++)
{
    printf("\n d[%d]'s address is : %x",i,&d[i]);
    printf("\n d[%d]'s value is : %d",i,d[i]);
}

ಮುಕ್ತ(d);

printf("\nd=%x",d);

}
