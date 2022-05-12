/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "utils.h"
//#include "uart.h"
//#include "platform.h"
#include "pinmux.h"
//#include "sspi.h"
//#include "log.h"

//#include "gpio.h"
// #include "uart.h"

//#include "Print.h"


#include "sd.h"

File myFile;

int main() {


  // ***************INITIALIZATION STAGE**************

  
  printf("1.Start to Initialize SD card... \n");

  if (!SD.begin(4)) {
    printf("initialization failed!");
    while (1);
  }
  printf("\n initialization  done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
 
 // ***************FILE WRITE STAGE **************



  myFile = SD.open("testfile.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    printf("\n Writing to a file... .");
    char buffer[]="testing 1, 2, 3.";
    int a=strlen(buffer);
    printf("\n buffer size =%d",a);
    // const char *buffer="testing 1, 2, 3.";
    //  size_t siz=0;
    // siz = strlen(buffer);
    // string str="testing 1, 2, 3.";
    myFile.write((const uint8_t *) buffer,strlen(buffer));
    //myFile.write();   //
    
    myFile.close();  // close the file:
    printf("\n writing done.");
  } else {
    
    printf("error opening test.txt writing stage error");  // if the file didn't open, print an error:
  }

  // ***************FILE READ STAGE **************
#if 0
  // re-open the file for reading:
  myFile = SD.open("readfile.txt");
  if (myFile) {
    printf("fileOpenRead--------------------------------------------------");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      myFile.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    printf("error opening test.txt reading stage error");
  }
return 0;
#endif
}

// void loop() {
//   // nothing happens after setup
// }


