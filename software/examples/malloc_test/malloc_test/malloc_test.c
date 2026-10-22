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
ਪੂਰਨ ਮੁੱਖ()
{
ਲਿਖੋ("\nTest Running");
ਪੂਰਨ *b,*c,*d;
ਪੂਰਨ i=0;ਪੂਰਨ n;
n= 25;
ਲਿਖੋ("\n size of array %d %x",n,&n);
b=ਸਮ੍ਰਿਤੀ_ਦਿਓ(n*ਆਕਾਰ(ਪੂਰਨ))	;
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

ਵਾਪਸ 0;
}

