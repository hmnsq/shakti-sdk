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
पूर्णाङ्क मुख्यम्()
{
प्रारूप_लिख("\nTest Running");
पूर्णाङ्क *b,*c,*d;
पूर्णाङ्क i=0;पूर्णाङ्क n;
n= 25;
प्रारूप_लिख("\n size of array %d %x",n,&n);
b=स्मृतिं_देहि(n*परिमाण(पूर्णाङ्क))	;
प्रारूप_लिख("\n B's address %x %x",b,&b);
प्रति(i=0;i<n;i++)
{
b[i]=i+1;
}
प्रति(i=0;i<n;i++)
{
प्रारूप_लिख("\n b[%d]'s address is : %x",i,&b[i]);
प्रारूप_लिख("\n b[%d]'s value is : %d",i,b[i]);
}
मुक्त(b);
प्रारूप_लिख("\nArray B is freed");
प्रारूप_लिख("\nb=%x",b);
प्रारूप_लिख("\n size of array %d",n);
c=स्मृतिं_देहि(n*परिमाण(पूर्णाङ्क))	;
प्रारूप_लिख("\n C's address %x",c);
प्रति(i=0;i<n;i++)
{
c[i]=i+1;
}
प्रति(i=0;i<n;i++)
{
प्रारूप_लिख("\n c[%d]'s address is : %x",i,&c[i]);
प्रारूप_लिख("\n c[%d]'s value is : %d",i,c[i]);
}
मुक्त(c);
प्रारूप_लिख("\nc=%x",c);
पूर्णाङ्क x;
x=30;
प्रारूप_लिख("\n\n\nx address is %x",&x);
d=स्मृतिं_देहि(x*परिमाण(पूर्णाङ्क));
प्रारूप_लिख("\n D's address %x",d);
प्रति(i=0;i<x;i++)
{
प्रारूप_लिख("\nSetting value %d , %x",i+1,&d[i]); 
d[i]=i+1;
}
प्रति(i=0;i<x;i++)
{
प्रारूप_लिख("\n d[%d]'s address is : %x",i,&d[i]);
प्रारूप_लिख("\n d[%d]'s value is : %d",i,d[i]);
}
मुक्त(d);
प्रारूप_लिख("\nd=%x",d);

प्रत्यागम 0;
}

