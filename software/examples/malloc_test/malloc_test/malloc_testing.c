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

خارجی حرف _free_space[];
خارجی حرف ڈھیر_سائز_3[];
خارجی حرف ڈھیر_سائز[];
خارجی حرف ڈھیر_انتہا[];
خارجی حرف ڈھیر[];
خارجی حرف ڈھیر_2[];
خارجی حرف ڈھیر_انتہا_2[];
خارجی حرف __bss_end[];
خارجی حرف __bss_start[];
خارجی حرف __sbss_end[];
خارجی حرف __sbss_start[];


حرف *test1=(حرف *)&_free_space;
حرف *test3=(حرف *)&ڈھیر_سائز_3;
حرف *test4=(حرف *)&ڈھیر_سائز;
حرف *test5=(حرف *)&ڈھیر_انتہا;
حرف *test6=(حرف *)&ڈھیر;
حرف *test7=(حرف *)&ڈھیر_2;
حرف *test8=(حرف *)&ڈھیر_انتہا_2;
حرف *test9=(حرف *)&__bss_end;
حرف *test10=(حرف *)&__bss_start;
حرف *test11=(حرف *)&__sbss_end;
حرف *test12=(حرف *)&__sbss_start;

صحیح c1,c2,c3,c4,c5;
صحیح *اشارہ_گر;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
صحیح مین()
{

  لکھو("\n\n\n\n\n\nTest Running");
  لکھو("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  لکھو("\n %x %d %x %x %x %x %x",&اشارہ_گر,c1,&c1,&c2,&c3,&c4,&c5);
  
  ساکن صحیح b1,b2,b3,b4,b5;
  لکھو("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  صحیح a1,a2,a3,a4,a5;
  لکھو("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

صحیح **a;
صحیح *b,*c,*d;
صحیح i=0;صحیح n;

//Enter Size of Array;
n= 25;
لکھو("\n size of array %d %x",n,&n);
b=حافظہ_دو(n*حجم(صحیح))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

لکھو("\n B's address %x %x",b,&b);
برائے(i=0;i<n;i++)
{
  b[i]=i+1;
}

برائے(i=0;i<n;i++)
{
    لکھو("\n b[%d]'s address is : %x",i,&b[i]);
    لکھو("\n b[%d]'s value is : %d",i,b[i]);
}

آزاد(b);

لکھو("\nArray B is freed");
لکھو("\nb=%x",b);
لکھو("\n size of array %d",n);

c=حافظہ_دو(n*حجم(صحیح))	;
لکھو("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

لکھو("\n C's address %x",c);

برائے(i=0;i<n;i++)
{
    c[i]=i+1;
}

برائے(i=0;i<n;i++)
{
    لکھو("\n c[%d]'s address is : %x",i,&c[i]);
    لکھو("\n c[%d]'s value is : %d",i,c[i]);
}
آزاد(c);

لکھو("\nc=%x",c);

صحیح x;
x=30;

لکھو("\n\n\nx address is %x",&x);
d=حافظہ_دو(x*حجم(صحیح));

لکھو("\n D's address %x",d);
برائے(i=0;i<x;i++)
{
    لکھو("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

برائے(i=0;i<x;i++)
{
    لکھو("\n d[%d]'s address is : %x",i,&d[i]);
    لکھو("\n d[%d]'s value is : %d",i,d[i]);
}

آزاد(d);

لکھو("\nd=%x",d);

}
