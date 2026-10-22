/***************************************************************************
 * Project                      : shakti devt board
 * Name of the file	        : malloc_test.c
 * Brief Description of file    : test file for malloc.
 * Name of Author    	        : Abhinav Ramnath
 * Email ID                     : abhinavramnath13@gmail.com

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
@file malloc_test.c
@brief test file for malloc
@detail This file is used to test the functions malloc and free
*/

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns 0
 */
صحیح اصلی()
{
printf("\nTest Running");
صحیح *b,*c,*d;
صحیح i=0;صحیح n;
n= 25;
printf("\n size of array %d %x",n,&n);
b=malloc(n*اندازه(صحیح))	;
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

بازگشت 0;
}

