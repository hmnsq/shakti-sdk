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
استورد time

صنف GDB:
	def __init__(self):
		self.gdbmi = None
		self.timeout = 10
		self.command=""
		self.opLog=None 

	def gdbStart(self,gdbPath):
		#open log file
		logFile = 'copy_to_flash_'+str(datetime.now().strftime("%Y-%m-%d_%H:%M:%S"))+ '.log'
		self.opLog=open( logFile,'w+')
		#open gdb
		self.gdbmi=GdbController(gdb_path=gdbPath, gdb_وسائط=None, time_to_check_for_additional_output_sec=4.5, rr=خطأ, verbose=خطأ)
		#print('started gdb')

	def gdbSendCommand(self,command):
		self.command=command
		إذا self.gdbmi is None:
			أرجع خطأ
		#send command and get output.
		response = self.gdbmi.اكتب(command,timeout_sec=self.timeout)
		إذا len(response) == 0:
			أرجع خطأ
		أرجع response

	def gdbClose(self):
		#close gdb
		إذا self.gdbmi is None:
			أرجع خطأ
		self.gdbmi.send_signal_to_gdb("SIGINT")
		self.gdbmi.send_signal_to_gdb(2)
		self.gdbmi.interrupt_gdb()
		أكد self.gdbmi.exit() is None
		أكد self.gdbmi.gdb_process is None
		self.opLog.close()
		أرجع صحيح

	def get_Response_Type_رسالة(self,response):
		Type_رسالة=""
		type_رسالة_رقم = str(response).عدد("payload")
		#get exact gdb console response.
		لكل سطر في range( type_رسالة_رقم ):
			إذا (str(response[سطر]['type'])) == "console":
				Type_رسالة += (str(response[سطر]['payload']))
		self.opLog.اكتب("The output of "+self.command+" :\n"+Type_رسالة+"\n")
		أرجع Type_رسالة	
	
	def gdbSendSignal(self,sig):
		إذا self.gdbmi is None:
			أرجع خطأ
		self.gdbmi.send_signal_to_gdb(sig)

إذا __name__ == "__main__":
	print("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	path_to_sdk = os.getenv("SHAKTISDK")
	إذا path_to_sdk == None:
		print("Set environmental variable SHAKTISDK")
		exit()
	print(path_to_sdk)
	#openocd = path_to_sdk +'/shakti-tools/bin/openocd'
	openocd = 'openocd'
	openocd_config = path_to_sdk +'/bsp/third_party/artix7_35t/ftdi.cfg'
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
	gdbObject.gdbStart(gdb)
#execute commands 
	لكل cmd في command:
		response = gdbObject.gdbSendCommand(cmd)
		إذا (response == خطأ):
			print("\n cmd %s failed\n",cmd)
			اكسر
		gdbObject.get_Response_Type_رسالة(response)
#close gdb
	time.نوم(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

