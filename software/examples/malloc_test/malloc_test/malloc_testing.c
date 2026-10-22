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

બાહ્ય અક્ષર _free_space[];
બાહ્ય અક્ષર ઢગલો_SIZE[];
બાહ્ય અક્ષર _HEAP_SIZE[];
બાહ્ય અક્ષર ઢગલો_end[];
બાહ્ય અક્ષર ઢગલો[];
બાહ્ય અક્ષર _heap[];
બાહ્ય અક્ષર _heap_end[];
બાહ્ય અક્ષર __bss_end[];
બાહ્ય અક્ષર __bss_start[];
બાહ્ય અક્ષર __sbss_end[];
બાહ્ય અક્ષર __sbss_start[];


અક્ષર *test1=(અક્ષર *)&_free_space;
અક્ષર *test3=(અક્ષર *)&ઢગલો_SIZE;
અક્ષર *test4=(અક્ષર *)&_HEAP_SIZE;
અક્ષર *test5=(અક્ષર *)&ઢગલો_end;
અક્ષર *test6=(અક્ષર *)&ઢગલો;
અક્ષર *test7=(અક્ષર *)&_heap;
અક્ષર *test8=(અક્ષર *)&_heap_end;
અક્ષર *test9=(અક્ષર *)&__bss_end;
અક્ષર *test10=(અક્ષર *)&__bss_start;
અક્ષર *test11=(અક્ષર *)&__sbss_end;
અક્ષર *test12=(અક્ષર *)&__sbss_start;

પૂર્ણાંક c1,c2,c3,c4,c5;
પૂર્ણાંક *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
પૂર્ણાંક મુખ્ય()
{

  printf("\n\n\n\n\n\nTest Running");
  printf("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  printf("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  સ્થિર પૂર્ણાંક b1,b2,b3,b4,b5;
  printf("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  પૂર્ણાંક a1,a2,a3,a4,a5;
  printf("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

પૂર્ણાંક **a;
પૂર્ણાંક *b,*c,*d;
પૂર્ણાંક i=0;પૂર્ણાંક n;

//Enter Size of Array;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*કદ(પૂર્ણાંક))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

printf("\n B's address %x %x",b,&b);
માટે(i=0;i<n;i++)
{
  b[i]=i+1;
}

માટે(i=0;i<n;i++)
{
    printf("\n b[%d]'s address is : %x",i,&b[i]);
    printf("\n b[%d]'s value is : %d",i,b[i]);
}

મુક્ત(b);

printf("\nArray B is freed");
printf("\nb=%x",b);
printf("\n size of array %d",n);

c=malloc(n*કદ(પૂર્ણાંક))	;
printf("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

printf("\n C's address %x",c);

માટે(i=0;i<n;i++)
{
    c[i]=i+1;
}

માટે(i=0;i<n;i++)
{
    printf("\n c[%d]'s address is : %x",i,&c[i]);
    printf("\n c[%d]'s value is : %d",i,c[i]);
}
મુક્ત(c);

printf("\nc=%x",c);

પૂર્ણાંક x;
x=30;

printf("\n\n\nx address is %x",&x);
d=malloc(x*કદ(પૂર્ણાંક));

printf("\n D's address %x",d);
માટે(i=0;i<x;i++)
{
    printf("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

માટે(i=0;i<x;i++)
{
    printf("\n d[%d]'s address is : %x",i,&d[i]);
    printf("\n d[%d]'s value is : %d",i,d[i]);
}

મુક્ત(d);

printf("\nd=%x",d);

}
