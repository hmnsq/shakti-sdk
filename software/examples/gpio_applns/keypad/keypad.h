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
#ಆದರೆ !defined(KYPD_H)
#ವ್ಯಾಖ್ಯಾನಿಸು KYPD_H

#ವ್ಯಾಖ್ಯಾನಿಸು ROWNUM 4
#ವ್ಯಾಖ್ಯಾನಿಸು COLNUM 4

#ವ್ಯಾಖ್ಯಾನಿಸು OUTPINS_ಸ್ಥಾನಾಂತರ 0
#ವ್ಯಾಖ್ಯಾನಿಸು INPINS_ಸ್ಥಾನಾಂತರ 4
#ವ್ಯಾಖ್ಯಾನಿಸು OUTPINS (0xF << OUTPINS_ಸ್ಥಾನಾಂತರ)
#ವ್ಯಾಖ್ಯಾನಿಸು INPINS  (0xF << INPINS_ಸ್ಥಾನಾಂತರ)

//function prototype
ಶೂನ್ಯ ಗಣ_pins(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ* ಅಡ್ಡಸಾಲು, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ* ಲಂಬಸಾಲು);
ಶೂನ್ಯ ಗಣ_ಕೀಲಿ_map(ಪೂರ್ಣಾಂಕ ಕೋಷ್ಟಕ[COLNUM][ROWNUM]);
ಪೂರ್ಣಾಂಕ get_ಕೀಲಿ();
ಪೂರ್ಣಾಂಕ get_ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು(ಶೂನ್ಯ);
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು_pins[ROWNUM];
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_pins[COLNUM];
ಪೂರ್ಣಾಂಕ ಕೀಲಿ_map[COLNUM][ROWNUM];

#ಆದರೆ_ಅಂತ್ಯ
