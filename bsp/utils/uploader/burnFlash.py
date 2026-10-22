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
તઃ pygdbmi.gdbcontroller આયાત GdbController
#To use gdb commands and get gdb console outputs.
તઃ pygdbmi આયાત gdbmiparser
#To name log files.
તઃ datetime આયાત datetime
#To verify gdb console outputs.
આયાત re
# To handle arguments to the script
આયાત sys
#To start openocd session
આયાત os
આયાત time

વર્ગ GDB:
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
		self.gdbmi=GdbController(gdb_path=gdbPath, gdb_args=None, time_to_check_for_additional_output_sec=4.5, rr=ખોટું, verbose=ખોટું)
		#print('started gdb')

	def gdbSendCommand(self,command):
		self.command=command
		જો self.gdbmi is None:
			પાછા ખોટું
		#send command and get output.
		response = self.gdbmi.લિખ(command,timeout_sec=self.timeout)
		જો len(response) == 0:
			પાછા ખોટું
		પાછા response

	def gdbClose(self):
		#close gdb
		જો self.gdbmi is None:
			પાછા ખોટું
		self.gdbmi.send_signal_to_gdb("SIGINT")
		self.gdbmi.send_signal_to_gdb(2)
		self.gdbmi.interrupt_gdb()
		પ્રતિજ્ઞા self.gdbmi.exit() is None
		પ્રતિજ્ઞા self.gdbmi.gdb_process is None
		self.opLog.close()
		પાછા સાચું

	def get_Response_Type_સંદેશ(self,response):
		Type_સંદેશ=""
		type_સંદેશ_અંક = str(response).ગણતરી("payload")
		#get exact gdb console response.
		માટે લીટી માં range( type_સંદેશ_અંક ):
			જો (str(response[લીટી]['type'])) == "console":
				Type_સંદેશ += (str(response[લીટી]['payload']))
		self.opLog.લિખ("The output of "+self.command+" :\n"+Type_સંદેશ+"\n")
		પાછા Type_સંદેશ	
	
	def gdbSendSignal(self,sig):
		જો self.gdbmi is None:
			પાછા ખોટું
		self.gdbmi.send_signal_to_gdb(sig)

જો __name__ == "__main__":
	print("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	path_to_sdk = os.getenv("SHAKTISDK")
	જો path_to_sdk == None:
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
	માટે cmd માં command:
		response = gdbObject.gdbSendCommand(cmd)
		જો (response == ખોટું):
			print("\n cmd %s failed\n",cmd)
			તોડો
		gdbObject.get_Response_Type_સંદેશ(response)
#close gdb
	time.સુષુપ્તિ(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

