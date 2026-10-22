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
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ()
{
ಬರೆ("\nTest Running");
ಪೂರ್ಣಾಂಕ *b,*c,*d;
ಪೂರ್ಣಾಂಕ i=0;ಪೂರ್ಣಾಂಕ n;
n= 25;
ಬರೆ("\n size of array %d %x",n,&n);
b=ಸ್ಮರಣೆ_ಕೊಡು(n*ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ))	;
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

ಹಿಂತಿರುಗಿ 0;
}

