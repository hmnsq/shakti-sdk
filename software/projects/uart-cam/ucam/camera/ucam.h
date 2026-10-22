/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  ucam.h
* Brief Description of file             :  
* Name of Author                        :  P Girinath, Shivaram Prasad Meesa
* Email ID                              :  palanigirinath@gmail.com, shivaramprasadmeesa@gmail.com

    Copyright (C) 2020  IIT Madras. All rights reserved.

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
  @file ucam.h
  @brief
  @details
**/



#अन्तर्भाव <stdio.h>
#अन्तर्भाव "uart.h"
#परिभाषय CAM uart_instance[1]
#परिभाषय HOST uart_instance[2]
पूर्णाङ्क init_cam();
शून्य get_pic(पूर्णाङ्क);  // two modes 0---one pic, 1---continuous pictures
शून्य send_पूर्णम्_reset();