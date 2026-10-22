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

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <assert.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
// Linux headers
#અન્તર્ભાવ <fcntl.h> // Contains file controls like O_RDWR
#અન્તર્ભાવ <errno.h> // Error integer and strerror() function
#અન્તર્ભાવ <termios.h> // Contains POSIX terminal control definitions
#અન્તર્ભાવ <unistd.h> // write(), read(), close()

પૂર્ણાંક મુખ્ય(પૂર્ણાંક argc,અક્ષર *argv[]) {
  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    પૂર્ણાંક serial_port1 = open(argv[1], O_RDWR);
    printf("%s\n",argv[1]);
    // Create new termios struc, we call it 'tty1' for convention
    સંરચના termios tty1;

    // Read in existing settings, and handle any error
    જો(tcgetattr(serial_port1, &tty1) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        પાછા 1;
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
    printf("\n Baud rate is set to 115200");

  // Save tty1 settings, also checking for error
    જો (tcsetattr(serial_port1, TCSANOW, &tty1) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        પાછા 1;
    }
    નહીંતર
        printf("\n  BaudRate = 115200 \n  StopBits = 1 \n  Parity   = none\n");

  // Allocate memory for read buffer, set size according to your needs
    પૂર્ણાંક loop=0;
    જ્યારે(1){
      loop++;
      unsigned અક્ષર read_buf [7];
      memset(&read_buf, '\0', કદ(read_buf));
      start:
      // From Shakti we expect 6 bytes : 0xAA 0xA 0x5 a b c where a b c represent size of image

      જ્યારે(read_buf[0]!=(unsigned અક્ષર)0xAA){
          પઠ(serial_port1, &read_buf[0], કદ(read_buf[0]));
      }
      પઠ(serial_port1, &read_buf[1], કદ(read_buf[0]));
      જો(read_buf[1]!=(unsigned અક્ષર)0xA){
        જાઓ start;
      }
      પઠ(serial_port1, &read_buf[2], કદ(read_buf[0]));
      જો(read_buf[2]!=(unsigned અક્ષર)0x5){
        જાઓ start;
      }
      પઠ(serial_port1, &read_buf[3], કદ(read_buf[0]));
      પઠ(serial_port1, &read_buf[4], કદ(read_buf[0]));
      પઠ(serial_port1, &read_buf[5], કદ(read_buf[0]));
      unsigned long size = 0;
      size = (unsigned long)read_buf[3] + (((unsigned long)read_buf[4])<<8) + (((unsigned long)read_buf[5])<<16) ;
      printf("Size : %ld\n",size);
      અક્ષર* temp = (અક્ષર*) malloc(size*કદ(અક્ષર));
      જો(temp==ખાલી) {
        printf("Malloc failed\n");
        exit(1);
      }
      અક્ષર write_buff;
      write_buff='K';
      //Send a conformation 'K'
      tcflush(serial_port1,TCIOFLUSH);
      લિખ(serial_port1,&write_buff,કદ(write_buff));
      માટે(long i=0;i<size;i++){
          પઠ(serial_port1, (temp + i) , કદ(read_buf[0]));
      }
      tcflush(serial_port1,TCIOFLUSH);
      FILE *f1;
      અક્ષર str[]="Images/image";
      અક્ષર inte[20];
      sprintf(inte, "%d", loop);
      strcat(str,inte);
      strcat(str,".jpeg");
      f1=fopen(str,"w");
      માટે(long i=0;i<size;i++)
      {
        fputc(*(temp+i),f1);
      }
      મુક્ત(temp);
      fclose(f1);
      write_buff='O';
      //Send a conformation 'O'
      tcflush(serial_port1,TCOFLUSH);
      લિખ(serial_port1,&write_buff,કદ(write_buff));
      tcflush(serial_port1,TCIOFLUSH);
      printf("Image %d done",loop);
    }
    close(serial_port1);
    પાછા 0; // success
}
