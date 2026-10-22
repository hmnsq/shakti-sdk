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

बाह्य वर्ण _free_space[];
बाह्य वर्ण राशिः_आकार[];
बाह्य वर्ण HEAP_आकार[];
बाह्य वर्ण राशिः_अन्तः[];
बाह्य वर्ण राशिः[];
बाह्य वर्ण _heap[];
बाह्य वर्ण heap_अन्तः[];
बाह्य वर्ण __bss_end[];
बाह्य वर्ण __bss_start[];
बाह्य वर्ण __sbss_end[];
बाह्य वर्ण __sbss_start[];


वर्ण *test1=(वर्ण *)&_free_space;
वर्ण *test3=(वर्ण *)&राशिः_आकार;
वर्ण *test4=(वर्ण *)&HEAP_आकार;
वर्ण *test5=(वर्ण *)&राशिः_अन्तः;
वर्ण *test6=(वर्ण *)&राशिः;
वर्ण *test7=(वर्ण *)&_heap;
वर्ण *test8=(वर्ण *)&heap_अन्तः;
वर्ण *test9=(वर्ण *)&__bss_end;
वर्ण *test10=(वर्ण *)&__bss_start;
वर्ण *test11=(वर्ण *)&__sbss_end;
वर्ण *test12=(वर्ण *)&__sbss_start;

पूर्णाङ्क c1,c2,c3,c4,c5;
पूर्णाङ्क *pointer;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
पूर्णाङ्क मुख्यम्()
{

  प्रारूप_लिख("\n\n\n\n\n\nTest Running");
  प्रारूप_लिख("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  प्रारूप_लिख("\n %x %d %x %x %x %x %x",&pointer,c1,&c1,&c2,&c3,&c4,&c5);
  
  स्थिर पूर्णाङ्क b1,b2,b3,b4,b5;
  प्रारूप_लिख("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  पूर्णाङ्क a1,a2,a3,a4,a5;
  प्रारूप_लिख("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

पूर्णाङ्क **a;
पूर्णाङ्क *b,*c,*d;
पूर्णाङ्क i=0;पूर्णाङ्क n;

//Enter Size of Array;
n= 25;
प्रारूप_लिख("\n size of array %d %x",n,&n);
b=स्मृतिं_देहि(n*परिमाण(पूर्णाङ्क))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

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
प्रारूप_लिख("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

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

}
