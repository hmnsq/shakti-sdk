# Created by Sathya Narayanan N
# Email id: sathya281@gmail.com

# Copyright (C) 2019 IIT Madras. All rights reserved.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>

SHELL := /bin/bash # Use bash syntax
DC ?=
PROGRAM ?= sdsupport
#default target board
FLAGS ?=
SD_DIR= ./sdcard/
SD_DIR1= ./sdcard1/

all: create_dir
	make $(PROGRAM).riscv 

$(PROGRAM).riscv: create_dir
	@riscv$(XLEN)-unknown-elf-gcc  -march=$(MARCH)  -mabi=$(MABI) -w $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -I$(bspinc) -I$(bspdri) -I$(bspboard) -I$(SD_DIR) 	$(FLAGS) -c $(SD_DIR)/spicntrl.c -o ./output/spicntrl.o 
	@riscv$(XLEN)-unknown-elf-gcc  -march=$(MARCH)  -mabi=$(MABI) -w $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -I$(bspinc) -I$(bspdri) -I$(bspboard) -I$(SD_DIR)	$(FLAGS) -c $(bspdri)/sspi/sspi_driver.c -o ./output/sspi_driver.o 
	@riscv$(XLEN)-unknown-elf-gcc  -march=$(MARCH)  -mabi=$(MABI) -w $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -I$(bspinc) -I$(bspdri) -I$(bspboard) -I$(SD_DIR)	$(FLAGS) -c $(SD_DIR)/ff.c -o ./output/ff.o 
	@riscv$(XLEN)-unknown-elf-gcc  -march=$(MARCH)  -mabi=$(MABI) -w $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -I$(bspinc) -I$(bspdri) -I$(bspboard) -I$(SD_DIR) -I$(bspinc)/ethernet 	$(FLAGS) -c ./$(PROGRAM).c -o ./output/$(PROGRAM).o 
	@riscv$(XLEN)-unknown-elf-gcc  -march=$(MARCH)  -mabi=$(MABI) -w $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -I$(bspinc) -I$(bspdri) -I$(bspboard) -I$(SD_DIR) -I$(bspinc)/ethernet 	$(FLAGS) -c ./framethchk.c -o ./output/framethchk.o 
	@riscv$(XLEN)-unknown-elf-gcc -march=$(MARCH) -mabi=$(MABI) -w $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf $(FLAGS) -I$(bsplib) -I$(bspinc) -I$(bspinc)/ethernet -I$(bspboard) -I$(bspdri)/ethernet -c ./poll_eg01.c -o ./output/poll_eg01.o -lm -lgcc
	@riscv$(XLEN)-unknown-elf-gcc -march=$(MARCH) -mabi=$(MABI) $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf -I$(bspinc) -I$(bspboard) -I$(bspinc)/ethernet -c $(bspdri)/ethernet/eth_driver.c -o ./output/eth_driver.o -lm -lgcc

#	@riscv$(XLEN)-unknown-elf-gcc -march=$(MARCH) -mabi=$(MABI) -T  $(bspboard)/link.ld $(GENLIB)/gen_lib/libshakti$(XLEN).a ./output/spicntrl.o ./output/ff.o ./output/$(PROGRAM).o -o ./output/$(PROGRAM).shakti -static -nostartfiles -lm -lgcc
	@echo "Linking files"
	@riscv$(XLEN)-unknown-elf-gcc -T $(bspboard)/link.ld ./output/$(PROGRAM).o   $(GENLIB)/gen_lib/libshakti$(XLEN).a  ./output/framethchk.o ./output/poll_eg01.o ./output/eth_driver.o ./output/sspi_driver.o ./output/ff.o ./output/spicntrl.o  -o ./output/$(PROGRAM).shakti -mcmodel=medany -march=$(MARCH)  -mabi=$(MABI) -static -nostartfiles -lm -lgcc
	@riscv$(XLEN)-unknown-elf-objdump -D ./output/$(PROGRAM).shakti &> ./output/$(PROGRAM).dump
create_dir:
	@mkdir -p ./output
	
clean: 
	@rm -rf $(OUTPUT)
	@echo "cleaned"


#  $(GENLIB)/gen_lib/libshakti$(XLEN).a 
