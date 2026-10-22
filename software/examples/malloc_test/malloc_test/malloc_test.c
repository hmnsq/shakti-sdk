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
పూర్ణాంకం ప్రధాన()
{
రాయి("\nTest Running");
పూర్ణాంకం *b,*c,*d;
పూర్ణాంకం i=0;పూర్ణాంకం n;
n= 25;
రాయి("\n size of array %d %x",n,&n);
b=జ్ఞాపకం_ఇవ్వు(n*పరిమాణం(పూర్ణాంకం))	;
రాయి("\n B's address %x %x",b,&b);
కొరకు(i=0;i<n;i++)
{
b[i]=i+1;
}
కొరకు(i=0;i<n;i++)
{
రాయి("\n b[%d]'s address is : %x",i,&b[i]);
రాయి("\n b[%d]'s value is : %d",i,b[i]);
}
విడుదల(b);
రాయి("\nArray B is freed");
రాయి("\nb=%x",b);
రాయి("\n size of array %d",n);
c=జ్ఞాపకం_ఇవ్వు(n*పరిమాణం(పూర్ణాంకం))	;
రాయి("\n C's address %x",c);
కొరకు(i=0;i<n;i++)
{
c[i]=i+1;
}
కొరకు(i=0;i<n;i++)
{
రాయి("\n c[%d]'s address is : %x",i,&c[i]);
రాయి("\n c[%d]'s value is : %d",i,c[i]);
}
విడుదల(c);
రాయి("\nc=%x",c);
పూర్ణాంకం x;
x=30;
రాయి("\n\n\nx address is %x",&x);
d=జ్ఞాపకం_ఇవ్వు(x*పరిమాణం(పూర్ణాంకం));
రాయి("\n D's address %x",d);
కొరకు(i=0;i<x;i++)
{
రాయి("\nSetting value %d , %x",i+1,&d[i]); 
d[i]=i+1;
}
కొరకు(i=0;i<x;i++)
{
రాయి("\n d[%d]'s address is : %x",i,&d[i]);
రాయి("\n d[%d]'s value is : %d",i,d[i]);
}
విడుదల(d);
రాయి("\nd=%x",d);

తిరిగి 0;
}

