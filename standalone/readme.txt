To program pinaka board with elfsize more than 8192 bytes. Use the following procedure.

1. Open a bash shell and cd to [absolute path]/shakti-sdk/standalone 
2. #Create executable for elf_to_header if elf_header is not present.
	gcc -g -w elf_to_header.c -o elf_to_header 

3. Convert the elf file to code.mem
    elf2hex 4 32768 [elf file with full path]  2147483648 > code.mem
e.g.
	elf2hex 4 32768 /tmp/arduino_build_371879/Test_code.ino.elf  2147483648 > code.mem

4. find the size of file and pass it as argument to elf_to_header
size=`riscv32-unknown-elf-size  /tmp/arduino_build_371879/Test_code.ino.elf | awk 'FNR == 2 {print $4}'`
size=$(($size/4))
echo "$size"
./elf_to_header $size
5. Build the deploy code.
make
6. program the flash with deploy code.
sudo $(which openocd) -f ../bsp/third_party/pinaka/ftdi.cfg -c "reset init" -c "load_image outputs/deploy.shakti ;resume 0x80000000;shutdown"
