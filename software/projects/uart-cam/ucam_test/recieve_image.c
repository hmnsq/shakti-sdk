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

पूर्णांक main(पूर्णांक argc,अक्षर *argv[]) {
  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    पूर्णांक serial_port1 = खोलो(argv[1], O_RDWR);
    म_लिखो("%s\n",argv[1]);
    // Create new termios struc, we call it 'tty1' for convention
    संरचना termios tty1;

    // Read in existing settings, and handle any error
    जर(tcgetattr(serial_port1, &tty1) != 0) {
        म_लिखो("Error %i from tcgetattr: %s\n", त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
        परत 1;
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
    म_लिखो("\n Baud rate is set to 115200");

  // Save tty1 settings, also checking for error
    जर (tcsetattr(serial_port1, TCSANOW, &tty1) != 0) {
        म_लिखो("Error %i from tcsetattr: %s\n", त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
        परत 1;
    }
    अन्यथा
        म_लिखो("\n  BaudRate = 115200 \n  StopBits = 1 \n  Parity   = none\n");

  // Allocate memory for read buffer, set size according to your needs
    पूर्णांक loop=0;
    पर्यंत(1){
      loop++;
      अचिन्हित अक्षर read_buf [7];
      स_रखो(&read_buf, '\0', आकार(read_buf));
      start:
      // From Shakti we expect 6 bytes : 0xAA 0xA 0x5 a b c where a b c represent size of image

      पर्यंत(read_buf[0]!=(अचिन्हित अक्षर)0xAA){
          पठ(serial_port1, &read_buf[0], आकार(read_buf[0]));
      }
      पठ(serial_port1, &read_buf[1], आकार(read_buf[0]));
      जर(read_buf[1]!=(अचिन्हित अक्षर)0xA){
        जा start;
      }
      पठ(serial_port1, &read_buf[2], आकार(read_buf[0]));
      जर(read_buf[2]!=(अचिन्हित अक्षर)0x5){
        जा start;
      }
      पठ(serial_port1, &read_buf[3], आकार(read_buf[0]));
      पठ(serial_port1, &read_buf[4], आकार(read_buf[0]));
      पठ(serial_port1, &read_buf[5], आकार(read_buf[0]));
      अचिन्हित दीर्घ size = 0;
      size = (अचिन्हित दीर्घ)read_buf[3] + (((अचिन्हित दीर्घ)read_buf[4])<<8) + (((अचिन्हित दीर्घ)read_buf[5])<<16) ;
      म_लिखो("Size : %ld\n",size);
      अक्षर* temp = (अक्षर*) दो_स्मृति(size*आकार(अक्षर));
      जर(temp==रिक्त) {
        म_लिखो("Malloc failed\n");
        निकास(1);
      }
      अक्षर write_buff;
      write_buff='K';
      //Send a conformation 'K'
      tcflush(serial_port1,TCIOFLUSH);
      लिख(serial_port1,&write_buff,आकार(write_buff));
      साठी(दीर्घ i=0;i<size;i++){
          पठ(serial_port1, (temp + i) , आकार(read_buf[0]));
      }
      tcflush(serial_port1,TCIOFLUSH);
      खाता *f1;
      अक्षर str[]="Images/image";
      अक्षर inte[20];
      प्र_लिखो(inte, "%d", loop);
      म_जोड़ो(str,inte);
      म_जोड़ो(str,".jpeg");
      f1=ख_खोलो(str,"w");
      साठी(दीर्घ i=0;i<size;i++)
      {
        ख_अक्षर_दो(*(temp+i),f1);
      }
      मुक्त(temp);
      ख_बंद(f1);
      write_buff='O';
      //Send a conformation 'O'
      tcflush(serial_port1,TCOFLUSH);
      लिख(serial_port1,&write_buff,आकार(write_buff));
      tcflush(serial_port1,TCIOFLUSH);
      म_लिखो("Image %d done",loop);
    }
    बंद(serial_port1);
    परत 0; // success
}
