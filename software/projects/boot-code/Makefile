SHELL := /bin/bash # Use bash syntax
XLEN=64

OUTPUT:=./outputs
SD_DIR= ./sdcard
BINCL:=.
MABI:=lp64
MARCH:=rv$(XLEN)imac
#ASCII Escape codes
RED='\033[0;31m' #Red
GREEN='\033[0;32m' #Green
NC='\033[0m' # No Color

all: create_dir	boot.riscv
	

create_dir:
	@mkdir -p $(OUTPUT)

boot.riscv: create_dir 	
	@echo -e "$(GREEN) Compiling BOOT Polling code $(NC)"
	@echo -e "$(RED) Caveat: BOOT Code starts at 0x2000. Configure RTL appropriately $(NC)"
	@riscv$(XLEN)-unknown-elf-gcc -w -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -I./ -I$(SD_DIR) -c boot.c -o $(OUTPUT)/boot.o -march=rv$(XLEN)imac -mabi=lp64 
	@riscv$(XLEN)-unknown-elf-gcc -O2 -march=rv$(XLEN)imac -mabi=lp64 -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -I./ -D__ASSEMBLY__=1 -c crt2.S -o $(OUTPUT)/crt.o
	@riscv$(XLEN)-unknown-elf-gcc -O2 -march=rv$(XLEN)imac -mabi=lp64 -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -D__ASSEMBLY__=1 -c trap.S -o $(OUTPUT)/trap.o
	@riscv$(XLEN)-unknown-elf-gcc -O2 -march=rv$(XLEN)imac -mabi=lp64 -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -I./ -c traps.c -o $(OUTPUT)/traps.o
	
	@riscv$(XLEN)-unknown-elf-gcc -O2 -march=rv$(XLEN)imac -mabi=lp64 -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c syscalls.c -o $(OUTPUT)/syscalls.shakti
	@riscv$(XLEN)-unknown-elf-gcc -O2 -march=rv$(XLEN)imac -mabi=lp64 -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -I./ -c ./sspi/sspi_driver.c -o $(OUTPUT)/sspi.o
	@riscv$(XLEN)-unknown-elf-gcc -O2 -march=rv$(XLEN)imac -mabi=lp64 -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -I./ -I$(SD_DIR) -c $(SD_DIR)/ff.c -o $(OUTPUT)/ff.o
	@riscv$(XLEN)-unknown-elf-gcc -O2 -march=rv$(XLEN)imac -mabi=lp64 -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -I./ -I$(SD_DIR) -c $(SD_DIR)/spicntrl.c -o $(OUTPUT)/spicntrl.o
	@riscv$(XLEN)-unknown-elf-gcc -march=rv$(XLEN)imac -T bootlink2.ld  $(OUTPUT)/boot.o $(OUTPUT)/syscalls.shakti $(OUTPUT)/crt.o $(OUTPUT)/trap.o $(OUTPUT)/traps.o $(OUTPUT)/sspi.o $(OUTPUT)/ff.o $(OUTPUT)/spicntrl.o -o $(OUTPUT)/boot.shakti -static -nostartfiles -lm -lgcc
	@riscv$(XLEN)-unknown-elf-objdump -D $(OUTPUT)/boot.shakti > $(OUTPUT)/boot.dump
	@elf2hex 4 4096 $(OUTPUT)/boot.shakti 4096 > $(OUTPUT)/boot.mem

clean: 
	@rm -rf $(OUTPUT)
	@echo "cleaned"
