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
#ਜੇ !defined(KYPD_H)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KYPD_H

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROWNUM 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COLNUM 4

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OUTPINS_ਵਿੱਥ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INPINS_ਵਿੱਥ 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OUTPINS (0xF << OUTPINS_ਵਿੱਥ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INPINS  (0xF << INPINS_ਵਿੱਥ)

//function prototype
ਖਾਲੀ ਸੈੱਟ_pins(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* ਪੰਕਤੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* ਖਾਨਾ);
ਖਾਲੀ ਸੈੱਟ_ਕੁੰਜੀ_map(ਪੂਰਨ ਸਾਰਣੀ[COLNUM][ROWNUM]);
ਪੂਰਨ get_ਕੁੰਜੀ();
ਪੂਰਨ get_ਖਾਨਾ_ਪੰਕਤੀ(ਖਾਲੀ);
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਪੰਕਤੀ_pins[ROWNUM];
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਖਾਨਾ_pins[COLNUM];
ਪੂਰਨ ਕੁੰਜੀ_map[COLNUM][ROWNUM];

#ਜੇ_ਅੰਤ
