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

బాహ్య అక్షరం _free_space[];
బాహ్య అక్షరం దొంతర_కొలత[];
బాహ్య అక్షరం కుప్ప_కొలత[];
బాహ్య అక్షరం దొంతర_చివర[];
బాహ్య అక్షరం దొంతర[];
బాహ్య అక్షరం కుప్ప[];
బాహ్య అక్షరం కుప్ప_చివర[];
బాహ్య అక్షరం __bss_end[];
బాహ్య అక్షరం __bss_start[];
బాహ్య అక్షరం __sbss_end[];
బాహ్య అక్షరం __sbss_start[];


అక్షరం *test1=(అక్షరం *)&_free_space;
అక్షరం *test3=(అక్షరం *)&దొంతర_కొలత;
అక్షరం *test4=(అక్షరం *)&కుప్ప_కొలత;
అక్షరం *test5=(అక్షరం *)&దొంతర_చివర;
అక్షరం *test6=(అక్షరం *)&దొంతర;
అక్షరం *test7=(అక్షరం *)&కుప్ప;
అక్షరం *test8=(అక్షరం *)&కుప్ప_చివర;
అక్షరం *test9=(అక్షరం *)&__bss_end;
అక్షరం *test10=(అక్షరం *)&__bss_start;
అక్షరం *test11=(అక్షరం *)&__sbss_end;
అక్షరం *test12=(అక్షరం *)&__sbss_start;

పూర్ణాంకం c1,c2,c3,c4,c5;
పూర్ణాంకం *సూచిక_2;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
పూర్ణాంకం ప్రధాన()
{

  రాయి("\n\n\n\n\n\nTest Running");
  రాయి("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  రాయి("\n %x %d %x %x %x %x %x",&సూచిక_2,c1,&c1,&c2,&c3,&c4,&c5);
  
  స్థిర పూర్ణాంకం b1,b2,b3,b4,b5;
  రాయి("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  పూర్ణాంకం a1,a2,a3,a4,a5;
  రాయి("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

పూర్ణాంకం **a;
పూర్ణాంకం *b,*c,*d;
పూర్ణాంకం i=0;పూర్ణాంకం n;

//Enter Size of Array;
n= 25;
రాయి("\n size of array %d %x",n,&n);
b=జ్ఞాపకం_ఇవ్వు(n*పరిమాణం(పూర్ణాంకం))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

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
రాయి("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

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

}
