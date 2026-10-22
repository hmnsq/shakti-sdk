/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  camera.c
* Brief Description of file             :  Sample project to demonstrate 
                                           using of uart to read data from Shakti board
* Name of Author    	                  :  Akshaya B
* Email ID                              :  akshayabarat@gmail.com
* Edited by                             :  P Girinath, Shivaram Prasad Meesa
* Email IDs                             :  palanigirinath@gmail.com, shivaramprasadmeesa@gmail.com


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
  @file camera.c
  @brief Sample project to demonstrate using of uart to read data from Shakti board
  @details We have a camera connected to the board, which sends the image size and then the jpeg image 
           bytewise. We transfer all those to our laptop, where this code is run.
**/

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <assert.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
// Linux headers
#ಅನ್ತರ್ಭಾವ <fcntl.h> // Contains file controls like O_RDWR
#ಅನ್ತರ್ಭಾವ <errno.h> // Error integer and strerror() function
#ಅನ್ತರ್ಭಾವ <termios.h> // Contains POSIX terminal control definitions
#ಅನ್ತರ್ಭಾವ <unistd.h> // write(), read(), close()

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc,ಅಕ್ಷರ *argv[]) {
  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    ಪೂರ್ಣಾಂಕ serial_port1 = open(argv[1], O_RDWR);
    ಬರೆ("%s\n",argv[1]);
    // Create new termios struc, we call it 'tty1' for convention
    ರಚನೆ termios tty1;

    // Read in existing settings, and handle any error
    ಆದರೆ(tcgetattr(serial_port1, &tty1) != 0) {
        ಬರೆ("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        ಹಿಂತಿರುಗಿ 1;
    }
    tty1.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty1.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty1.c_cflag &= ~CSIZE; // Clear all bits that set the data size
    tty1.c_cflag |= CS8; // 8 bits per byte (most common)
    tty1.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty1.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty1.c_lflag &= ~ICANON;
    tty1.c_lflag &= ~ECHO; // Disable echo
    tty1.c_lflag &= ~ECHOE; // Disable erasure
    tty1.c_lflag &= ~ECHONL; // Disable new-line echo
    tty1.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty1.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty1.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty1.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty1.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty1.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty1.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty1.c_cc[VTIME] = 0;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty1.c_cc[VMIN] = 10;

    // Set in/out baud rate to be 19200
    cfsetispeed(&tty1, B115200);
    cfsetospeed(&tty1, B115200);
    ಬರೆ("\n Baud rate is set to 115200");

  // Save tty1 settings, also checking for error
    ಆದರೆ (tcsetattr(serial_port1, TCSANOW, &tty1) != 0) {
        ಬರೆ("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        ಹಿಂತಿರುಗಿ 1;
    }
    ಇಲ್ಲದಿದ್ದರೆ
        ಬರೆ("\n  BaudRate = 115200 \n  StopBits = 1 \n  Parity   = none\n");

  // Allocate memory for read buffer, set size according to your needs
    ಪೂರ್ಣಾಂಕ loop=0;
    ಆಗ(1){
      loop++;
      ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_buf [7];
      memset(&read_buf, '\0', ಗಾತ್ರ(read_buf));
      ಆರಂಭ:
      // From Shakti we expect 6 bytes : 0xAA 0xA 0x5 a b c where a b c represent size of image

      ಆಗ(read_buf[0]!=(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)0xAA){
          ಪಠ(serial_port1, &read_buf[0], ಗಾತ್ರ(read_buf[0]));
      }
      ಪಠ(serial_port1, &read_buf[1], ಗಾತ್ರ(read_buf[0]));
      ಆದರೆ(read_buf[1]!=(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)0xA){
        ಹೋಗು ಆರಂಭ;
      }
      ಪಠ(serial_port1, &read_buf[2], ಗಾತ್ರ(read_buf[0]));
      ಆದರೆ(read_buf[2]!=(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)0x5){
        ಹೋಗು ಆರಂಭ;
      }
      ಪಠ(serial_port1, &read_buf[3], ಗಾತ್ರ(read_buf[0]));
      ಪಠ(serial_port1, &read_buf[4], ಗಾತ್ರ(read_buf[0]));
      ಪಠ(serial_port1, &read_buf[5], ಗಾತ್ರ(read_buf[0]));
      ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಗಾತ್ರ_2 = 0;
      ಗಾತ್ರ_2 = (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)read_buf[3] + (((ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)read_buf[4])<<8) + (((ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)read_buf[5])<<16) ;
      ಬರೆ("Size : %ld\n",ಗಾತ್ರ_2);
      ಅಕ್ಷರ* ತಾತ್ಕಾಲಿಕ = (ಅಕ್ಷರ*) ಸ್ಮರಣೆ_ಕೊಡು(ಗಾತ್ರ_2*ಗಾತ್ರ(ಅಕ್ಷರ));
      ಆದರೆ(ತಾತ್ಕಾಲಿಕ==ಖಾಲಿ) {
        ಬರೆ("Malloc failed\n");
        ನಿರ್ಗಮಿಸು(1);
      }
      ಅಕ್ಷರ write_buff;
      write_buff='K';
      //Send a conformation 'K'
      tcflush(serial_port1,TCIOFLUSH);
      ಲಿಖ(serial_port1,&write_buff,ಗಾತ್ರ(write_buff));
      ಗಾಗಿ(ದೀರ್ಘ i=0;i<ಗಾತ್ರ_2;i++){
          ಪಠ(serial_port1, (ತಾತ್ಕಾಲಿಕ + i) , ಗಾತ್ರ(read_buf[0]));
      }
      tcflush(serial_port1,TCIOFLUSH);
      FILE *f1;
      ಅಕ್ಷರ str[]="Images/image";
      ಅಕ್ಷರ inte[20];
      sprintf(inte, "%d", loop);
      strcat(str,inte);
      strcat(str,".jpeg");
      f1=fopen(str,"w");
      ಗಾಗಿ(ದೀರ್ಘ i=0;i<ಗಾತ್ರ_2;i++)
      {
        fputc(*(ತಾತ್ಕಾಲಿಕ+i),f1);
      }
      ಬಿಡುಗಡೆ(ತಾತ್ಕಾಲಿಕ);
      fclose(f1);
      write_buff='O';
      //Send a conformation 'O'
      tcflush(serial_port1,TCOFLUSH);
      ಲಿಖ(serial_port1,&write_buff,ಗಾತ್ರ(write_buff));
      tcflush(serial_port1,TCIOFLUSH);
      ಬರೆ("Image %d done",loop);
    }
    close(serial_port1);
    ಹಿಂತಿರುಗಿ 0; // success
}
