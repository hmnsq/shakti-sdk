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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <assert.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
// Linux headers
#अन्तर्भाव <fcntl.h> // Contains file controls like O_RDWR
#अन्तर्भाव <errno.h> // Error integer and strerror() function
#अन्तर्भाव <termios.h> // Contains POSIX terminal control definitions
#अन्तर्भाव <unistd.h> // write(), read(), close()

पूर्णाङ्क मुख्यम्(पूर्णाङ्क argc,वर्ण *argv[]) {
  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    पूर्णाङ्क serial_port1 = उद्घाटय(argv[1], O_RDWR);
    प्रारूप_लिख("%s\n",argv[1]);
    // Create new termios struc, we call it 'tty1' for convention
    संरचना termios tty1;

    // Read in existing settings, and handle any error
    यदि(tcgetattr(serial_port1, &tty1) != 0) {
        प्रारूप_लिख("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        प्रत्यागम 1;
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
    प्रारूप_लिख("\n Baud rate is set to 115200");

  // Save tty1 settings, also checking for error
    यदि (tcsetattr(serial_port1, TCSANOW, &tty1) != 0) {
        प्रारूप_लिख("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        प्रत्यागम 1;
    }
    अन्यथा
        प्रारूप_लिख("\n  BaudRate = 115200 \n  StopBits = 1 \n  Parity   = none\n");

  // Allocate memory for read buffer, set size according to your needs
    पूर्णाङ्क loop=0;
    यावत्(1){
      loop++;
      अचिह्नित वर्ण read_buf [7];
      स्मृतिं_पूरय(&read_buf, '\0', परिमाण(read_buf));
      start:
      // From Shakti we expect 6 bytes : 0xAA 0xA 0x5 a b c where a b c represent size of image

      यावत्(read_buf[0]!=(अचिह्नित वर्ण)0xAA){
          पठ(serial_port1, &read_buf[0], परिमाण(read_buf[0]));
      }
      पठ(serial_port1, &read_buf[1], परिमाण(read_buf[0]));
      यदि(read_buf[1]!=(अचिह्नित वर्ण)0xA){
        गच्छ start;
      }
      पठ(serial_port1, &read_buf[2], परिमाण(read_buf[0]));
      यदि(read_buf[2]!=(अचिह्नित वर्ण)0x5){
        गच्छ start;
      }
      पठ(serial_port1, &read_buf[3], परिमाण(read_buf[0]));
      पठ(serial_port1, &read_buf[4], परिमाण(read_buf[0]));
      पठ(serial_port1, &read_buf[5], परिमाण(read_buf[0]));
      अचिह्नित दीर्घ आकार = 0;
      आकार = (अचिह्नित दीर्घ)read_buf[3] + (((अचिह्नित दीर्घ)read_buf[4])<<8) + (((अचिह्नित दीर्घ)read_buf[5])<<16) ;
      प्रारूप_लिख("Size : %ld\n",आकार);
      वर्ण* अस्थायी = (वर्ण*) स्मृतिं_देहि(आकार*परिमाण(वर्ण));
      यदि(अस्थायी==रिक्त) {
        प्रारूप_लिख("Malloc failed\n");
        निर्गच्छ(1);
      }
      वर्ण write_buff;
      write_buff='K';
      //Send a conformation 'K'
      tcflush(serial_port1,TCIOFLUSH);
      लिख(serial_port1,&write_buff,परिमाण(write_buff));
      प्रति(दीर्घ i=0;i<आकार;i++){
          पठ(serial_port1, (अस्थायी + i) , परिमाण(read_buf[0]));
      }
      tcflush(serial_port1,TCIOFLUSH);
      FILE *f1;
      वर्ण str[]="Images/image";
      वर्ण inte[20];
      sprintf(inte, "%d", loop);
      वाक्यं_योजय(str,inte);
      वाक्यं_योजय(str,".jpeg");
      f1=fopen(str,"w");
      प्रति(दीर्घ i=0;i<आकार;i++)
      {
        fputc(*(अस्थायी+i),f1);
      }
      मुक्त(अस्थायी);
      fclose(f1);
      write_buff='O';
      //Send a conformation 'O'
      tcflush(serial_port1,TCOFLUSH);
      लिख(serial_port1,&write_buff,परिमाण(write_buff));
      tcflush(serial_port1,TCIOFLUSH);
      प्रारूप_लिख("Image %d done",loop);
    }
    close(serial_port1);
    प्रत्यागम 0; // success
}
