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
صحیح مین()
{
لکھو("\nTest Running");
صحیح *b,*c,*d;
صحیح i=0;صحیح n;
n= 25;
لکھو("\n size of array %d %x",n,&n);
b=حافظہ_دو(n*حجم(صحیح))	;
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

واپس 0;
}

