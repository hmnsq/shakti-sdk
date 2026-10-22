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
தஃ pygdbmi.gdbcontroller இறக்குமதி GdbController
#To use gdb commands and get gdb console outputs.
தஃ pygdbmi இறக்குமதி gdbmiparser
#To name log files.
தஃ datetime இறக்குமதி datetime
#To verify gdb console outputs.
இறக்குமதி re
# To handle arguments to the script
இறக்குமதி sys
#To start openocd session
இறக்குமதி os
இறக்குமதி time

வகுப்பு GDB:
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
		self.gdbmi=GdbController(gdb_path=gdbPath, gdb_args=None, time_to_check_for_additional_output_sec=4.5, rr=பொய், verbose=பொய்)
		#print('started gdb')

	def gdbSendCommand(self,command):
		self.command=command
		எனில் self.gdbmi is None:
			திரும்பு பொய்
		#send command and get output.
		response = self.gdbmi.லிக(command,timeout_sec=self.timeout)
		எனில் len(response) == 0:
			திரும்பு பொய்
		திரும்பு response

	def gdbClose(self):
		#close gdb
		எனில் self.gdbmi is None:
			திரும்பு பொய்
		self.gdbmi.send_signal_to_gdb("SIGINT")
		self.gdbmi.send_signal_to_gdb(2)
		self.gdbmi.interrupt_gdb()
		ப்ரதிஜ்ஞா self.gdbmi.exit() is None
		ப்ரதிஜ்ஞா self.gdbmi.gdb_process is None
		self.opLog.close()
		திரும்பு உண்மை

	def get_Response_Type_செய்தி(self,response):
		Type_செய்தி=""
		type_செய்தி_இலக்கம் = str(response).மொத்தம்("payload")
		#get exact gdb console response.
		க்கு வரி உள் range( type_செய்தி_இலக்கம் ):
			எனில் (str(response[வரி]['type'])) == "console":
				Type_செய்தி += (str(response[வரி]['payload']))
		self.opLog.லிக("The output of "+self.command+" :\n"+Type_செய்தி+"\n")
		திரும்பு Type_செய்தி	
	
	def gdbSendSignal(self,sig):
		எனில் self.gdbmi is None:
			திரும்பு பொய்
		self.gdbmi.send_signal_to_gdb(sig)

எனில் __name__ == "__main__":
	print("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	path_to_sdk = os.getenv("SHAKTISDK")
	எனில் path_to_sdk == None:
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
	க்கு cmd உள் command:
		response = gdbObject.gdbSendCommand(cmd)
		எனில் (response == பொய்):
			print("\n cmd %s failed\n",cmd)
			நிறுத்து
		gdbObject.get_Response_Type_செய்தி(response)
#close gdb
	time.ஸுஷுப்தி(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

