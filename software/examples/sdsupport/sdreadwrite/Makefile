
#Created by Sathya Narayanan N
# Email id: sathya281@gmail.com

#   Copyright (C) 2019  IIT Madras. All rights reserved.

#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

SHELL := /bin/bash # Use bash syntax
DC ?=
PROGRAM ?=sdsupport
#default target board
TARGET ?= artix7_35t
DEBUG ?=
MARCH ?= rv32imac
MABI  ?= ilp32
XLEN  ?= 32
FLAGS ?=

COMPILER=g++
STANDARD=c++0x

all: create_dir
	make $(PROGRAM).riscv

$(PROGRAM).riscv: create_dir

	@riscv$(XLEN)-unknown-elf-$(COMPILER) -march=$(MARCH) -mabi=$(MABI) -w $(DC) -mcmodel=medany -g -static -std=$(STANDARD) -fno-builtin-printf -I$(bspboard) -I$(bspinc)  -c ./sdvolume.cpp -o ./output/sdvolume.o -lm -lgcc
	@riscv$(XLEN)-unknown-elf-$(COMPILER) -march=$(MARCH) -mabi=$(MABI) -w $(DC) -mcmodel=medany -g -static -std=$(STANDARD) -fno-builtin-printf -I$(bspboard) -I$(bspinc)  -c ./sdreadwrite.cpp -o ./output/sdreadwrite.o -lm -lgcc
	@riscv$(XLEN)-unknown-elf-$(COMPILER) -march=$(MARCH) -mabi=$(MABI) -w $(DC) -mcmodel=medany -g -static -std=$(STANDARD) -fno-builtin-printf -I$(bspboard) -I$(bspinc)  -c ./sd.cpp -o ./output/sd.o -lm -lgcc
	@riscv$(XLEN)-unknown-elf-$(COMPILER) -march=$(MARCH) -mabi=$(MABI) -w $(DC) -mcmodel=medany -g -static -std=$(STANDARD) -fno-builtin-printf -I$(bspboard) -I$(bspinc)  -c ./file.cpp -o ./output/file.o -lm -lgcc
#	@riscv$(XLEN)-unknown-elf-$(COMPILER) -march=$(MARCH) -mabi=$(MABI) -w $(DC) -mcmodel=medany -static -std=$(STANDARD) -fno-builtin-printf -I$(bspboard) -I$(bspinc)  -c ./print.cpp -o ./output/print.o -lm -lgcc
	@riscv$(XLEN)-unknown-elf-$(COMPILER) -march=$(MARCH) -mabi=$(MABI) -w $(DC) -mcmodel=medany -g -static -std=$(STANDARD) -fno-builtin-printf -I$(bspboard) -I$(bspinc)  -c ./sdfile.cpp -o ./output/sdfile.o -lm -lgcc
	@riscv$(XLEN)-unknown-elf-$(COMPILER) -march=$(MARCH) -mabi=$(MABI) -w $(DC) -mcmodel=medany -g -static -std=$(STANDARD) -fno-builtin-printf -I$(bspboard) -I$(bspinc)  -c ./sspi_driver.c -o ./output/sspi.o -lm -lgcc
	@riscv$(XLEN)-unknown-elf-$(COMPILER) -march=$(MARCH) -mabi=$(MABI) -w $(DC) -mcmodel=medany -g -static -std=$(STANDARD) -fno-builtin-printf -I$(bspboard) -I$(bspinc)  -c ./sd2card.cpp -o ./output/sd2card.o -lm -lgcc
	
	@riscv$(XLEN)-unknown-elf-$(COMPILER) -march=$(MARCH) -mabi=$(MABI) -T  $(bspboard)/link.ld $(GENLIB)/gen_lib/libshakti$(XLEN).a  ./output/sdvolume.o ./output/sdreadwrite.o ./output/sd.o ./output/file.o ./output/sdfile.o ./output/sspi.o ./output/sd2card.o -o ./output/$(PROGRAM).shakti -static -nostartfiles -lm -lgcc
	@riscv$(XLEN)-unknown-elf-objdump -D ./output/$(PROGRAM).shakti > ./output/$(PROGRAM).dump
	

create_dir:
	@mkdir -p ./output




  
    