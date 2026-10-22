#!/usr/bin/env python3

#***************************************************************************
#* Project                               :  shakti devt board
#* Name of the file                      :  burn_to_flash.c
#* Brief Description of file             :  Execute elf that copies target elf to Flash
#* Name of Author                        :  Anand Kumar S
#* Email ID                              :  007334@imail.iitm.ac.in
#
#    Copyright (C) 2019  IIT Madras. All rights reserved.
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
#***************************************************************************

#To open gdb. 
من pygdbmi.gdbcontroller استورد GdbController
#To use gdb commands and get gdb console outputs.
من pygdbmi استورد gdbmiparser
#To name log files.
من datetime استورد datetime
#To verify gdb console outputs.
استورد re
# To handle arguments to the script
استورد sys
#To start openocd session
استورد os
استورد وقت

صنف GDB:
	وصف __init__(self):
		self.gdbmi = ڪجهه_نه
		self.timeout = 10
		self.command=""
		self.opLog=ڪجهه_نه 

	وصف gdb_شروعات(self,gdb_رستو):
		#open log file
		logFile = 'copy_to_flash_'+str(datetime.now().strftime("%Y-%m-%d_%H:%M:%S"))+ '.log'
		self.opLog=open( logFile,'w+')
		#open gdb
		self.gdbmi=GdbController(gdb_رستو_2=gdb_رستو, gdb_دليلون=ڪجهه_نه, وقت_منزل_check_for_additional_output_sec=4.5, rr=خطأ, verbose=خطأ)
		#print('started gdb')

	وصف gdbSendCommand(self,command):
		self.command=command
		إذا self.gdbmi آهي ڪجهه_نه:
			أرجع خطأ
		#send command and get output.
		response = self.gdbmi.اكتب(command,timeout_sec=self.timeout)
		إذا ڊيگهه(response) == 0:
			أرجع خطأ
		أرجع response

	وصف gdbClose(self):
		#close gdb
		إذا self.gdbmi آهي ڪجهه_نه:
			أرجع خطأ
		self.gdbmi.send_signal_منزل_gdb("SIGINT")
		self.gdbmi.send_signal_منزل_gdb(2)
		self.gdbmi.مداخلت_gdb()
		أكد self.gdbmi.exit() آهي ڪجهه_نه
		أكد self.gdbmi.gdb_process آهي ڪجهه_نه
		self.opLog.close()
		أرجع سچ

	وصف get_Response_Type_نياپو(self,response):
		Type_نياپو=""
		type_نياپو_انگ = str(response).ڳڻپ("payload")
		#get exact gdb console response.
		لكل سٽ في سلسلو( type_نياپو_انگ ):
			إذا (str(response[سٽ]['type'])) == "console":
				Type_نياپو += (str(response[سٽ]['payload']))
		self.opLog.اكتب("The output of "+self.command+" :\n"+Type_نياپو+"\n")
		أرجع Type_نياپو	
	
	وصف gdbSendSignal(self,sig):
		إذا self.gdbmi آهي ڪجهه_نه:
			أرجع خطأ
		self.gdbmi.send_signal_منزل_gdb(sig)

إذا __name__ == "__main__":
	ڇاپيو("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	رستو_منزل_sdk = os.getenv("SHAKTISDK")
	إذا رستو_منزل_sdk == ڪجهه_نه:
		ڇاپيو("Set environmental variable SHAKTISDK")
		exit()
	ڇاپيو(رستو_منزل_sdk)
	#openocd = path_to_sdk +'/shakti-tools/bin/openocd'
	openocd = 'openocd'
	openocd_config = رستو_منزل_sdk +'/bsp/third_party/artix7_35t/ftdi.cfg'
	#gdb = path_to_sdk+'/shakti-tools/bin/riscv32-unknown-elf-gdb'
	gdb = 'riscv32-unknown-elf-gdb'
	elf = "file "+ sys.argv[1]
	command = []
	#command.append(gdb)
	command.append("target remote localhost:3333")
	command.append("set remotetimeout unlimited")
	command.append(elf)
	command.append("load")
	command.append("compare-sections")
	command.append("load")
	command.append("compare-sections")
	command.append("continue")
#create a openocd connection in background
	os.system(openocd+' -f '+openocd_config +' &')
	gdbObject = GDB()
	gdbObject.gdb_شروعات(gdb)
#execute commands 
	لكل cmd في command:
		response = gdbObject.gdbSendCommand(cmd)
		إذا (response == خطأ):
			ڇاپيو("\n cmd %s failed\n",cmd)
			اكسر
		gdbObject.get_Response_Type_نياپو(response)
#close gdb
	وقت.نوم(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

