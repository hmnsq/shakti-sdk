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
पूर्णांक main()
{
म_लिखो("\nTest Running");
पूर्णांक *b,*c,*d;
पूर्णांक i=0;पूर्णांक n;
n= 25;
म_लिखो("\n size of array %d %x",n,&n);
b=दो_स्मृति(n*आकार(पूर्णांक))	;
म_लिखो("\n B's address %x %x",b,&b);
साठी(i=0;i<n;i++)
{
b[i]=i+1;
}
साठी(i=0;i<n;i++)
{
म_लिखो("\n b[%d]'s address is : %x",i,&b[i]);
म_लिखो("\n b[%d]'s value is : %d",i,b[i]);
}
मुक्त(b);
म_लिखो("\nArray B is freed");
म_लिखो("\nb=%x",b);
म_लिखो("\n size of array %d",n);
c=दो_स्मृति(n*आकार(पूर्णांक))	;
म_लिखो("\n C's address %x",c);
साठी(i=0;i<n;i++)
{
c[i]=i+1;
}
साठी(i=0;i<n;i++)
{
म_लिखो("\n c[%d]'s address is : %x",i,&c[i]);
म_लिखो("\n c[%d]'s value is : %d",i,c[i]);
}
मुक्त(c);
म_लिखो("\nc=%x",c);
पूर्णांक x;
x=30;
म_लिखो("\n\n\nx address is %x",&x);
d=दो_स्मृति(x*आकार(पूर्णांक));
म_लिखो("\n D's address %x",d);
साठी(i=0;i<x;i++)
{
म_लिखो("\nSetting value %d , %x",i+1,&d[i]); 
d[i]=i+1;
}
साठी(i=0;i<x;i++)
{
म_लिखो("\n d[%d]'s address is : %x",i,&d[i]);
म_लिखो("\n d[%d]'s value is : %d",i,d[i]);
}
मुक्त(d);
म_लिखो("\nd=%x",d);

परत 0;
}

