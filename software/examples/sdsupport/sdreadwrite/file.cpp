/*

  SD - a slightly more friendly wrapper for sdfatlib

  This library aims to expose a subset of SD card functionality
  in the form of a higher level "wrapper" object.

  License: GNU General Public License V3
          (Because sdfatlib is licensed with this.)

  (C) Copyright 2010 SparkFun Electronics

*/


#include <stdlib.h>
#include <cstring>
#include <stdbool.h>
#include "sd.h"
//#include "print.h"
#include "sd2card.h"
//#include <cstdlib>


// for debugging file open/close leaks
//uint8_t nfilecount=0;

File::File(SdFile f, const char *n) {
//  SdFile _file;
  printf("/n before malloc"); 
  // oh man you are kidding me, new() doesn't exist? Ok we do it by hand!
  int b= sizeof(SdFile);
  printf("b=%d \n ",b);
  // int *ptr=new int[100];
   printf("\n after malloc"); 
  // printf("a=%d \n ",&ptr);
  //_file = (SdFile *)malloc(sizeof(SdFile));
  //_file = (SdFile *)malloc(b);
  //_file = (SdFile *)new SdFile;
  //_file = new SdFile;
  

   printf("\n after malloc"); 
 // if (_file) {
     printf("\n before memcpy"); 
    memcpy(&_file, &f, sizeof(SdFile)); //copying sdfile to file_
 printf("\n after memcpy"); 
    strncpy(_name, n, 12);
    _name[12] = 0;

    //for debugging file open/close leaks
      //  nfilecount++;
      // printf("\n Created \"");
      //  printf(n);
      // printf("\": ");
      //  printf("\n nfilecount=%d",nfilecount);
  
 // }
}

File::File(void) {
 // _file = 0;
  _name[0] = 0;
  printf("\n Created empty file object");
}

// returns a pointer to the file name
char *File::name(void) {
  return _name;
}

// a directory is a special type of file
bool File::isDirectory(void) {
  return (_file.isDir());
}


size_t File::write(uint8_t val) {
  return write(&val, 1);
}

size_t File::write(const uint8_t *buf, size_t size) {
  // size_t t;
  // if (!_file) {
  //   _file->setWriteError(1);
  //   return 0;
  // }
  // _file->clearWriteError();
  // t = _file->write(buf, size);
  // if (_file->getWriteError()) {
  //   _file->setWriteError(1);
  //   return 0;
  // }
  // return t;


  size_t t;
 // if (!_file) {
   // _file.setWriteError(1);
   // return 0;
 // }
  _file.clearWriteError();
  t = _file.write(buf, size);
  if (_file.getWriteError()) {
     printf("\n Error in Writing");
    _file.setWriteError(1);
    return 0;
  }
  return t;
}
int File::availableForWrite() {
 // if (_file) {
    return _file.availableForWrite();
  //}
  return 0;
}

int File::peek() {
  //if (! _file) {
    return 0;
  //}

  int c = _file.read();
  //if (c != -1) {
    printf("read1");
    _file.seekCur(-1);
  //}
  return c;
}

int File::read() {
  //if (_file) {
    printf("read2");
    return _file.read();
 // }
  return -1;
}

// buffered read for more efficient, high speed reading
int File::read(void *buf, uint16_t nbyte) {
 // if (_file) {
   printf("\n buffered read 3for");
    return _file.read(buf, nbyte);
  //}
  return 0;
}

int File::available() {
 // if (! _file) {
    //return 0;
 // }

  uint32_t n = size() - position();
printf("\n n value=%d",n);
  return n > 0X7FFF ? 0X7FFF : n;
}

void File::flush() {
 // if (_file) {
    _file.sync();
 // }
}
bool File::seek(uint32_t pos) {
 // if (! _file) {
 //   return false;
 // }

  return _file.seekSet(pos);
}

uint32_t File::position() {
  //if (! _file) {
  //  return -1;
  //}
  return _file.curPosition();
}

uint32_t File::size() {
  //if (! _file) {
  //  return 0;
 // }
  return _file.fileSize();
}

void File::close() {
 //if (_file) {
   
    _file.close();
    //free(_file);
    //_file = 0;

    /* for debugging file open/close leaks
      nfilecount--;
      Serial.print("Deleted ");
      Serial.println(nfilecount, DEC);
    */
  //}
}

File::operator bool() {
 // if (_file) {
    return  _file.isOpen();
 // }
  return false;
}



