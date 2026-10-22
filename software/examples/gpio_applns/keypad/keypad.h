/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  keypad.h
 * Brief Description of file            :  Declaration for keypad library.
 * Name of Author    	                : Kotteeswaran
 * Email ID                             : kottee.1@gmail.com

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
 * @file keypad.h
 * @brief Declaration for keypad library.
 * @detail Include File Definitions	
 */
#ఒకవేళ !defined(KYPD_H)
#నిర్వచించు KYPD_H

#నిర్వచించు ROWNUM 4
#నిర్వచించు COLNUM 4

#నిర్వచించు OUTPINS_స్థానభ్రంశం 0
#నిర్వచించు INPINS_స్థానభ్రంశం 4
#నిర్వచించు OUTPINS (0xF << OUTPINS_స్థానభ్రంశం)
#నిర్వచించు INPINS  (0xF << INPINS_స్థానభ్రంశం)

//function prototype
శూన్య సమితి_pins(గుర్తులేని పూర్ణాంకం* అడ్డువరుస, గుర్తులేని పూర్ణాంకం* నిలువు);
శూన్య సమితి_కీలకం_map(పూర్ణాంకం పట్టిక[COLNUM][ROWNUM]);
పూర్ణాంకం get_కీలకం();
పూర్ణాంకం get_నిలువు_అడ్డువరుస(శూన్య);
గుర్తులేని పూర్ణాంకం అడ్డువరుస_pins[ROWNUM];
గుర్తులేని పూర్ణాంకం నిలువు_pins[COLNUM];
పూర్ణాంకం కీలకం_map[COLNUM][ROWNUM];

#అయితే_ముగింపు
