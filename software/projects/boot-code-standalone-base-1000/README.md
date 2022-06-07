Boot Code 

Stand alone boot-code for vajra and sos, interfacing SD Card using SSPI drivers using elm-chan FatFs Library. 

Command to compile:
```
make 
```
Command to clean: 
```
make clean
```
The linker file has the load address set to 0x1000
The load address can be changed in the bootlink.ld file 
