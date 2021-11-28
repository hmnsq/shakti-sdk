SHELL := /bin/bash # Use bash syntax
XLEN=32

OUTPUT:=./outputs

#ASCII Escape codes
RED='\033[0;31m' #Red
GREEN='\033[0;32m' #Green
NC='\033[0m' # No Color

all: create_dir	boot.riscv

create_dir:
	@mkdir -p $(OUTPUT)

boot.riscv: create_dir 	
	@echo -e "$(GREEN) Compiling flash deploy code $(NC)"
	@echo -e "$(RED) Caveat: Deploy Code starts at 0x80000000. Configure RTL appropriately $(NC)"
	@riscv$(XLEN)-unknown-elf-gcc -w -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -c deploy.c -o $(OUTPUT)/deploy.o -march=rv$(XLEN)imac -mabi=ilp32 
	@riscv$(XLEN)-unknown-elf-gcc -O2 -march=rv$(XLEN)imac -mabi=ilp32 -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -D__ASSEMBLY__=1 -c crt.S -o $(OUTPUT)/crt.o
	@riscv$(XLEN)-unknown-elf-gcc -O2 -march=rv$(XLEN)imac -mabi=ilp32 -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c syscalls.c -o $(OUTPUT)/syscalls.shakti
	@riscv$(XLEN)-unknown-elf-gcc -march=rv$(XLEN)imac -T bootlink.ld  $(OUTPUT)/deploy.o $(OUTPUT)/syscalls.shakti $(OUTPUT)/crt.o -o $(OUTPUT)/deploy.shakti -static -nostartfiles -lm -lgcc
	@riscv$(XLEN)-unknown-elf-objdump -D $(OUTPUT)/deploy.shakti > $(OUTPUT)/deploy.dump

clean: 
	@rm -rf $(OUTPUT)
	@echo "cleaned"
