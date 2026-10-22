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
صحيح اصلي()
{
چاپ_کړه("\nTest Running");
صحيح *b,*c,*d;
صحيح i=0;صحيح n;
n= 25;
چاپ_کړه("\n size of array %d %x",n,&n);
b=حافظه_ورکړه(n*حجم(صحيح))	;
چاپ_کړه("\n B's address %x %x",b,&b);
لكل(i=0;i<n;i++)
{
b[i]=i+1;
}
لكل(i=0;i<n;i++)
{
چاپ_کړه("\n b[%d]'s address is : %x",i,&b[i]);
چاپ_کړه("\n b[%d]'s value is : %d",i,b[i]);
}
حرر(b);
چاپ_کړه("\nArray B is freed");
چاپ_کړه("\nb=%x",b);
چاپ_کړه("\n size of array %d",n);
c=حافظه_ورکړه(n*حجم(صحيح))	;
چاپ_کړه("\n C's address %x",c);
لكل(i=0;i<n;i++)
{
c[i]=i+1;
}
لكل(i=0;i<n;i++)
{
چاپ_کړه("\n c[%d]'s address is : %x",i,&c[i]);
چاپ_کړه("\n c[%d]'s value is : %d",i,c[i]);
}
حرر(c);
چاپ_کړه("\nc=%x",c);
صحيح x;
x=30;
چاپ_کړه("\n\n\nx address is %x",&x);
d=حافظه_ورکړه(x*حجم(صحيح));
چاپ_کړه("\n D's address %x",d);
لكل(i=0;i<x;i++)
{
چاپ_کړه("\nSetting value %d , %x",i+1,&d[i]); 
d[i]=i+1;
}
لكل(i=0;i<x;i++)
{
چاپ_کړه("\n d[%d]'s address is : %x",i,&d[i]);
چاپ_کړه("\n d[%d]'s value is : %d",i,d[i]);
}
حرر(d);
چاپ_کړه("\nd=%x",d);

أرجع 0;
}

