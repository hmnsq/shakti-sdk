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
from pygdbmi.gdbcontroller आयात GdbController
#To use gdb commands and get gdb console outputs.
from pygdbmi आयात gdbmiparser
#To name log files.
from datetime आयात datetime
#To verify gdb console outputs.
आयात re
# To handle arguments to the script
आयात sys
#To start openocd session
आयात os
आयात time

श्रेणी GDB:
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
		self.gdbmi=GdbController(gdb_path=gdbPath, gdb_args=None, time_to_check_for_additional_output_sec=4.5, rr=False, verbose=False)
		#print('started gdb')

	def gdbSendCommand(self,command):
		self.command=command
		अगर self.gdbmi is None:
			वापस False
		#send command and get output.
		response = self.gdbmi.म_लिखो(command,timeout_sec=self.timeout)
		अगर len(response) == 0:
			वापस False
		वापस response

	def gdbClose(self):
		#close gdb
		अगर self.gdbmi is None:
			वापस False
		self.gdbmi.send_signal_to_gdb("SIGINT")
		self.gdbmi.send_signal_to_gdb(2)
		self.gdbmi.interrupt_gdb()
		assert self.gdbmi.exit() is None
		assert self.gdbmi.gdb_process is None
		self.opLog.बंद()
		वापस True

	def get_Response_Type_संदेश(self,response):
		Type_संदेश=""
		type_संदेश_अंक = str(response).गिनती("payload")
		#get exact gdb console response.
		क्रम पंक्ति_2 in range( type_संदेश_अंक ):
			अगर (str(response[पंक्ति_2]['type'])) == "console":
				Type_संदेश += (str(response[पंक्ति_2]['payload']))
		self.opLog.म_लिखो("The output of "+self.command+" :\n"+Type_संदेश+"\n")
		वापस Type_संदेश	
	
	def gdbSendSignal(self,sig):
		अगर self.gdbmi is None:
			वापस False
		self.gdbmi.send_signal_to_gdb(sig)

अगर __name__ == "__main__":
	print("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	path_to_sdk = os.getenv("SHAKTISDK")
	अगर path_to_sdk == None:
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
	क्रम cmd in command:
		response = gdbObject.gdbSendCommand(cmd)
		अगर (response == False):
			print("\n cmd %s failed\n",cmd)
			अवरोध
		gdbObject.get_Response_Type_संदेश(response)
#close gdb
	time.सो_जाओ(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

