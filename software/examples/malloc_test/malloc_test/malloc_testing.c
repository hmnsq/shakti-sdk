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

ਬਾਹਰੀ ਅੱਖਰ _free_space[];
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ_ਮਾਪ_3[];
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ_ਮਾਪ[];
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ_ਸਿਰਾ[];
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ[];
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ_2[];
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ_ਸਿਰਾ_2[];
ਬਾਹਰੀ ਅੱਖਰ __bss_end[];
ਬਾਹਰੀ ਅੱਖਰ __bss_start[];
ਬਾਹਰੀ ਅੱਖਰ __sbss_end[];
ਬਾਹਰੀ ਅੱਖਰ __sbss_start[];


ਅੱਖਰ *test1=(ਅੱਖਰ *)&_free_space;
ਅੱਖਰ *test3=(ਅੱਖਰ *)&ਢੇਰ_ਮਾਪ_3;
ਅੱਖਰ *test4=(ਅੱਖਰ *)&ਢੇਰ_ਮਾਪ;
ਅੱਖਰ *test5=(ਅੱਖਰ *)&ਢੇਰ_ਸਿਰਾ;
ਅੱਖਰ *test6=(ਅੱਖਰ *)&ਢੇਰ;
ਅੱਖਰ *test7=(ਅੱਖਰ *)&ਢੇਰ_2;
ਅੱਖਰ *test8=(ਅੱਖਰ *)&ਢੇਰ_ਸਿਰਾ_2;
ਅੱਖਰ *test9=(ਅੱਖਰ *)&__bss_end;
ਅੱਖਰ *test10=(ਅੱਖਰ *)&__bss_start;
ਅੱਖਰ *test11=(ਅੱਖਰ *)&__sbss_end;
ਅੱਖਰ *test12=(ਅੱਖਰ *)&__sbss_start;

ਪੂਰਨ c1,c2,c3,c4,c5;
ਪੂਰਨ *ਸੂਚਕ;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
ਪੂਰਨ ਮੁੱਖ()
{

  ਲਿਖੋ("\n\n\n\n\n\nTest Running");
  ਲਿਖੋ("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  ਲਿਖੋ("\n %x %d %x %x %x %x %x",&ਸੂਚਕ,c1,&c1,&c2,&c3,&c4,&c5);
  
  ਸਥਿਰ ਪੂਰਨ b1,b2,b3,b4,b5;
  ਲਿਖੋ("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  ਪੂਰਨ a1,a2,a3,a4,a5;
  ਲਿਖੋ("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

ਪੂਰਨ **a;
ਪੂਰਨ *b,*c,*d;
ਪੂਰਨ i=0;ਪੂਰਨ n;

//Enter Size of Array;
n= 25;
ਲਿਖੋ("\n size of array %d %x",n,&n);
b=ਸਮ੍ਰਿਤੀ_ਦਿਓ(n*ਆਕਾਰ(ਪੂਰਨ))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

ਲਿਖੋ("\n B's address %x %x",b,&b);
ਲਈ(i=0;i<n;i++)
{
  b[i]=i+1;
}

ਲਈ(i=0;i<n;i++)
{
    ਲਿਖੋ("\n b[%d]'s address is : %x",i,&b[i]);
    ਲਿਖੋ("\n b[%d]'s value is : %d",i,b[i]);
}

ਮੁਕਤ(b);

ਲਿਖੋ("\nArray B is freed");
ਲਿਖੋ("\nb=%x",b);
ਲਿਖੋ("\n size of array %d",n);

c=ਸਮ੍ਰਿਤੀ_ਦਿਓ(n*ਆਕਾਰ(ਪੂਰਨ))	;
ਲਿਖੋ("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

ਲਿਖੋ("\n C's address %x",c);

ਲਈ(i=0;i<n;i++)
{
    c[i]=i+1;
}

ਲਈ(i=0;i<n;i++)
{
    ਲਿਖੋ("\n c[%d]'s address is : %x",i,&c[i]);
    ਲਿਖੋ("\n c[%d]'s value is : %d",i,c[i]);
}
ਮੁਕਤ(c);

ਲਿਖੋ("\nc=%x",c);

ਪੂਰਨ x;
x=30;

ਲਿਖੋ("\n\n\nx address is %x",&x);
d=ਸਮ੍ਰਿਤੀ_ਦਿਓ(x*ਆਕਾਰ(ਪੂਰਨ));

ਲਿਖੋ("\n D's address %x",d);
ਲਈ(i=0;i<x;i++)
{
    ਲਿਖੋ("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

ਲਈ(i=0;i<x;i++)
{
    ਲਿਖੋ("\n d[%d]'s address is : %x",i,&d[i]);
    ਲਿਖੋ("\n d[%d]'s value is : %d",i,d[i]);
}

ਮੁਕਤ(d);

ਲਿਖੋ("\nd=%x",d);

}
