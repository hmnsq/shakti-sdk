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

ಬಾಹ್ಯ ಅಕ್ಷರ _free_space[];
ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ_ಗಾತ್ರ_3[];
ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ_ಗಾತ್ರ[];
ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ_ಕೊನೆ[];
ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ[];
ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ_2[];
ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ_ಕೊನೆ_2[];
ಬಾಹ್ಯ ಅಕ್ಷರ __bss_end[];
ಬಾಹ್ಯ ಅಕ್ಷರ __bss_start[];
ಬಾಹ್ಯ ಅಕ್ಷರ __sbss_end[];
ಬಾಹ್ಯ ಅಕ್ಷರ __sbss_start[];


ಅಕ್ಷರ *test1=(ಅಕ್ಷರ *)&_free_space;
ಅಕ್ಷರ *test3=(ಅಕ್ಷರ *)&ರಾಶಿ_ಗಾತ್ರ_3;
ಅಕ್ಷರ *test4=(ಅಕ್ಷರ *)&ರಾಶಿ_ಗಾತ್ರ;
ಅಕ್ಷರ *test5=(ಅಕ್ಷರ *)&ರಾಶಿ_ಕೊನೆ;
ಅಕ್ಷರ *test6=(ಅಕ್ಷರ *)&ರಾಶಿ;
ಅಕ್ಷರ *test7=(ಅಕ್ಷರ *)&ರಾಶಿ_2;
ಅಕ್ಷರ *test8=(ಅಕ್ಷರ *)&ರಾಶಿ_ಕೊನೆ_2;
ಅಕ್ಷರ *test9=(ಅಕ್ಷರ *)&__bss_end;
ಅಕ್ಷರ *test10=(ಅಕ್ಷರ *)&__bss_start;
ಅಕ್ಷರ *test11=(ಅಕ್ಷರ *)&__sbss_end;
ಅಕ್ಷರ *test12=(ಅಕ್ಷರ *)&__sbss_start;

ಪೂರ್ಣಾಂಕ c1,c2,c3,c4,c5;
ಪೂರ್ಣಾಂಕ *ಸೂಚಕ_2;

/** @fn int main()
 * @brief main runs the code to test malloc
 * @details runs the code to test malloc
 * @return returns int
 */
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ()
{

  ಬರೆ("\n\n\n\n\n\nTest Running");
  ಬರೆ("\n %x %x %x %x %x %x %x %x %x %x %x",test1,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12);
  ಬರೆ("\n %x %d %x %x %x %x %x",&ಸೂಚಕ_2,c1,&c1,&c2,&c3,&c4,&c5);
  
  ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ b1,b2,b3,b4,b5;
  ಬರೆ("\n %x %x %x %x %x",&b1,&b2,&b3,&b4,&b5);

  ಪೂರ್ಣಾಂಕ a1,a2,a3,a4,a5;
  ಬರೆ("\n %x %x %x %x %x",&a1,&a2,&a3,&a4,&a5);

ಪೂರ್ಣಾಂಕ **a;
ಪೂರ್ಣಾಂಕ *b,*c,*d;
ಪೂರ್ಣಾಂಕ i=0;ಪೂರ್ಣಾಂಕ n;

//Enter Size of Array;
n= 25;
ಬರೆ("\n size of array %d %x",n,&n);
b=ಸ್ಮರಣೆ_ಕೊಡು(n*ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ))	;

//printf("\n\n\n\n\n\n\n %x %x %x %x %x %x %x  \n\n\n\n\n",test1,test3,test4,test5,test6,test7,test8);

ಬರೆ("\n B's address %x %x",b,&b);
ಗಾಗಿ(i=0;i<n;i++)
{
  b[i]=i+1;
}

ಗಾಗಿ(i=0;i<n;i++)
{
    ಬರೆ("\n b[%d]'s address is : %x",i,&b[i]);
    ಬರೆ("\n b[%d]'s value is : %d",i,b[i]);
}

ಬಿಡುಗಡೆ(b);

ಬರೆ("\nArray B is freed");
ಬರೆ("\nb=%x",b);
ಬರೆ("\n size of array %d",n);

c=ಸ್ಮರಣೆ_ಕೊಡು(n*ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ))	;
ಬರೆ("\n The previously allocated block from the free list is used to allocate Array C since they are of the same size");

ಬರೆ("\n C's address %x",c);

ಗಾಗಿ(i=0;i<n;i++)
{
    c[i]=i+1;
}

ಗಾಗಿ(i=0;i<n;i++)
{
    ಬರೆ("\n c[%d]'s address is : %x",i,&c[i]);
    ಬರೆ("\n c[%d]'s value is : %d",i,c[i]);
}
ಬಿಡುಗಡೆ(c);

ಬರೆ("\nc=%x",c);

ಪೂರ್ಣಾಂಕ x;
x=30;

ಬರೆ("\n\n\nx address is %x",&x);
d=ಸ್ಮರಣೆ_ಕೊಡು(x*ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ));

ಬರೆ("\n D's address %x",d);
ಗಾಗಿ(i=0;i<x;i++)
{
    ಬರೆ("\nSetting value %d , %x",i+1,&d[i]); 
    d[i]=i+1;
}

ಗಾಗಿ(i=0;i<x;i++)
{
    ಬರೆ("\n d[%d]'s address is : %x",i,&d[i]);
    ಬರೆ("\n d[%d]'s value is : %d",i,d[i]);
}

ಬಿಡುಗಡೆ(d);

ಬರೆ("\nd=%x",d);

}
